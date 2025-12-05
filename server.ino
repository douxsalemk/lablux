
// void setup() {
//   Serial.begin(115200); 
//   // Serial3.begin(115200);  

//   // pinMode(13, OUTPUT);
//   pinMode(4, OUTPUT);
//   pinMode(5, OUTPUT);
//   // pinMode(6, OUTPUT);
//   while(!Serial){
//   }
//   // while(!Serial3){
//   // }

//   delay(30);
// }

// void loop() {
//   Serial.println("Hello From ARDUINO");
//   // if (!Serial3.available()) {
//     // String command = Serial.readStringUntil('\n');
//     String command = Serial.readString();
//     // String command2 = Serial3.readString();
//     String command3 = Serial.readStringUntil("\n");
//     // String command4 = Serial.readStringUntil("\n");

//     // Serial3.println("Received: " + command);
//     Serial.println("Received: " + command);

//     // Serial3.println("Received 2: " + command2);
//     // Serial.println("Received 2: " + command2);

//     // Serial3.println("Received 3: " + command3);
//     Serial.println("Received 3: " + command3);

//     // Serial3.println("Received 4: " + command4);
//     // Serial.println("Received 4: " + command4);

//     if (command == "LED_ON") {
//       digitalWrite(5, HIGH);
//     } 
//     if (command3 == "LED_ON") {
//       digitalWrite(5, HIGH);
//     } 
//     digitalWrite(6, HIGH);

//     // if (command2 == "LED_ON") {
//     //   digitalWrite(6, HIGH);
//     // } 

//     //   digitalWrite(5, LOW);
//   // }
//   // else {
//     // Serial.println("No data available on serial port.");
//   // }
//   digitalWrite(4, HIGH);
//   Serial.println("");
//   Serial.write("LED_ON");
//   Serial.println("");
//   Serial.println("LED_ON");
//   Serial.println("");
//   // Serial3.write("OI 3");
//   // Serial3.println("");
//   // Serial3.println("OI 3");
//   Serial.println("");

//   delay(1000);
// }

// Wifiduino . esp8266

// Quantidade de grupos/portas controladas.
const uint8_t NUM_PORTAS = 25;
// Mapa de pinos físicos associados a cada grupo (1..25). Ajuste conforme seu hardware.
uint8_t portaPins[NUM_PORTAS] = {
  4, 5, 6, 7, 8,
  9, 10, 11, 12, 13,
  22, 23, 24, 25, 26,
  27, 28, 29, 30, 31,
  32, 33, 34, 35, 36
};

String msg; // String para armazenar a mensagem recebida pela porta serial 3.

void setup() {
  //Defina o pino LED_BUILTIN (13), como saida.
  pinMode(LED_BUILTIN, OUTPUT);
  for (uint8_t i = 0; i < NUM_PORTAS; i++) {
    pinMode(portaPins[i], OUTPUT);
    digitalWrite(portaPins[i], LOW);
  }
  pinMode(3, INPUT);

  Serial.println("INICIALIANDO ");


  //Defina as porta serial para comunicação usb.
  Serial.begin(115200);
  //Defina as porta serial para comunicação com ESP8266.
  Serial3.begin(115200);
}

void loop() {
  //Aguarde dados vindos do ESP8266.
  if (Serial3.available()) {
    //Leitura de um byte.
    char data = Serial3.read();
    //Imprima o mesmo dado pela porta usb.
    Serial.print(data);
    //Acrescente o caractere recebido a string de mensagem.
    msg += data;

    if (data == '\r' || data == '\n') {
      // Tenta processar a mensagem completa
      int onPos = msg.indexOf("LED_ON_");
      int offPos = msg.indexOf("LED_OFF_");
      if (onPos >= 0) {
        int id = msg.substring(onPos + 7).toInt();
        if (id >= 1 && id <= NUM_PORTAS) {
          uint8_t pin = portaPins[id - 1];
          digitalWrite(pin, HIGH);
          if (pin == LED_BUILTIN) digitalWrite(LED_BUILTIN, HIGH);
        }
      } else if (offPos >= 0) {
        int id = msg.substring(offPos + 8).toInt();
        if (id >= 1 && id <= NUM_PORTAS) {
          uint8_t pin = portaPins[id - 1];
          digitalWrite(pin, LOW);
          if (pin == LED_BUILTIN) digitalWrite(LED_BUILTIN, LOW);
        }
      }
      msg = "";
    }
  }

  delay(50);
}


