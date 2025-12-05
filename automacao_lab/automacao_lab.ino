#include <ArduinoWiFiServer.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266mDNS.h>        // Include the mDNS library

#include <ESP8266WebServer.h>   // Include the WebServer library


ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();

const char* ssid     = "Trojan";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "84f58tg56h8ae";     // The password of the Wi-Fi network

// GPIOs to control
const int pins[] = {4, 5};  // GPIO 4 and 5
bool states[] = {false, false};  // Store pin states

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

  if (!MDNS.begin("esp8266")) {             // Start the mDNS responder for esp8266.local
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");


  pinMode(12, INPUT);
  // Initialize GPIOs as output
  for (int i = 0; i < 2; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], states[i] ? HIGH : LOW);
  }

  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/toggle", handleToggle);
  server.on("/status", handleStatus);
  server.on("/network", handleNetworkStatus);
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop() { 
  MDNS.update();  // Keep mDNS activ
  server.handleClient(); 

  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 5000) {
    lastPrint = millis();
    Serial.print("GPIO 4: "); Serial.println(digitalRead(4));
    Serial.print("GPIO 5: "); Serial.println(digitalRead(5));
    Serial.print("GPIO 12: "); Serial.println(digitalRead(12));
  }
  // Print GPIO states every 3 seconds
  // static unsigned long lastPrint = 0;
  // if (millis() - lastPrint > 3000) {
  //   lastPrint = millis();
  //   Serial.print("GPIO States: ");
  //   Serial.print("4 -> "); Serial.print(states[0] ? "ON" : "OFF");
  //   Serial.print(" | 5 -> "); Serial.println(states[1] ? "ON" : "OFF");
  //   Serial.print(" | Rede -> "); Serial.println(digitalRead(12) ? "ON" : "OFF");
  // }

  // Serial.println('\n');
  // Serial.println("Connection established!"); 
   
  // Serial.print("IP address:\t");
  // Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
  // delay(5000);
}

// Web Page
void handleRoot() {
  int networkState = digitalRead(12); // Lê o estado do pino 12 para a rede

  String html = R"rawliteral(
    <html>
    <head>
      <title>ESP8266 Control</title>
      <script>
        function togglePin(pin) {
          var xhr = new XMLHttpRequest();
          xhr.open('GET', '/toggle?pin=' + pin, true);
          xhr.onload = function() {
            var btn = document.getElementById('btn-' + pin);
            btn.style.backgroundColor = (xhr.responseText === 'ON') ? 'green' : 'red';
          };
          xhr.send();
        }
      
        function updateStatus() {
          var xhr = new XMLHttpRequest();
          xhr.open("GET", "/status", true);
          xhr.onload = function() {
            document.getElementById("status").innerHTML = xhr.responseText;
            updateButtonColors();  // Update button colors based on the status
          };
          xhr.send();
        }

        function updateButtonColors() {
          // Extract individual GPIO states from the status string
          var gpioStates = {};
          var statusLines = status.split('|');
          statusLines.forEach(function(line) {
            var match = line.match(/GPIO (\d+): (\w+)/);
            if (match) {
              var pin = match[1];
              var state = match[2];
              gpioStates[pin] = state;
            }
          });
          
          // Update button colors based on the GPIO states
          var buttons = document.getElementsByClassName('gpio-button');
          for (var i = 0; i < buttons.length; i++) {
            var pin = buttons[i].getAttribute('data-pin');
            var state = gpioStates[pin] === 'ON' ? 'green' : 'red';
            buttons[i].style.backgroundColor = state;
          }
        }

        setInterval(updateStatus, 2000);

        function updateNetworkStatus() {
          var xhr = new XMLHttpRequest();
          xhr.open('GET', '/network', true);
          xhr.onload = function() {
            var circle = document.getElementById('network-status');
            circle.style.backgroundColor = (xhr.responseText === 'ON') ? 'green' : 'red';
          };
          xhr.send();
        }

        setInterval(updateNetworkStatus, 2000); // Atualiza o estado da rede a cada 2s        

      </script>
      <style> 
        .status-circle {
          width: 50px;
          height: 50px;
          border-radius: 50%;
          display: inline-block;
        }
        .gpio-button {
          padding: 10px 20px;
          margin: 10px;
          border: none;
          cursor: pointer;
          color: white;
          font-size: 16px;
        } 
      </style>
    </head>
    <body>
      <h1>ESP8266 Web Server</h1>
      <button id="btn-4" class="gpio-button" data-pin="4" onclick="togglePin(4)" style="background-color: )rawliteral" + String(states[0] ? "green" : "red") + R"rawliteral(;">GPIO 4</button>
      <button id="btn-5" class="gpio-button" data-pin="5" onclick="togglePin(5)" style="background-color: )rawliteral" + String(states[1] ? "green" : "red") + R"rawliteral(;">GPIO 5</button>
      <br><br>
      <h3>Status da Rede:</h3>
      <div id="network-status" class="status-circle" style="background-color: )rawliteral" + String(digitalRead(12) ? "green" : "red") + R"rawliteral(;"></div>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

// Toggle GPIO
void handleToggle() {
  if (!server.hasArg("pin")) {
    server.send(400, "text/plain", "Missing 'pin' parameter!");
    return;
  }

  int pin = server.arg("pin").toInt();
  int index = (pin == 4) ? 0 : (pin == 5) ? 1 : -1;

  if (index == -1) {
    server.send(400, "text/plain", "Invalid pin number!");
    return;
  }

  states[index] = !states[index];  // Toggle state
  digitalWrite(pins[index], states[index] ? HIGH : LOW);

  server.send(200, "text/plain", states[index] ? "ON" : "OFF");
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

// Retorna status dos pinos
void handleStatus() {
  String status = "GPIO 4: " + String(states[0] ? "ON" : "OFF") + " | GPIO 5: " + String(states[1] ? "ON" : "OFF");
  server.send(200, "text/plain", status);
}

void handleNetworkStatus() {
  int networkState = digitalRead(12);
  server.send(200, "text/plain", networkState ? "ON" : "OFF");
}



