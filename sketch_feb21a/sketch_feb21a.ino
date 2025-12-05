#include <dummy.h>

void setup() {
  Serial.begin(115200);   // Comunicação com PC
  Serial1.begin(115200);
  delay(30);

}

void loop() {
  Serial.println("Hello From ESP 35");
  
  // if (Serial.available()) {
  String command = Serial.readString();
  String command2 = Serial1.readString();
  String command3 = Serial.readStringUntil('\n');
  String command4 = Serial1.readStringUntil('\n');


  Serial1.println("Received: " + command);
  Serial.println("Received: " + command);

  Serial1.println("Received 2: " + command2);
  Serial.println("Received 2: " + command2);

  Serial1.println("Received 3: " + command3);
  Serial.println("Received 3: " + command3);

  Serial1.println("Received 4: " + command4);
  Serial.println("Received 4: " + command4);

  // }  
  
  Serial.println("");
  Serial1.println("");
  Serial.write("LED_ON");
  Serial.println("");
  Serial1.println("");
  Serial1.write("LED_ON");
  Serial.println("");
  Serial1.println("");
  Serial1.println("LED_ON");  // Envia comando para o Mega
  Serial.println("");
  Serial1.println("");
  Serial.println("LED_ON");
  
  delay(1500);
}
