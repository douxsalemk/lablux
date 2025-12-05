#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


// Substitua pelas suas credenciais de rede.
const char* ssid     = "Trojan";         
const char* password = "84f58tg56h8ae"; 
// const char* ssid     = "KASA";         
// const char* password = "188k1001kg"; 


// Defina um servidor com a porta 80.
WiFiServer server(80);

// Variável para armazenar a solicitação HTTP.
String header;

// Variáveis para armazenar o estado, tempo e data/horário de criação.
String outputState4 = "Desligado";
String outputTime4 = "";
String outputCreatedAt4 = "";
String outputState5 = "Desligado";
String outputTime5 = "";
String outputCreatedAt5 = "";
String outputState6 = "Desligado";
String outputTime6 = "";
String outputCreatedAt6 = "";
String outputState7 = "Desligado";
String outputTime7 = "";
String outputCreatedAt7 = "";
String outputState8 = "Desligado";
String outputTime8 = "";
String outputCreatedAt8 = "";
String outputState9 = "Desligado";
String outputTime9 = "";
String outputCreatedAt9 = "";
String outputState10 = "Desligado";
String outputTime10 = "";
String outputCreatedAt10 = "";

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

void setup() {
  Serial.begin(115200);
  delay(3000);
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

            // Processa requisições PUT
            if (header.indexOf("PUT /4/on") >= 0) {
              Serial.println("LED_ON_4");
              outputState4 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime4 = timeStr;
                }
                // outputCreatedAt4 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt4 = body.substring(createdAtStart, createdAtEnd);

                // long diff = getTimeDifference(outputCreatedAt4, outputTime4);
                // Serial.println("Horário de differença Epoch: " + String(diff));
              }
            } else if (header.indexOf("PUT /4/off") >= 0) {
              Serial.println("LED_OFF_4");
              outputState4 = "Desligado";
              outputTime4 = "";
              outputCreatedAt4 = "";
            }

            if (header.indexOf("PUT /5/on") >= 0) {
              Serial.println("LED_ON_5");
              outputState5 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime5 = timeStr;
                }
                // outputCreatedAt5 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt5 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /5/off") >= 0) {
              Serial.println("LED_OFF_5");
              outputState5 = "Desligado";
              outputTime5 = "";
              outputCreatedAt5 = "";
            }

            if (header.indexOf("PUT /6/on") >= 0) {
              Serial.println("LED_ON_6");
              outputState6 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime6 = timeStr;
                }
                // outputCreatedAt6 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt6 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /6/off") >= 0) {
              Serial.println("LED_OFF_6");
              outputState6 = "Desligado";
              outputTime6 = "";
              outputCreatedAt6 = "";
            }

            if (header.indexOf("PUT /7/on") >= 0) {
              Serial.println("LED_ON_7");
              outputState7 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime7 = timeStr;
                }
                // outputCreatedAt7 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt7 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /7/off") >= 0) {
              Serial.println("LED_OFF_7");
              outputState7 = "Desligado";
              outputTime7 = "";
              outputCreatedAt7 = "";
            }

            if (header.indexOf("PUT /8/on") >= 0) {
              Serial.println("LED_ON_8");
              outputState8 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime8 = timeStr;
                }
                // outputCreatedAt8 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt8 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /8/off") >= 0) {
              Serial.println("LED_OFF_8");
              outputState8 = "Desligado";
              outputTime8 = "";
              outputCreatedAt8 = "";
            }

            if (header.indexOf("PUT /9/on") >= 0) {
              Serial.println("LED_ON_9");
              outputState9 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime9 = timeStr;
                }
                // outputCreatedAt9 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt9 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /9/off") >= 0) {
              Serial.println("LED_OFF_9");
              outputState9 = "Desligado";
              outputTime9 = "";
              outputCreatedAt9 = "";
            }

            if (header.indexOf("PUT /10/on") >= 0) {
              Serial.println("LED_ON_10");
              outputState10 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime10 = timeStr;
                }
                // outputCreatedAt10 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt10 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /10/off") >= 0) {
              Serial.println("LED_OFF_10");
              outputState10 = "Desligado";
              outputTime10 = "";
              outputCreatedAt10 = "";
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

            // Grupo 4
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 4 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState4 + "</div>");
            if (outputState4 == "Ligado" && outputTime4 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime4 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt4 + "</div>");
            }
            if (outputState4 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/4/on', '4')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/4/off', '4')\">Desligar</button>");
            }
            client.println("<select id=\"time4\">");
            client.println("<option value=\"1\"" + String(outputTime4 == "" || outputTime4 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime4 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime4 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime4 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 5
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 5 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState5 + "</div>");
            if (outputState5 == "Ligado" && outputTime5 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime5 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt5 + "</div>");
            }
            if (outputState5 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/5/on', '5')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/5/off', '5')\">Desligar</button>");
            }
            client.println("<select id=\"time5\">");
            client.println("<option value=\"1\"" + String(outputTime5 == "" || outputTime5 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime5 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime5 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime5 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 6
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 6 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState6 + "</div>");
            if (outputState6 == "Ligado" && outputTime6 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime6 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt6 + "</div>");
            }
            if (outputState6 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/6/on', '6')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/6/off', '6')\">Desligar</button>");
            }
            client.println("<select id=\"time6\">");
            client.println("<option value=\"1\"" + String(outputTime6 == "" || outputTime6 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime6 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime6 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime6 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 7
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 7 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState7 + "</div>");
            if (outputState7 == "Ligado" && outputTime7 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime7 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt7 + "</div>");
            }
            if (outputState7 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/7/on', '7')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/7/off', '7')\">Desligar</button>");
            }
            client.println("<select id=\"time7\">");
            client.println("<option value=\"1\"" + String(outputTime7 == "" || outputTime7 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime7 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime7 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime7 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 8
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 8 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState8 + "</div>");
            if (outputState8 == "Ligado" && outputTime8 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime8 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt8 + "</div>");
            }
            if (outputState8 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/8/on', '8')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/8/off', '8')\">Desligar</button>");
            }
            client.println("<select id=\"time8\">");
            client.println("<option value=\"1\"" + String(outputTime8 == "" || outputTime8 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime8 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime8 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime8 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 9
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 9 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState9 + "</div>");
            if (outputState9 == "Ligado" && outputTime9 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime9 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt9 + "</div>");
            }
            if (outputState9 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/9/on', '9')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/9/off', '9')\">Desligar</button>");
            }
            client.println("<select id=\"time9\">");
            client.println("<option value=\"1\"" + String(outputTime9 == "" || outputTime9 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime9 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime9 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime9 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 10
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 10 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState10 + "</div>");
            if (outputState10 == "Ligado" && outputTime10 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime10 + "000h" + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt10 + "</div>");
            }
            if (outputState10 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/10/on', '10')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/10/off', '10')\">Desligar</button>");
            }
            client.println("<select id=\"time10\">");
            client.println("<option value=\"1\"" + String(outputTime10 == "" || outputTime10 == "1" ? " selected" : "") + ">1000 h</option>");
            client.println("<option value=\"2\"" + String(outputTime10 == "2" ? " selected" : "") + ">2000 h</option>");
            client.println("<option value=\"5\"" + String(outputTime10 == "5" ? " selected" : "") + ">5000 h</option>");
            client.println("<option value=\"10\"" + String(outputTime10 == "10" ? " selected" : "") + ">10000 h</option>");
            client.println("</select>");
            client.println("</div>");

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

  // if (currentTime - previousTime <= checkTimeoutTime) {
    if (outputState4 == "Ligado") {
      long diff2 = getTimeDifference(outputCreatedAt4, outputTime4);
      // Serial.println("AQUI: " + String(diff2));
      if (getTimeDifference(outputCreatedAt4, outputTime4) > 0) {
        Serial.println("LED_OFF_4");
        outputState4 = "Desligado";
        outputTime4 = "";
        outputCreatedAt4 = "";
      }
    } 
    if (outputState5 == "Ligado") {
      if (getTimeDifference(outputCreatedAt5, outputTime5) > 0) {
        Serial.println("LED_OFF_5");
        outputState5 = "Desligado";
        outputTime5 = "";
        outputCreatedAt5 = "";
      }               
    } 
    if (outputState6 == "Ligado") {
      if (getTimeDifference(outputCreatedAt6, outputTime6) > 0) {
        Serial.println("LED_OFF_6");
        outputState6 = "Desligado";
        outputTime6 = "";
        outputCreatedAt6 = "";
      }               
    } 
    if (outputState7 == "Ligado") {
      if (getTimeDifference(outputCreatedAt7, outputTime7) > 0) {
        Serial.println("LED_OFF_7");
        outputState7 = "Desligado";
        outputTime7 = "";
        outputCreatedAt7 = "";
      }               
    }
    if (outputState8 == "Ligado") {
      if (getTimeDifference(outputCreatedAt8, outputTime8) > 0) {
        Serial.println("LED_OFF_8");
        outputState8 = "Desligado";
        outputTime8 = "";
        outputCreatedAt8 = "";
      }               
    } 
    if (outputState9 == "Ligado") {
      if (getTimeDifference(outputCreatedAt9, outputTime9) > 0) {
        Serial.println("LED_OFF_9");
        outputState9 = "Desligado";
        outputTime9 = "";
        outputCreatedAt9 = "";
      }               
    } 
    if (outputState10 == "Ligado") {
      if (getTimeDifference(outputCreatedAt10, outputTime10) > 0) {
        Serial.println("LED_OFF_10");
        outputState10 = "Desligado";
        outputTime10 = "";
        outputCreatedAt10 = "";
      }               
    }
  // }
  
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


