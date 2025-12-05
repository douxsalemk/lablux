#include <ESP8266WiFi.h>

// Substitua pelas suas credenciais de rede.
const char* ssid     = "Trojan";         
const char* password = "84f58tg56h8ae"; 

// Defina um servidor com a porta 80.
WiFiServer server(80);

// Variável para armazenar a solicitação HTTP.
String header;

// Variável para armazenar o estado de saída atual.
// String outputState = "Desligado";
String outputState1 = "Desligado";
String outputState2 = "Desligado";
String outputState3 = "Desligado";
String outputState4 = "Desligado";
String outputState5 = "Desligado";
String outputState6 = "Desligado";
String outputState7 = "Desligado";
String outputState8 = "Desligado";
String outputState9 = "Desligado";
String outputState10 = "Desligado";
String outputState11 = "Desligado";
String outputState12 = "Desligado";
String outputState13 = "Desligado";
String outputState14 = "Desligado";
String outputState15 = "Desligado";
String outputState16 = "Desligado";
String outputState17 = "Desligado";
String outputState18 = "Desligado";
String outputState19 = "Desligado";
String outputState20 = "Desligado";
String outputState21 = "Desligado";
String outputState22 = "Desligado";
String outputState23 = "Desligado";
String outputState24 = "Desligado";
String outputState25 = "Desligado";
String outputState26 = "Desligado";
String outputState27 = "Desligado";
String outputState28 = "Desligado";
String outputState29 = "Desligado";
String outputState30 = "Desligado";
String outputState31 = "Desligado";
String outputState32 = "Desligado";
String outputState33 = "Desligado";
String outputState34 = "Desligado";
String outputState35 = "Desligado";
String outputState36 = "Desligado";
String outputState37 = "Desligado";
String outputState38 = "Desligado";
String outputState39 = "Desligado";
String outputState40 = "Desligado";

