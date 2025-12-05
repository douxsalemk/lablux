#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>

const char* ssid = "iPhone"; // <-- set
const char* password = "doux@doux"; // <-- set

const int NUM_PORTS = 20;

WiFiServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -3600*3, 60000);

// read log from Arduino via Serial: send READLOG,N and wait LOG_START/LOG_END
String requestLogFromArduino(int N = 100, unsigned long timeoutMs = 8000) {
  String cmd = "READLOG," + String(N);
  // clear serial buffer
  while (Serial.available()) Serial.read();
  Serial.println(cmd);
  unsigned long start = millis();
  bool inLog = false;
  String out = "";
  while (millis() - start < timeoutMs) {
    if (Serial.available()) {
      String line = Serial.readStringUntil('\n');
      line.trim();
      if (line.length() == 0) continue;
      if (!inLog) {
        if (line == "LOG_START") inLog = true;
        else if (line.startsWith("ERR")) return line;
      } else {
        if (line == "LOG_END") return out;
        out += line + "\n";
      }
    }
    delay(5);
  }
  return String("ERR,TIMEOUT");
}

void serveLogsCsv(WiFiClient &client) {
  String csv = requestLogFromArduino(100, 8000);
  if (csv.startsWith("ERR")) {
    client.println("HTTP/1.1 500 Internal Server Error");
    client.println("Content-Type: text/plain; charset=utf-8");
    client.println("Connection: close");
    client.println();
    client.print(csv);
    return;
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/csv; charset=utf-8");
  client.print("Content-Length: "); client.println(csv.length());
  client.println("Connection: close");
  client.println();
  client.print(csv);
}

void serveIndex(WiFiClient &client) {
  // minimal dynamic page with buttons for ports and link to logs
  String html = "<!doctype html><html><head><meta charset='utf-8'><title>Controle</title></head><body>";
  html += "<h1>Controle de Portas</h1>";
  html += "<a href='/logs'>Ver Histórico</a><br/><br/>";
  html += "<div style='display:flex;flex-wrap:wrap;'>";
  for (int i = 1; i <= NUM_PORTS; i++) {
    int port = i + 3; // match earlier scheme where physical ports start at 4
    html += "<div style='width:220px;margin:6px;padding:8px;border:1px solid #ccc;border-radius:6px;'>";
    html += "<div><strong>Grupo " + String(i) + "</strong></div>";
    html += "<button onclick=\"fetch('/" + String(port) + "/on',{method:'PUT'}).then(()=>location.reload())\">Ligar</button> ";
    html += "<button onclick=\"fetch('/" + String(port) + "/off',{method:'PUT'}).then(()=>location.reload())\">Desligar</button>";
    html += "<div>Tempo: <select id='t" + String(port) + "'><option value='0'>Sem tempo</option><option value='1'>2000 h</option><option value='2'>3000 h</option><option value='5'>6000 h</option><option value='10'>Teste 1 min</option></select></div>";
    html += "</div>";
  }
  html += "</div></body></html>";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=utf-8");
  client.print("Content-Length: "); client.println(html.length());
  client.println("Connection: close");
  client.println();
  client.print(html);
}

void setup() {
  Serial.begin(115200);
  delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  server.begin();
  timeClient.begin(); timeClient.update();
}

unsigned long computeEndEpoch(int timeCode) {
  // timeCode: 1->2000h,2->3000h,5->6000h,10->1min (test)
  unsigned long addSeconds = 0;
  if (timeCode == 1) addSeconds = (unsigned long)2000 * 60UL * 60UL;
  else if (timeCode == 2) addSeconds = (unsigned long)3000 * 60UL * 60UL;
  else if (timeCode == 5) addSeconds = (unsigned long)6000 * 60UL * 60UL;
  else if (timeCode == 10) addSeconds = 60UL; // 1 minute for test
  if (addSeconds == 0) return 0;
  timeClient.update();
  unsigned long now = timeClient.getEpochTime();
  return now + addSeconds;
}

void handlePut(WiFiClient &client, const String &path, const String &body) {
  // path like /7/on
  int p2 = path.indexOf('/', 1);
  if (p2 < 0) { client.println("HTTP/1.1 400 Bad Request\r\nConnection: close\r\n\r\n"); return; }
  int port = path.substring(1, p2).toInt();
  String action = path.substring(p2 + 1);

  // body is expected to contain time selection if any, but we also can read select via fetch-less implementation
  int timeCode = 0;
  int tpos = body.indexOf("time=");
  if (tpos >= 0) {
    int vpos = tpos + 5;
    int amp = body.indexOf('&', vpos);
    String ts = (amp > 0) ? body.substring(vpos, amp) : body.substring(vpos);
    timeCode = ts.toInt();
  }

  unsigned long endEpoch = computeEndEpoch(timeCode);
  String reason = "web_manual";
  String cmd = "EVENT," + String(port) + "," + (action == "on" ? "ON" : "OFF") + "," + String(endEpoch) + "," + reason;
  Serial.println(cmd);

  client.println("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nOK");
}

void serveLogsPage(WiFiClient &client) {
  const char* html = "<!doctype html><html><head><meta charset='utf-8'><title>Logs</title></head><body>"
    "<h2>Histórico de Eventos</h2>"
    "<a href='/'>Voltar</a><br/><br/>"
    "<button onclick=\"load()\">Atualizar</button>"
    "<table id='tbl' border=1><thead><tr><th>Data/Hora</th><th>Epoch</th><th>Porta</th><th>Ação</th><th>Fim</th><th>Motivo</th></tr></thead><tbody></tbody></table>"
    "<script>async function load(){document.querySelector('tbody').innerHTML='';let r=await fetch('/logs.csv'); if(!r.ok){alert('Erro');return;} let txt=await r.text(); txt.split('\n').filter(l=>l.trim()).forEach(l=>{const f=l.split(','); let tr=document.createElement('tr'); tr.innerHTML=`<td>${f[0]}</td><td>${f[1]}</td><td>${f[2]}</td><td>${f[3]}</td><td>${f[4]}</td><td>${f.slice(6).join(',')}</td>`; document.querySelector('tbody').appendChild(tr); }); } window.onload=load;</script></body></html>";
  client.println("HTTP/1.1 200 OK"); client.println("Content-Type: text/html; charset=utf-8"); client.print("Content-Length: "); client.println(strlen(html)); client.println("Connection: close"); client.println(); client.print(html);
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;
  String reqLine = client.readStringUntil('\n');
  if (reqLine.indexOf("GET /logs.csv") >= 0) {
    // consume rest
    while (client.available()) { String l = client.readStringUntil('\n'); if (l == "\r") break; }
    serveLogsCsv(client);
  } else if (reqLine.indexOf("GET /logs") >= 0) {
    while (client.available()) { String l = client.readStringUntil('\n'); if (l == "\r") break; }
    serveLogsPage(client);
  } else if (reqLine.indexOf("GET /") >= 0) {
    while (client.available()) { String l = client.readStringUntil('\n'); if (l == "\r") break; }
    serveIndex(client);
  } else if (reqLine.indexOf("PUT /") >= 0) {
    // read first line to obtain path
    int s1 = reqLine.indexOf(' ');
    int s2 = reqLine.indexOf(' ', s1 + 1);
    String path = reqLine.substring(s1 + 1, s2);
    // read headers and detect Content-Length
    int contentLength = 0;
    while (client.available()) {
      String h = client.readStringUntil('\n');
      h.trim();
      if (h.length() == 0) break;
      if (h.startsWith("Content-Length:")) {
        contentLength = h.substring(15).toInt();
      }
    }
    String body = "";
    if (contentLength > 0) {
      while ((int)body.length() < contentLength) { if (client.available()) body += (char)client.read(); else delay(1); }
    }
    handlePut(client, path, body);
  } else {
    // 404
    while (client.available()) client.read();
    client.println("HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\n");
  }
  delay(1);
  client.stop();
}