ESP866   . esp866
// config 567 para carregar e 56 para testar

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


// Substitua pelas suas credenciais de rede.
const char* ssid     = "Trojan";         
const char* password = "84f58tg56h8ae"; 
// const char* ssid     = "KASA";         
// const char* password = "188k1001kg"; 


// Defina um servidor com a porta 80.
WiFiServer server(80);

// Variável para armazenar a solicitação HTTP.
String header;

// Variáveis para armazenar o estado, tempo e data/horário de criação.
String outputState4 = "Desligado";
String outputTime4 = "";
String outputCreatedAt4 = "";
String outputState5 = "Desligado";
String outputTime5 = "";
String outputCreatedAt5 = "";
String outputState6 = "Desligado";
String outputTime6 = "";
String outputCreatedAt6 = "";
String outputState7 = "Desligado";
String outputTime7 = "";
String outputCreatedAt7 = "";
String outputState8 = "Desligado";
String outputTime8 = "";
String outputCreatedAt8 = "";
String outputState9 = "Desligado";
String outputTime9 = "";
String outputCreatedAt9 = "";
String outputState10 = "Desligado";
String outputTime10 = "";
String outputCreatedAt10 = "";

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

void setup() {
  Serial.begin(115200);
  delay(3000);
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

            // Processa requisições PUT
            if (header.indexOf("PUT /4/on") >= 0) {
              Serial.println("LED_ON_4");
              outputState4 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime4 = timeStr;
                }
                // outputCreatedAt4 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt4 = body.substring(createdAtStart, createdAtEnd);

                // long diff = getTimeDifference(outputCreatedAt4, outputTime4);
                // Serial.println("Horário de differença Epoch: " + String(diff));
              }
            } else if (header.indexOf("PUT /4/off") >= 0) {
              Serial.println("LED_OFF_4");
              outputState4 = "Desligado";
              outputTime4 = "";
              outputCreatedAt4 = "";
            }

            if (header.indexOf("PUT /5/on") >= 0) {
              Serial.println("LED_ON_5");
              outputState5 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime5 = timeStr;
                }
                // outputCreatedAt5 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt5 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /5/off") >= 0) {
              Serial.println("LED_OFF_5");
              outputState5 = "Desligado";
              outputTime5 = "";
              outputCreatedAt5 = "";
            }

            if (header.indexOf("PUT /6/on") >= 0) {
              Serial.println("LED_ON_6");
              outputState6 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime6 = timeStr;
                }
                // outputCreatedAt6 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt6 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /6/off") >= 0) {
              Serial.println("LED_OFF_6");
              outputState6 = "Desligado";
              outputTime6 = "";
              outputCreatedAt6 = "";
            }

            if (header.indexOf("PUT /7/on") >= 0) {
              Serial.println("LED_ON_7");
              outputState7 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime7 = timeStr;
                }
                // outputCreatedAt7 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt7 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /7/off") >= 0) {
              Serial.println("LED_OFF_7");
              outputState7 = "Desligado";
              outputTime7 = "";
              outputCreatedAt7 = "";
            }

            if (header.indexOf("PUT /8/on") >= 0) {
              Serial.println("LED_ON_8");
              outputState8 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime8 = timeStr;
                }
                // outputCreatedAt8 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt8 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /8/off") >= 0) {
              Serial.println("LED_OFF_8");
              outputState8 = "Desligado";
              outputTime8 = "";
              outputCreatedAt8 = "";
            }

            if (header.indexOf("PUT /9/on") >= 0) {
              Serial.println("LED_ON_9");
              outputState9 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime9 = timeStr;
                }
                // outputCreatedAt9 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt9 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /9/off") >= 0) {
              Serial.println("LED_OFF_9");
              outputState9 = "Desligado";
              outputTime9 = "";
              outputCreatedAt9 = "";
            }

            if (header.indexOf("PUT /10/on") >= 0) {
              Serial.println("LED_ON_10");
              outputState10 = "Ligado";
              if (body.indexOf("\"time\":") >= 0 && body.indexOf("\"created_at\":") >= 0) {
                String timeStr = body.substring(body.indexOf("\"time\":") + 7, body.indexOf(",", body.indexOf("\"time\":")));
                if (timeStr == "1" || timeStr == "2" || timeStr == "5" || timeStr == "10") {
                  outputTime10 = timeStr;
                }
                // outputCreatedAt10 = body.substring(body.indexOf("\"created_at\":\"") + 13, body.indexOf("\"", body.indexOf("\"created_at\":\"") + 13));
                int createdAtStart = body.indexOf("\"created_at\":\"") + 14;
                // Assume que created_at tem formato "YYYY-MM-DD HH:mm:ss" (19 caracteres)
                int createdAtEnd = createdAtStart + 19;
                outputCreatedAt10 = body.substring(createdAtStart, createdAtEnd);
              }
            } else if (header.indexOf("PUT /10/off") >= 0) {
              Serial.println("LED_OFF_10");
              outputState10 = "Desligado";
              outputTime10 = "";
              outputCreatedAt10 = "";
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

            // Grupo 4
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 4 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState4 + "</div>");
            if (outputState4 == "Ligado" && outputTime4 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime4 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt4 + "</div>");
            }
            if (outputState4 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/4/on', '4')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/4/off', '4')\">Desligar</button>");
            }
            client.println("<select id=\"time4\">");
            client.println("<option value=\"1\"" + String(outputTime4 == "" || outputTime4 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime4 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime4 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime4 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 5
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 5 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState5 + "</div>");
            if (outputState5 == "Ligado" && outputTime5 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime5 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt5 + "</div>");
            }
            if (outputState5 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/5/on', '5')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/5/off', '5')\">Desligar</button>");
            }
            client.println("<select id=\"time5\">");
            client.println("<option value=\"1\"" + String(outputTime5 == "" || outputTime5 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime5 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime5 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime5 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 6
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 6 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState6 + "</div>");
            if (outputState6 == "Ligado" && outputTime6 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime6 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt6 + "</div>");
            }
            if (outputState6 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/6/on', '6')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/6/off', '6')\">Desligar</button>");
            }
            client.println("<select id=\"time6\">");
            client.println("<option value=\"1\"" + String(outputTime6 == "" || outputTime6 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime6 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime6 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime6 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 7
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 7 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState7 + "</div>");
            if (outputState7 == "Ligado" && outputTime7 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime7 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt7 + "</div>");
            }
            if (outputState7 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/7/on', '7')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/7/off', '7')\">Desligar</button>");
            }
            client.println("<select id=\"time7\">");
            client.println("<option value=\"1\"" + String(outputTime7 == "" || outputTime7 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime7 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime7 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime7 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 8
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 8 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState8 + "</div>");
            if (outputState8 == "Ligado" && outputTime8 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime8 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt8 + "</div>");
            }
            if (outputState8 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/8/on', '8')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/8/off', '8')\">Desligar</button>");
            }
            client.println("<select id=\"time8\">");
            client.println("<option value=\"1\"" + String(outputTime8 == "" || outputTime8 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime8 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime8 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime8 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 9
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 9 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState9 + "</div>");
            if (outputState9 == "Ligado" && outputTime9 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime9 + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt9 + "</div>");
            }
            if (outputState9 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/9/on', '9')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/9/off', '9')\">Desligar</button>");
            }
            client.println("<select id=\"time9\">");
            client.println("<option value=\"1\"" + String(outputTime9 == "" || outputTime9 == "1" ? " selected" : "") + ">1</option>");
            client.println("<option value=\"2\"" + String(outputTime9 == "2" ? " selected" : "") + ">2</option>");
            client.println("<option value=\"5\"" + String(outputTime9 == "5" ? " selected" : "") + ">5</option>");
            client.println("<option value=\"10\"" + String(outputTime9 == "10" ? " selected" : "") + ">10</option>");
            client.println("</select>");
            client.println("</div>");

            // Grupo 10
            client.println("<div class=\"group-container\">");
            client.println("<div class=\"group-title\">Grupo 10 </div>");
            client.println("<div class=\"group-state\">Estado: " + outputState10 + "</div>");
            if (outputState10 == "Ligado" && outputTime10 != "") {
              client.println("<div class=\"group-time\">Ensaio: " + outputTime10 + "000h" + "</div>");
              client.println("<div class=\"group-created\">Criado em: " + outputCreatedAt10 + "</div>");
            }
            if (outputState10 == "Desligado") {
              client.println("<button class=\"button\" onclick=\"sendPutRequest('/10/on', '10')\">Ligar</button>");
            } else {
              client.println("<button class=\"button button-off\" onclick=\"sendPutRequest('/10/off', '10')\">Desligar</button>");
            }
            client.println("<select id=\"time10\">");
            client.println("<option value=\"1\"" + String(outputTime10 == "" || outputTime10 == "1" ? " selected" : "") + ">1000 h</option>");
            client.println("<option value=\"2\"" + String(outputTime10 == "2" ? " selected" : "") + ">2000 h</option>");
            client.println("<option value=\"5\"" + String(outputTime10 == "5" ? " selected" : "") + ">5000 h</option>");
            client.println("<option value=\"10\"" + String(outputTime10 == "10" ? " selected" : "") + ">10000 h</option>");
            client.println("</select>");
            client.println("</div>");

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

  // if (currentTime - previousTime <= checkTimeoutTime) {
    if (outputState4 == "Ligado") {
      long diff2 = getTimeDifference(outputCreatedAt4, outputTime4);
      // Serial.println("AQUI: " + String(diff2));
      if (getTimeDifference(outputCreatedAt4, outputTime4) > 0) {
        Serial.println("LED_OFF_4");
        outputState4 = "Desligado";
        outputTime4 = "";
        outputCreatedAt4 = "";
      }
    } 
    if (outputState5 == "Ligado") {
      if (getTimeDifference(outputCreatedAt5, outputTime5) > 0) {
        Serial.println("LED_OFF_5");
        outputState5 = "Desligado";
        outputTime5 = "";
        outputCreatedAt5 = "";
      }               
    } 
    if (outputState6 == "Ligado") {
      if (getTimeDifference(outputCreatedAt6, outputTime6) > 0) {
        Serial.println("LED_OFF_6");
        outputState6 = "Desligado";
        outputTime6 = "";
        outputCreatedAt6 = "";
      }               
    } 
    if (outputState7 == "Ligado") {
      if (getTimeDifference(outputCreatedAt7, outputTime7) > 0) {
        Serial.println("LED_OFF_7");
        outputState7 = "Desligado";
        outputTime7 = "";
        outputCreatedAt7 = "";
      }               
    }
    if (outputState8 == "Ligado") {
      if (getTimeDifference(outputCreatedAt8, outputTime8) > 0) {
        Serial.println("LED_OFF_8");
        outputState8 = "Desligado";
        outputTime8 = "";
        outputCreatedAt8 = "";
      }               
    } 
    if (outputState9 == "Ligado") {
      if (getTimeDifference(outputCreatedAt9, outputTime9) > 0) {
        Serial.println("LED_OFF_9");
        outputState9 = "Desligado";
        outputTime9 = "";
        outputCreatedAt9 = "";
      }               
    } 
    if (outputState10 == "Ligado") {
      if (getTimeDifference(outputCreatedAt10, outputTime10) > 0) {
        Serial.println("LED_OFF_10");
        outputState10 = "Desligado";
        outputTime10 = "";
        outputCreatedAt10 = "";
      }               
    }
  // }
  
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