unsigned long currentTime = millis();
unsigned long previousTime = 0;
// Defina um timeout de 2000 milisegundos.
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  delay(5000);
  // Conecte com a rede Wi-Fi com SSID e senha.
  //Serial.print("Conectando a rede ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
  //Inicie o servidor.
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Escute os clientes conectados 
  if (client) {                             // Se um novo cliente se conectar
    String currentLine = "";                // Faça uma String para armazenar dados recebidos do cliente
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop enquanto cliente estiver conectado.
      currentTime = millis();
      if (client.available()) {             // Se holver bytes para ler do cliente,
        char c = client.read();             // faça a leitura.
        header += c;
        if (c == '\n') {                    // Se o byte é um caractere de nova linha, 
                                            // é o fim da solicitação HTML,entao envie uma resposta.
          if (currentLine.length() == 0) {  
            //Envie um cabeçalho HTTP de resposta.
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Procure o trecho "GET /1/on" dentro da solicitação do recebida do cliente.
            if (header.indexOf("GET /1/on") >= 0) {
              //Envie um comando para Mega2560 via serial.
              Serial.println("LED_ON");
              //Altere a variavel de estado.
              outputState1 = "Ligado";
            } else if (header.indexOf("GET /1/off") >= 0) {
              //Envie um comando para Mega2560 via serial.
              Serial.println("LED_OFF");
              //Altere a variavel de estado.
              outputState1 = "Desligado";
            }

            if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("LED_ON");
              outputState2 = "Ligado";
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("LED_OFF");
              outputState2 = "Desligado";
            }

            if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("LED_ON");
              outputState3 = "Ligado";
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("LED_OFF");
              outputState3 = "Desligado";
            }

            if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("LED_ON");
              outputState4 = "Ligado";
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("LED_OFF");
              outputState4 = "Desligado";
            }

            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("LED_ON");
              outputState5 = "Ligado";
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("LED_OFF");
              outputState5 = "Desligado";
            }

            if (header.indexOf("GET /6/on") >= 0) {
              Serial.println("LED_ON");
              outputState6 = "Ligado";
            } else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("LED_OFF");
              outputState6 = "Desligado";
            }

            if (header.indexOf("GET /7/on") >= 0) {
              Serial.println("LED_ON");
              outputState7 = "Ligado";
            } else if (header.indexOf("GET /7/off") >= 0) {
              Serial.println("LED_OFF");
              outputState7 = "Desligado";
            }

            if (header.indexOf("GET /8/on") >= 0) {
              Serial.println("LED_ON");
              outputState8 = "Ligado";
            } else if (header.indexOf("GET /8/off") >= 0) {
              Serial.println("LED_OFF");
              outputState8 = "Desligado";
            }

            if (header.indexOf("GET /9/on") >= 0) {
              Serial.println("LED_ON");
              outputState9 = "Ligado";
            } else if (header.indexOf("GET /9/off") >= 0) {
              Serial.println("LED_OFF");
              outputState9 = "Desligado";
            }

            if (header.indexOf("GET /10/on") >= 0) {
              Serial.println("LED_ON");
              outputState10 = "Ligado";
            } else if (header.indexOf("GET /10/off") >= 0) {
              Serial.println("LED_OFF");
              outputState10 = "Desligado";
            }

            if (header.indexOf("GET /11/on") >= 0) {
              Serial.println("LED_ON");
              outputState11 = "Ligado";
            } else if (header.indexOf("GET /11/off") >= 0) {
              Serial.println("LED_OFF");
              outputState11 = "Desligado";
            }

            if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("LED_ON");
              outputState12 = "Ligado";
            } else if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("LED_OFF");
              outputState12 = "Desligado";
            }

            if (header.indexOf("GET /13/on") >= 0) {
              Serial.println("LED_ON");
              outputState13 = "Ligado";
            } else if (header.indexOf("GET /13/off") >= 0) {
              Serial.println("LED_OFF");
              outputState13 = "Desligado";
            }

            if (header.indexOf("GET /14/on") >= 0) {
              Serial.println("LED_ON");
              outputState14 = "Ligado";
            } else if (header.indexOf("GET /14/off") >= 0) {
              Serial.println("LED_OFF");
              outputState14 = "Desligado";
            }

            if (header.indexOf("GET /15/on") >= 0) {
              Serial.println("LED_ON");
              outputState15 = "Ligado";
            } else if (header.indexOf("GET /15/off") >= 0) {
              Serial.println("LED_OFF");
              outputState15 = "Desligado";
            }

            if (header.indexOf("GET /16/on") >= 0) {
              Serial.println("LED_ON");
              outputState16 = "Ligado";
            } else if (header.indexOf("GET /16/off") >= 0) {
              Serial.println("LED_OFF");
              outputState16 = "Desligado";
            }

            if (header.indexOf("GET /17/on") >= 0) {
              Serial.println("LED_ON");
              outputState17 = "Ligado";
            } else if (header.indexOf("GET /17/off") >= 0) {
              Serial.println("LED_OFF");
              outputState17 = "Desligado";
            }

            if (header.indexOf("GET /18/on") >= 0) {
              Serial.println("LED_ON");
              outputState18 = "Ligado";
            } else if (header.indexOf("GET /18/off") >= 0) {
              Serial.println("LED_OFF");
              outputState18 = "Desligado";
            }

            if (header.indexOf("GET /19/on") >= 0) {
              Serial.println("LED_ON");
              outputState19 = "Ligado";
            } else if (header.indexOf("GET /19/off") >= 0) {
              Serial.println("LED_OFF");
              outputState19 = "Desligado";
            }

            if (header.indexOf("GET /20/on") >= 0) {
              Serial.println("LED_ON");
              outputState20 = "Ligado";
            } else if (header.indexOf("GET /20/off") >= 0) {
              Serial.println("LED_OFF");
              outputState20 = "Desligado";
            }

            if (header.indexOf("GET /21/on") >= 0) {
              Serial.println("LED_ON");
              outputState21 = "Ligado";
            } else if (header.indexOf("GET /21/off") >= 0) {
              Serial.println("LED_OFF");
              outputState21 = "Desligado";
            }

            if (header.indexOf("GET /22/on") >= 0) {
              Serial.println("LED_ON");
              outputState22 = "Ligado";
            } else if (header.indexOf("GET /22/off") >= 0) {
              Serial.println("LED_OFF");
              outputState22 = "Desligado";
            }

            if (header.indexOf("GET /23/on") >= 0) {
              Serial.println("LED_ON");
              outputState23 = "Ligado";
            } else if (header.indexOf("GET /23/off") >= 0) {
              Serial.println("LED_OFF");
              outputState23 = "Desligado";
            }

            if (header.indexOf("GET /24/on") >= 0) {
              Serial.println("LED_ON");
              outputState24 = "Ligado";
            } else if (header.indexOf("GET /24/off") >= 0) {
              Serial.println("LED_OFF");
              outputState24 = "Desligado";
            }

            if (header.indexOf("GET /25/on") >= 0) {
              Serial.println("LED_ON");
              outputState25 = "Ligado";
            } else if (header.indexOf("GET /25/off") >= 0) {
              Serial.println("LED_OFF");
              outputState25 = "Desligado";
            }

            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("LED_ON");
              outputState26 = "Ligado";
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("LED_OFF");
              outputState26 = "Desligado";
            }

            if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("LED_ON");
              outputState27 = "Ligado";
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("LED_OFF");
              outputState27 = "Desligado";
            }

            if (header.indexOf("GET /28/on") >= 0) {
              Serial.println("LED_ON");
              outputState28 = "Ligado";
            } else if (header.indexOf("GET /28/off") >= 0) {
              Serial.println("LED_OFF");
              outputState28 = "Desligado";
            }

            if (header.indexOf("GET /29/on") >= 0) {
              Serial.println("LED_ON");
              outputState29 = "Ligado";
            } else if (header.indexOf("GET /29/off") >= 0) {
              Serial.println("LED_OFF");
              outputState29 = "Desligado";
            }

            if (header.indexOf("GET /30/on") >= 0) {
              Serial.println("LED_ON");
              outputState30 = "Ligado";
            } else if (header.indexOf("GET /30/off") >= 0) {
              Serial.println("LED_OFF");
              outputState30 = "Desligado";
            }

            if (header.indexOf("GET /31/on") >= 0) {
              Serial.println("LED_ON");
              outputState31 = "Ligado";
            } else if (header.indexOf("GET /31/off") >= 0) {
              Serial.println("LED_OFF");
              outputState31 = "Desligado";
            }

            if (header.indexOf("GET /32/on") >= 0) {
              Serial.println("LED_ON");
              outputState32 = "Ligado";
            } else if (header.indexOf("GET /32/off") >= 0) {
              Serial.println("LED_OFF");
              outputState32 = "Desligado";
            }

            if (header.indexOf("GET /33/on") >= 0) {
              Serial.println("LED_ON");
              outputState33 = "Ligado";
            } else if (header.indexOf("GET /33/off") >= 0) {
              Serial.println("LED_OFF");
              outputState33 = "Desligado";
            }

            if (header.indexOf("GET /34/on") >= 0) {
              Serial.println("LED_ON");
              outputState34 = "Ligado";
            } else if (header.indexOf("GET /34/off") >= 0) {
              Serial.println("LED_OFF");
              outputState34 = "Desligado";
            }

            if (header.indexOf("GET /35/on") >= 0) {
              Serial.println("LED_ON");
              outputState35 = "Ligado";
            } else if (header.indexOf("GET /35/off") >= 0) {
              Serial.println("LED_OFF");
              outputState35 = "Desligado";
            }

            if (header.indexOf("GET /36/on") >= 0) {
              Serial.println("LED_ON");
              outputState36 = "Ligado";
            } else if (header.indexOf("GET /36/off") >= 0) {
              Serial.println("LED_OFF");
              outputState36 = "Desligado";
            }

            if (header.indexOf("GET /37/on") >= 0) {
              Serial.println("LED_ON");
              outputState37 = "Ligado";
            } else if (header.indexOf("GET /37/off") >= 0) {
              Serial.println("LED_OFF");
              outputState37 = "Desligado";
            }

            if (header.indexOf("GET /38/on") >= 0) {
              Serial.println("LED_ON");
              outputState38 = "Ligado";
            } else if (header.indexOf("GET /38/off") >= 0) {
              Serial.println("LED_OFF");
              outputState38 = "Desligado";
            }

            if (header.indexOf("GET /39/on") >= 0) {
              Serial.println("LED_ON");
              outputState39 = "Ligado";
            } else if (header.indexOf("GET /39/off") >= 0) {
              Serial.println("LED_OFF");
              outputState39 = "Desligado";
            }

            if (header.indexOf("GET /40/on") >= 0) {
              Serial.println("LED_ON");
              outputState40 = "Ligado";
            } else if (header.indexOf("GET /40/off") >= 0) {
              Serial.println("LED_OFF");
              outputState40 = "Desligado";
            }


              // Pagina HTML
              client.println("<!DOCTYPE html><html>");
              // client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
              // client.println("<link rel=\"icon\" href=\"data:,\">");
              // // CSS para estilizar a pagina
              // client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
              // client.println("h1,p {font-weight: bold;color: #126e54; font-size: 32px;}");
              // client.println("p {font-size: 16px;}");
              // client.println(".button { background-color: #1BAE85; border: none; color: white; padding: 16px 40px;");
              // client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
              // client.println("</style></head>");

  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"icon\" href=\"data:,\">");  
  // CSS
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println("h1 { font-weight: bold; color: #126e54; font-size: 32px; margin-bottom: 20px; }");
  client.println(".group-container { display: inline-block; width: 200px; margin: 10px; padding: 15px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }");
  client.println(".group-title { font-weight: bold; color: #333; font-size: 18px; margin-bottom: 10px; }");
  client.println(".group-state { color: #666; font-size: 14px; margin-bottom: 10px; }");
  client.println(".button { background-color: #1BAE85; border: none; color: white; padding: 10px 20px;");
  client.println("  text-decoration: none; font-size: 16px; margin: 2px; cursor: pointer;border-radius: 5px; transition: background-color 0.3s;}");
  client.println(".button:hover { background-color: #0e8c6a; }");
  client.println(".button-off { background-color: #e74c3c; }");
  client.println(".button-off:hover { background-color: #c0392b; }");
  client.println("</style></head><body>");

              client.println("<h1>LABLUX - Controle de Grupos</h1>");
  
    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 1 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState1 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState1 == "Desligado") {
                client.print("<a href=\"/1/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/1/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");

    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 2 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState2 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState2 == "Desligado") {
                client.print("<a href=\"/2/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/2/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");

    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 3 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState3 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState3 == "Desligado") {
                client.print("<a href=\"/3/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/3/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");

    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 4 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState4 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState4 == "Desligado") {
                client.print("<a href=\"/4/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/4/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");

    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 5 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState5 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState5 == "Desligado") {
                client.print("<a href=\"/5/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/5/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 6 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState6 + "</div>");              
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState6 == "Desligado") {
                client.print("<a href=\"/6/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/6/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 7 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState7 + "</div>");              
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState7 == "Desligado") {
                client.print("<a href=\"/7/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/7/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 8 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState8 + "</div>");              
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState8 == "Desligado") {
                client.print("<a href=\"/8/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/8/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 9 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState9 + "</div>");              
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState9 == "Desligado") {
                client.print("<a href=\"/9/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/9/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 10 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState10 + "</div>");              
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState10 == "Desligado") {
                client.print("<a href=\"/10/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/10/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 11 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState11 + "</div>");              
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState11 == "Desligado") {
                client.print("<a href=\"/11/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/11/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 12 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState12 + "</div>");              
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState12 == "Desligado") {
                client.print("<a href=\"/12/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/12/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 13 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState13 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState13 == "Desligado") {
                client.print("<a href=\"/13/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/13/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 14 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState14 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState14 == "Desligado") {
                client.print("<a href=\"/14/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/14/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 15 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState15 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState15 == "Desligado") {
                client.print("<a href=\"/15/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/15/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 16 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState16 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState16 == "Desligado") {
                client.print("<a href=\"/16/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/16/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 17 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState17 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState17 == "Desligado") {
                client.print("<a href=\"/17/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/17/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 18 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState18 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState18 == "Desligado") {
                client.print("<a href=\"/18/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/18/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 19 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState19 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState19 == "Desligado") {
                client.print("<a href=\"/19/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/19/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 20 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState20 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState20 == "Desligado") {
                client.print("<a href=\"/20/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/20/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 21 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState21 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState21 == "Desligado") {
                client.print("<a href=\"/21/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/21/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 22 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState22 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState22 == "Desligado") {
                client.print("<a href=\"/22/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/22/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 23 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState23 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState23 == "Desligado") {
                client.print("<a href=\"/23/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/23/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 24 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState24 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState24 == "Desligado") {
                client.print("<a href=\"/24/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/24/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 25 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState25 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState25 == "Desligado") {
                client.print("<a href=\"/25/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/35/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 26 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState26 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState26 == "Desligado") {
                client.print("<a href=\"/26/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/26/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 27 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState27 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState27 == "Desligado") {
                client.print("<a href=\"/27/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/27/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 28 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState28 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState28 == "Desligado") {
                client.print("<a href=\"/28/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/28/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 29 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState29 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState29 == "Desligado") {
                client.print("<a href=\"/29/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/29/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 30 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState30 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState30 == "Desligado") {
                client.print("<a href=\"/30/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/30/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 31 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState31 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState31 == "Desligado") {
                client.print("<a href=\"/31/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/31/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 32 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState32 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState32 == "Desligado") {
                client.print("<a href=\"/32/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/32/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 33 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState33 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState33 == "Desligado") {
                client.print("<a href=\"/33/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/33/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 34 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState34 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState34 == "Desligado") {
                client.print("<a href=\"/34/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/34/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 35 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState35 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState35 == "Desligado") {
                client.print("<a href=\"/35/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/35/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 36 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState36 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState36 == "Desligado") {
                client.print("<a href=\"/36/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/36/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 37 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState37 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState37 == "Desligado") {
                client.print("<a href=\"/37/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/37/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 38 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState38 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState38 == "Desligado") {
                client.print("<a href=\"/38/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/38/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 39 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState39 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState39 == "Desligado") {
                client.print("<a href=\"/39/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/39/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


    client.println("<div class=\"group-container\">");
    client.println("<div class=\"group-title\">Grupo 40 </div>");
    client.println("<div class=\"group-state\">Estado: " + outputState40 + "</div>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState40 == "Desligado") {
                client.print("<a href=\"/40/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/40/off\"><button class=\"button button2\">Desligar</button></a>");
              }
    client.println("</div>");


              // Mostre o estado atual do pino 13, aqui representado pela variavel de estado outputState. 
              client.println("<p>Grupo 1 - Estado " + outputState1 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState1 == "Desligado") {
                client.print("<a href=\"/1/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/1/off\"><button class=\"button button2\">Desligar</button></a>");
              }

              client.println("<p>Grupo 2 - Estado " + outputState2 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState2 == "Desligado") {
                client.print("<a href=\"/2/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/2/off\"><button class=\"button button2\">Desligar</button></a>");
              }

              client.println("<p>Grupo 3 - Estado " + outputState3 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState3 == "Desligado") {
                client.print("<a href=\"/3/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/3/off\"><button class=\"button button2\">Desligar</button></a>");
              }

              client.println("<p>Grupo 4 - Estado " + outputState4 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState4 == "Desligado") {
                client.print("<a href=\"/4/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/4/off\"><button class=\"button button2\">Desligar</button></a>");
              }

              client.println("<p>Grupo 5 - Estado " + outputState5 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState5 == "Desligado") {
                client.print("<a href=\"/5/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/5/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 6 - Estado " + outputState6 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState6 == "Desligado") {
                client.print("<a href=\"/6/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/6/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 7 - Estado " + outputState7 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState7 == "Desligado") {
                client.print("<a href=\"/7/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/7/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 8 - Estado " + outputState8 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState8 == "Desligado") {
                client.print("<a href=\"/8/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/8/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 9 - Estado " + outputState9 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState9 == "Desligado") {
                client.print("<a href=\"/9/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/9/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 10 - Estado " + outputState10 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState10 == "Desligado") {
                client.print("<a href=\"/10/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/10/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 11 - Estado " + outputState11 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState11 == "Desligado") {
                client.print("<a href=\"/11/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/11/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 12 - Estado " + outputState12 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState12 == "Desligado") {
                client.print("<a href=\"/12/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/12/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 13 - Estado " + outputState13 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState13 == "Desligado") {
                client.print("<a href=\"/13/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/13/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 14 - Estado " + outputState14 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState14 == "Desligado") {
                client.print("<a href=\"/14/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/14/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 15 - Estado " + outputState15 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState15 == "Desligado") {
                client.print("<a href=\"/15/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/15/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 16 - Estado " + outputState16 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState16 == "Desligado") {
                client.print("<a href=\"/16/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/16/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 17 - Estado " + outputState17 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState17 == "Desligado") {
                client.print("<a href=\"/17/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/17/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 18 - Estado " + outputState18 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState18 == "Desligado") {
                client.print("<a href=\"/18/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/18/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 19 - Estado " + outputState19 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState19 == "Desligado") {
                client.print("<a href=\"/19/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/19/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 20 - Estado " + outputState20 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState20 == "Desligado") {
                client.print("<a href=\"/20/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/20/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 21 - Estado " + outputState21 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState21 == "Desligado") {
                client.print("<a href=\"/21/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/21/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 22 - Estado " + outputState22 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState22 == "Desligado") {
                client.print("<a href=\"/22/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/22/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 23 - Estado " + outputState23 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState23 == "Desligado") {
                client.print("<a href=\"/23/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/23/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 24 - Estado " + outputState24 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState24 == "Desligado") {
                client.print("<a href=\"/24/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/24/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 25 - Estado " + outputState25 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState25 == "Desligado") {
                client.print("<a href=\"/25/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/35/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 26 - Estado " + outputState26 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState26 == "Desligado") {
                client.print("<a href=\"/26/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/26/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 27 - Estado " + outputState27 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState27 == "Desligado") {
                client.print("<a href=\"/27/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/27/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 28 - Estado " + outputState28 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState28 == "Desligado") {
                client.print("<a href=\"/28/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/28/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 29 - Estado " + outputState29 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState29 == "Desligado") {
                client.print("<a href=\"/29/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/29/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 30 - Estado " + outputState30 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState30 == "Desligado") {
                client.print("<a href=\"/30/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/30/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 31 - Estado " + outputState31 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState31 == "Desligado") {
                client.print("<a href=\"/31/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/31/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 32 - Estado " + outputState32 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState32 == "Desligado") {
                client.print("<a href=\"/32/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/32/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 33 - Estado " + outputState33 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState33 == "Desligado") {
                client.print("<a href=\"/33/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/33/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 34 - Estado " + outputState34 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState34 == "Desligado") {
                client.print("<a href=\"/34/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/34/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 35 - Estado " + outputState35 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState35 == "Desligado") {
                client.print("<a href=\"/35/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/35/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 36 - Estado " + outputState36 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState36 == "Desligado") {
                client.print("<a href=\"/36/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/36/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 37 - Estado " + outputState37 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState37 == "Desligado") {
                client.print("<a href=\"/37/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/37/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 38 - Estado " + outputState38 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState38 == "Desligado") {
                client.print("<a href=\"/38/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/38/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 39 - Estado " + outputState39 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState39 == "Desligado") {
                client.print("<a href=\"/39/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/39/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("<p>Grupo 40 - Estado " + outputState40 + "</p>");
              // Se outputState estiver como Desligado, crie um botao com texto Ligar.
              if (outputState40 == "Desligado") {
                client.print("<a href=\"/40/on\"><button class=\"button\">Ligar</button></a>");
              } else {
                // Se outputState estiver como Ligado, crie um botao com texto Desligar.
                client.print("<a href=\"/40/off\"><button class=\"button button2\">Desligar</button></a>");
              }


              client.println("</body></html>");
              // A resposta HTTP termina com outra linha em branco.
              client.println();
              break;
            } else { // Se você recebeu uma nova linha, limpe currentLine
              currentLine = "";
            }
          } else if (c != '\r') {  // Se você tiver mais alguma coisa além de um caractere de retorno de carro,
            currentLine += c;      // Adicione-o ao final do currentLine.
          }
        }
      }
      // Limpe a variável de cabeçalho
      header = "";
      // Feche a conexão.
      client.stop();
    }
  }