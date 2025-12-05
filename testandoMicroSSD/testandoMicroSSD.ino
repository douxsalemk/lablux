#include <Wire.h>
#include <RTClib.h>

#include <SPI.h>
#include <SD.h>

const int CS_PIN = 53; // Pode testar 10 ou 4 se necessário

RTC_DS3231 rtc;

unsigned long lastWriteTime = 0;
unsigned long lastReadTime = 0;
int counter = 1;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    // Inicializa RTC
    if (!rtc.begin()) {
        Serial.println("Erro: RTC não encontrado!");
        while (1);
    }

    Serial.println("Testando cartão SD...");

    if (!SD.begin(CS_PIN)) {
        Serial.println("Erro: Falha ao inicializar o cartão SD!");
        return;
    }

    Serial.println("Cartão SD detectado!");

    // Criar o arquivo CSV se não existir
    if (!SD.exists("data.csv")) {
        File file = SD.open("data.csv", FILE_WRITE);
        if (file) {
            file.println("Timestamp,Contador");
            file.close();
            Serial.println("Arquivo data.csv criado com cabeçalho!");
        } else {
            Serial.println("Erro ao criar data.csv!");
        }
    }
}

void loop() {
    unsigned long currentMillis = millis();

    // A cada 10 segundos, salva o tempo e o contador no CSV
    if (currentMillis - lastWriteTime >= 10000) {
        lastWriteTime = currentMillis;

        DateTime now = rtc.now();

        File file = SD.open("data.csv", FILE_WRITE);

        if (file) {
            file.print(millis() / 1000); // Tempo em segundos
            file.print(",");

            // Formato: YYYY-MM-DD HH:MM:SS
            file.print(now.year());
            file.print("-");
            file.print(now.month());
            file.print("-");
            file.print(now.day());
            file.print(" ");
            file.print(now.hour());
            file.print(":");
            file.print(now.minute());
            file.print(":");
            file.print(now.second());
            file.print(",");

            file.println(counter);
            file.close();
            Serial.print("Salvo: ");
            Serial.print(millis() / 1000);
            Serial.print(", ");
            Serial.println(counter);
            counter++; // Incrementa o contador
        } else {
            Serial.println("Erro ao escrever no data.csv!");
        }
    }

    // A cada 25 segundos, lê e imprime o conteúdo do CSV
    if (currentMillis - lastReadTime >= 25000) {
        lastReadTime = currentMillis;
        File file = SD.open("data.csv");
        if (file) {
            Serial.println("Conteúdo do data.csv:");
            while (file.available()) {
                Serial.write(file.read());
            }
            file.close();
            Serial.println("\n---- Fim do arquivo ----\n");
        } else {
            Serial.println("Erro ao abrir data.csv para leitura!");
        }
    }
}



// #include <SPI.h>
// #include <SD.h>

// const int CS_PIN = 53; // Tente mudar para 10 ou 4 se necessário

// void setup() {
//     Serial.begin(115200);
//     while (!Serial);

//     Serial.println("Testando cartão SD...");

//     if (!SD.begin(CS_PIN)) {
//         Serial.println("Erro: Falha ao inicializar o cartão SD!");
//         return;
//     }

//     Serial.println("Cartão SD detectado!");

//     File testFile = SD.open("test.txt", FILE_WRITE);
//     if (testFile) {
//         testFile.println("Teste de escrita no SD!");
//         testFile.close();
//         Serial.println("Arquivo test.txt criado com sucesso!");
//     } else {
//         Serial.println("Erro ao criar test.txt!");
//     }
// }

// void loop() {
// }




// #include <Wire.h>  // Biblioteca para comunicação I2C (caso necessário)
// #include <SPI.h>   // Biblioteca para comunicação SPI
// #include <SD.h>    // Biblioteca para manipulação do cartão SD


// void setup() {
//     Serial.begin(115200);
//     Wire.begin();  

//     Serial.print("Inicializando SD...");
//     pinMode(53, OUTPUT);

//     if (!SD.begin(53)) {
//         Serial.println(" Falha! Verifique as conexões.");
//         return;
//     }
//     Serial.println(" Cartão SD pronto!");

//     // Criar/Abrir arquivo para escrita
//     File CO2Data = SD.open("datalog.txt", FILE_WRITE);
//     if (!CO2Data) {
//         Serial.println("Erro ao criar datalog.txt!");
//         return;
//     }

//     // Escrevendo no SD
//     CO2Data.println("Teste de escrita no SD via ATmega2560");
//     CO2Data.close();
//     Serial.println("Dados gravados com sucesso!");

//     // Agora, verificamos se o arquivo realmente existe
//     if (SD.exists("datalog.txt")) {
//         Serial.println("Arquivo datalog.txt foi criado corretamente!");
//     } else {
//         Serial.println("Erro: O arquivo não foi criado!");
//     }
// }

// void loop() {
//     // Verificar se o arquivo está presente antes de tentar abrir
//     if (!SD.exists("datalog.txt")) {
//         Serial.println("Arquivo não encontrado!");
//         return;
//     }

//     // Abrir arquivo para leitura
//     File CO2Data = SD.open("datalog.txt");
//     if (CO2Data) {
//         Serial.println("Conteúdo do datalog.txt:");
//         while (CO2Data.available()) {
//             Serial.write(CO2Data.read());
//         }
//         CO2Data.close();
//     } else {
//         Serial.println("Erro ao abrir o arquivo para leitura!");
//     }

//     delay(5000); // Espera 5 segundos antes da próxima leitura
// }









// #include <SPI.h>
// #include <SD.h>

// #define CS_PIN 15  // GPIO15 (D8), altere se necessário

// void setup() {
//     Serial.begin(115200);
//     while (!Serial);

//     Serial.print("Inicializando o cartão SD...");
//     if (!SD.begin(CS_PIN)) {
//         Serial.println(" Falha! Verifique as conexões.");
//         return;
//     }
//     Serial.println(" OK!");

//     // Escrever no arquivo
//     File logFile = SD.open("/log.csv", FILE_WRITE);
//     if (logFile) {
//         logFile.println("Teste de escrita no microSD via ESP8266");
//         logFile.close();
//         Serial.println("Dados gravados no log.csv!");
//     } else {
//         Serial.println("Erro ao abrir o log.csv!");
//     }

//     // Ler o arquivo
//     logFile = SD.open("/log.csv");
//     if (logFile) {
//         Serial.println("Conteúdo do log.csv:");
//         while (logFile.available()) {
//             Serial.write(logFile.read());
//         }
//         logFile.close();
//     } else {
//         Serial.println("Erro ao abrir o arquivo para leitura!");
//     }
// }

// void loop() {
//     // Nada aqui, pois a escrita/leitura ocorre no setup()
// }
