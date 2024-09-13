#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "SEU_SSID";       // Substitua pelo nome da rede Wi-Fi
const char* password = "SUA_SENHA";  // Substitua pela senha da rede Wi-Fi
const char* serverUrl = "http://SEU_SERVIDOR:5000";  // URL do servidor Python

const int ledPin = 2;  // Pino onde o LED está conectado

void setup() {
  Serial.begin(115200);

  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Conectando ao WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Tentando conectar...");
  }

  Serial.println("Conectado ao WiFi!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Definir pino do LED como saída
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // LED começa desligado
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Requisição ao servidor para buscar os comandos
    String url = String(serverUrl) + "/comandos";
    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Resposta do servidor:");
      Serial.println(response);

      // Processa a resposta JSON
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, response);

      if (!error) {
        JsonArray comandos = doc["comandos"];

        // Loop pelos comandos e agir conforme a ação
        for (JsonObject comando : comandos) {
          const char* acao = comando["acao"];

          if (strcmp(acao, "ligar") == 0) {
            digitalWrite(ledPin, HIGH);  // Liga o LED
            Serial.println("LED Ligado");

            // Notifica o servidor sobre o estado do LED
            HTTPClient ledRequest;
            String ledUrl = String(serverUrl) + "/led/ligar";
            ledRequest.begin(ledUrl);
            ledRequest.POST("");
            ledRequest.end();
          } 
          else if (strcmp(acao, "desligar") == 0) {
            digitalWrite(ledPin, LOW);   // Desliga o LED
            Serial.println("LED Desligado");

            // Notifica o servidor sobre o estado do LED
            HTTPClient ledRequest;
            String ledUrl = String(serverUrl) + "/led/desligar";
            ledRequest.begin(ledUrl);
            ledRequest.POST("");
            ledRequest.end();
          } 
          else if (strcmp(acao, "verificar") == 0) {
            Serial.println("Verificando estado do LED...");
            if (digitalRead(ledPin) == HIGH) {
              Serial.println("LED está ligado");
            } else {
              Serial.println("LED está desligado");
            }
          }
        }
      } else {
        Serial.println("Erro ao processar JSON");
      }
    } else {
      Serial.print("Erro na requisição: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }

  delay(5000); // Aguardar antes de buscar novos comandos
}
