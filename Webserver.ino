#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


// Substitua pelas suas credenciais de rede.
// const char* ssid     = "Trojan";         
// const char* password = "84f58tg56h8ae"; 
const char* ssid     = "DouxKarina";         
const char* password = "Casa403@17"; 


// Defina um servidor com a porta 80.
WiFiServer server(80);

// Variável para armazenar a solicitação HTTP.
String header;

// Quantidade de grupos controlados.
const int NUM_GRUPOS = 25;
// Arrays para estado, tempo selecionado e horário de criação de cada grupo.
String outputState[NUM_GRUPOS];
String outputTime[NUM_GRUPOS];
String outputCreatedAt[NUM_GRUPOS];

unsigned long currentTime = millis();
unsigned long previousTime = 0;
// Defina um timeout de 5000 milisegundos.
const long timeoutTime = 5000;
// Intervalo para verificar se o grupo permanece ligado ou nao
const long checkTimeoutTime = 5000;

// Configuração do cliente NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


// Declaração antecipada das funções
String getFormattedTime();
unsigned long parseTimeToEpoch(String timeStr);
long getTimeDifference(String createdAt, String outputTime);
long getEndTime(String outputTime);
int parseGroupId(const String &path);
bool isOnPath(const String &path);
String extractJsonField(const String &body, const String &field);

void setup() {
  Serial.begin(115200);
  delay(3000);
  for (int i = 0; i < NUM_GRUPOS; i++) {
    outputState[i] = "Desligado";
    outputTime[i] = "";
    outputCreatedAt[i] = "";
  }
  // Conecte com a rede Wi-Fi com SSID e senha.
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Imprime o endereço IP local e inicia o servidor web
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
  // Inicie o servidor.
  server.begin();


  // Iniciar cliente servidorNTP
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(-3600*3);

  timeClient.update();

  time_t epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  
  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime); 
  Serial.println("Horário NTP: " + getFormattedTime());
}

