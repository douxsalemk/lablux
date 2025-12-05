
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

String msg;//String para armazenar a mensagem recebida pela porta serial 3.

void setup() {
  //Defina o pino LED_BUILTIN (13), como saida.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
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

    if (data == 13) {//Limpa a string ao receber caractere CR(Carriage return).
      msg = "";
    }

    if (msg.indexOf("LED_ON_4") > 0) {//Verifica a ocorrencia do trecho "LED_ON" na mensagem recebida.
      //Ative a saida.
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(4, HIGH);
    }
    if (msg.indexOf("LED_OFF_4")> 0) {//Verifica a ocorrencia do trecho "LED_OFF" na mensagem recebida.
      //Desligue a saida.
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(4, LOW);
    } 

    if (msg.indexOf("LED_ON_5") > 0) {//Verifica a ocorrencia do trecho "LED_ON" na mensagem recebida.
      //Ative a saida.
      digitalWrite(5, HIGH);

    }
    if (msg.indexOf("LED_OFF_5")> 0) {//Verifica a ocorrencia do trecho "LED_OFF" na mensagem recebida.
      //Desligue a saida.
      digitalWrite(5, LOW);
    }    
   
    if (msg.indexOf("LED_ON_6") > 0) {//Verifica a ocorrencia do trecho "LED_ON" na mensagem recebida.
      //Ative a saida.
      digitalWrite(6, HIGH);

    }
    if (msg.indexOf("LED_OFF_6")> 0) {//Verifica a ocorrencia do trecho "LED_OFF" na mensagem recebida.
      //Desligue a saida.
      digitalWrite(6, LOW);
    }    


    if (msg.indexOf("LED_ON_7") > 0) {//Verifica a ocorrencia do trecho "LED_ON" na mensagem recebida.
      //Ative a saida.
      digitalWrite(7, HIGH);

    }
    if (msg.indexOf("LED_OFF_7")> 0) {//Verifica a ocorrencia do trecho "LED_OFF" na mensagem recebida.
      //Desligue a saida.
      digitalWrite(7, LOW);
    }    


    if (msg.indexOf("LED_ON_8") > 0) {//Verifica a ocorrencia do trecho "LED_ON" na mensagem recebida.
      //Ative a saida.
      digitalWrite(8, HIGH);

    }
    if (msg.indexOf("LED_OFF_8")> 0) {//Verifica a ocorrencia do trecho "LED_OFF" na mensagem recebida.
      //Desligue a saida.
      digitalWrite(8, LOW);
    }    


    if (msg.indexOf("LED_ON_9") > 0) {//Verifica a ocorrencia do trecho "LED_ON" na mensagem recebida.
      //Ative a saida.
      digitalWrite(9, HIGH);

    }
    if (msg.indexOf("LED_OFF_9")> 0) {//Verifica a ocorrencia do trecho "LED_OFF" na mensagem recebida.
      //Desligue a saida.
      digitalWrite(9, LOW);
    }    


    if (msg.indexOf("LED_ON_10") > 0) {//Verifica a ocorrencia do trecho "LED_ON" na mensagem recebida.
      //Ative a saida.
      digitalWrite(10, HIGH);

    }
    if (msg.indexOf("LED_OFF_10")> 0) {//Verifica a ocorrencia do trecho "LED_OFF" na mensagem recebida.
      //Desligue a saida.
      digitalWrite(10, LOW);
    }    

    if (msg.indexOf("LED_ON_11") > 0) {//Verifica a ocorrencia do trecho "LED_ON" na mensagem recebida.
      //Ative a saida.
      digitalWrite(11, HIGH);

    }
    if (msg.indexOf("LED_OFF_11")> 0) {//Verifica a ocorrencia do trecho "LED_OFF" na mensagem recebida.
      //Desligue a saida.
      digitalWrite(11, LOW);
    }    
  }

  delay(50);
}


