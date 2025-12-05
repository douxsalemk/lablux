void setup() {
  Serial.begin(115200);  // Inicia a comunicação serial
  delay(30);

  // Configuração de pinos de saída
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);

  // Configuração de pino de entrada (botão, sensor, etc.)
  pinMode(2, INPUT_PULLUP);

  // Inicializa os pinos de saída em HIGH
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);

  Serial.println("Configuração concluída!");
}

void loop() {
  Serial.println("Leitura dos GPIOs:");

  Serial.print("GPIO 4: "); Serial.println(digitalRead(4));
  Serial.print("GPIO 5: "); Serial.println(digitalRead(5));
  Serial.print("GPIO 12: "); Serial.println(digitalRead(12));
  Serial.print("GPIO 13: "); Serial.println(digitalRead(13));
  Serial.print("GPIO 14: "); Serial.println(digitalRead(14));
  Serial.print("GPIO 15: "); Serial.println(digitalRead(15));
  Serial.print("GPIO 16: "); Serial.println(digitalRead(16));

  Serial.print("GPIO 2 (INPUT): "); Serial.println(digitalRead(2)); // Exemplo de entrada

  Serial.println("---------------------");
  delay(2000); // Atualiza a cada 2 segundos
}