void loop() {
  timeClient.update();

  WiFiClient client = server.available();   // Escute os clientes conectados 
  if (client) {                             // Se um novo cliente se conectar
    // Serial.println("Novo cliente conectado.");
    String currentLine = "";                // String para armazenar dados recebidos
    String body = "";                      // Para armazenar o corpo da requisição
    bool isBody = false;                   // Flag para indicar leitura do corpo
    header = "";                           // Limpa o cabeçalho
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // Loop enquanto cliente estiver conectado
      currentTime = millis();
      if (client.available()) {             // Se houver bytes para ler
        char c = client.read();            // Lê o caractere
        // Serial.print(c);                   // Imprime no monitor serial para depuração
        if (isBody) {
          body += c;                       // Armazena o corpo
        } else {
          header += c;                     // Armazena o cabeçalho
        }
        if (c == '\n') {                   // Se for uma nova linha
          if (currentLine.length() == 0) { // Linha em branco indica fim do cabeçalho
            isBody = true;
            // Tenta ler o corpo com espera
            unsigned long readStart = millis();
            // Começa a ler o corpo
            while (millis() - readStart < 500) { // Espera até 500ms pelo corpo
              if (client.available()) {
                c = client.read();
                // Serial.print(c);
                body += c;
              }
              delay(1); // Pequeno atraso para evitar sobrecarga
            }
            // Imprime o cabeçalho e corpo para depuração
            // Serial.println("\nCabeçalho recebido: ");
            // Serial.println(header);
            // Serial.println("Corpo recebido: ");
            // Serial.println(body);
            // Serial.println("Tamanho do corpo: " + String(body.length()));

            // Envie um cabeçalho HTTP de resposta
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Processa requisições PUT em formato /<id>/on ou /<id>/off
            int firstLineEnd = header.indexOf("\r\n");
            String requestLine = firstLineEnd > 0 ? header.substring(0, firstLineEnd) : header;
            String path = "";
            if (requestLine.startsWith("PUT ")) {
              int s1 = requestLine.indexOf(' ');
              int s2 = requestLine.indexOf(' ', s1 + 1);
              if (s1 > 0 && s2 > s1) {
                path = requestLine.substring(s1 + 1, s2);
              }
            }
            int groupId = parseGroupId(path); // 1..NUM_GRUPOS
            bool ligar = isOnPath(path);
            if (groupId >= 1 && groupId <= NUM_GRUPOS) {
              int idx = groupId - 1;
              if (ligar) {
                Serial.print("LED_ON_"); Serial.println(groupId);
                outputState[idx] = "Ligado";
                String timeStr = extractJsonField(body, "time");
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime[idx] = timeStr;
                }
                String created = extractJsonField(body, "created_at");
                if (created.length() >= 19) {
                  outputCreatedAt[idx] = created.substring(0, 19);
                }
              } else if (groupId > 0) {
                Serial.print("LED_OFF_"); Serial.println(groupId);
                outputState[idx] = "Desligado";
                outputTime[idx] = "";
                outputCreatedAt[idx] = "";
              }
            }

            // Página HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\">");  
            // CSS
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println("h1 { font-weight: bold; color: #126e54; font-size: 32px; margin-bottom: 20px; }");
            client.println(".group-container { display: inline-block; width: 200px; margin: 10px; padding: 15px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }");
            client.println(".group-title { font-weight: bold; color: #333; font-size: 18px; margin-bottom: 10px; }");
            client.println(".group-state { color: #666; font-size: 14px; margin-bottom: 10px; }");
            client.println(".group-time { color: #666; font-size: 14px; margin-bottom: 10px; }");
            client.println(".group-created { color: #666; font-size: 14px; margin-bottom: 10px; }");
            client.println(".button { background-color: #1BAE85; border: none; color: white; padding: 10px 20px;");
            client.println("text-decoration: none; font-size: 16px; margin: 2px; cursor: pointer; border-radius: 5px; transition: background-color 0.3s;}");
            client.println(".button:hover { background-color: #0e8c6a; }");
            client.println(".button-off { background-color: #e74c3c; }");
            client.println(".button-off:hover { background-color: #c0392b; }");
            client.println("select { width: 100%; padding: 8px; margin-top: 8px; font-size: 14px; border-radius: 5px; }");
            client.println("</style>");
            // JavaScript para enviar requisições PUT
            client.println("<script>");
            client.println("function sendPutRequest(url, groupId) {");
            client.println("  console.log('Enviando PUT para: ' + url);");
            client.println("  let time = document.getElementById('time' + groupId).value;");
            client.println("  console.log('Ensaio selecionado: ' + time);");
            client.println("  let now = new Date();");
            client.println("  let createdAt = now.getFullYear() + '-' +");
            client.println("    String(now.getMonth() + 1).padStart(2, '0') + '-' +");
            client.println("    String(now.getDate()).padStart(2, '0') + ' ' +");
            client.println("    String(now.getHours()).padStart(2, '0') + ':' +");
            client.println("    String(now.getMinutes()).padStart(2, '0') + ':' +");
            client.println("    String(now.getSeconds()).padStart(2, '0');");
            client.println("  console.log('Created At: ' + createdAt);");
            client.println("  fetch(url, {");
            client.println("    method: 'PUT',");
            client.println("    headers: {'Content-Type': 'application/json'},");
            client.println("    body: JSON.stringify({time: parseInt(time), created_at: createdAt})");
            client.println("  }).then(response => {");
            client.println("    console.log('Resposta recebida:', response);");
            client.println("    location.reload();");
            client.println("  }).catch(error => console.error('Erro:', error));");
            client.println("}");
            client.println("</script>");
            client.println("</head><body>");

            client.println("<h1>LABLUX - Controle de Grupos</h1>");

            // Renderização dos grupos em loop
            for (int id = 1; id <= NUM_GRUPOS; id++) {
              int idx = id - 1;
              client.println("<div class=\"group-container\">");
              client.println("<div class=\"group-title\">Grupo " + String(id) + " </div>");
              client.println("<div class=\"group-state\">Estado: " + outputState[idx] + "</div>");
              if (outputState[idx] == "Ligado" && outputTime[idx] != "") {
                client.println("<div class=\"group-time\">Ensaio: " + outputTime[idx] + "</div>");
                client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt[idx] + "</div>");
              }
              String onUrl = "/" + String(id) + "/on";
              String offUrl = "/" + String(id) + "/off";
              if (outputState[idx] == "Desligado") {
                client.println("<button class=\"button\" onclick=\"sendPutRequest('" + onUrl + "', '" + String(id) + "')\">Ligar</button>");
              } else {
                client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('" + offUrl + "', '" + String(id) + "')\">Desligar</button>");
              }
              client.println("<select id=\"time" + String(id) + "\">");
              // mesmas opções de tempo (valores 1,2,5,10)
              client.println("<option value=\"1\"" + String(outputTime[idx] == "" || outputTime[idx] == "1" ? " selected" : "") + ">1</option>");
              client.println("<option value=\"2\"" + String(outputTime[idx] == "2" ? " selected" : "") + ">2</option>");
              client.println("<option value=\"5\"" + String(outputTime[idx] == "5" ? " selected" : "") + ">5</option>");
              client.println("<option value=\"10\"" + String(outputTime[idx] == "10" ? " selected" : "") + ">10</option>");
              client.println("</select>");
              client.println("</div>");
            }

            client.println("</body></html>");
            // A resposta HTTP termina com outra linha em branco
            client.println();
            break;
          } else { // Se recebeu uma nova linha, limpe currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // Se tiver mais alguma coisa além de um caractere de retorno de carro
          currentLine += c;      // Adicione ao final do currentLine
        }
      }
    }
    // Limpe as variáveis
    header = "";
    body = "";
    // Feche a conexão
    client.stop();
    // Serial.println("Cliente desconectado.");
  }

    for (int id = 1; id <= NUM_GRUPOS; id++) {
      int idx = id - 1;
      if (outputState[idx] == "Ligado" && outputTime[idx] != "") {
        if (getTimeDifference(outputCreatedAt[idx], outputTime[idx]) > 0) {
          Serial.print("LED_OFF_"); Serial.println(id);
          outputState[idx] = "Desligado";
          outputTime[idx] = "";
          outputCreatedAt[idx] = "";
        }
      }
    }
  
  // Serial.println("2");
}

// Formata o horário NTP
String getFormattedTime() {
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);
  int year = ptm->tm_year + 1900;
  int month = ptm->tm_mon + 1;
  int day = ptm->tm_mday;
  int hour = ptm->tm_hour;
  int minute = ptm->tm_min;
  int second = ptm->tm_sec;
  char formattedTime[20];
  sprintf(formattedTime, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
  return String(formattedTime);
}

// Converte string YYYY-MM-DD HH:mm:ss para epoch
unsigned long parseTimeToEpoch(String timeStr) {
  int year, month, day, hour, minute, second;
  sscanf(timeStr.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
  struct tm t = {0};
  t.tm_year = year - 1900;
  t.tm_mon = month - 1;
  t.tm_mday = day;
  t.tm_hour = hour;
  t.tm_min = minute;
  t.tm_sec = second;
  return mktime(&t); // Ajusta para UTC (NTP retorna UTC, +3h para Brasília)
}

// Calcula diferença entre a data de finalização dp ensaio e horário atual
long getTimeDifference(String createdAt, String outputTime) {
  unsigned long createdEpoch = parseTimeToEpoch(createdAt);
  unsigned long currentEpoch = timeClient.getEpochTime();
  long endTime = getEndTime(outputTime);
  long convertedCurrentEpoch = currentEpoch;
  long convertedCreatedAt = createdEpoch;
  long diff = convertedCurrentEpoch - convertedCreatedAt;
  return diff - endTime;
}

long getEndTime(String outputTime) {
  if (outputTime == "1") {
    return long(5);
  } else if (outputTime == "2") {
    return long(10);
  } else if (outputTime == "5") {
    return long(15);
  } else if (outputTime == "10") {
    return long(20);
  }
  return long(20);
}

int parseGroupId(const String &path) {
  int p2 = path.indexOf('/', 1);
  if (p2 < 0) return -1;
  return path.substring(1, p2).toInt();
}

bool isOnPath(const String &path) {
  return path.endsWith("/on");
}

// Extrai campo simples de um JSON pequeno (número ou string).
String extractJsonField(const String &body, const String &field) {
  String key = "\"" + field + "\":";
  int pos = body.indexOf(key);
  if (pos < 0) return "";
  int start = pos + key.length();
  // pula espaços
  while (start < (int)body.length() && body[start] == ' ') start++;
  if (start >= (int)body.length()) return "";
  // valor string
  if (body[start] == '\"') {
    start++;
    int end = body.indexOf('"', start);
    if (end < 0) return "";
    return body.substring(start, end);
  }
  // valor numérico
  int end = body.indexOf(',', start);
  if (end < 0) end = body.length();
  return body.substring(start, end).trim();
}