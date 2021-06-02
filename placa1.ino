#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "NewPing.h"
#include "DHT.h"
#define DHT11TYPE DHT11



int DHT11PIN = D2;
int trigPin = D0;
int echoPin = D1;


NewPing sonar(trigPin, echoPin);
DHT dht11(DHT11PIN, DHT11TYPE);
String server = "";

//------ para conectar a internet

HTTPClient http;


const char* ssid     = "INFINITUMB(X^2)";
const char* password = "Gsg26#Ji$80A&16";



void setup() {
  Serial.begin(115200); // sets the serial port to 9600
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);

  //codigo
  dht11.begin();


}

void loop() {
  int echoTime = sonar.ping();
  float temperature = dht11.readTemperature();
  float humidity = dht11.readHumidity();
  float vsound = 331.3 + (0.606 * temperature) + (0.0124 * humidity);
  float distance = (echoTime / 2.0) * vsound / 10000;
  
float S_distancia= distance;
int S_temperature = temperature;
float S_humidity= humidity;

  Serial.print("distance: ");
  Serial.print(distance, 2);
  Serial.print(" cm");
  //S_distancia =distance;
  Serial.print("t Temperature: ");
  Serial.print(temperature);
  //S_temperature=temperature;

  Serial.print("t Humidity: ");
  Serial.println(humidity);
  //S_humidity = humidity;
  post(S_distancia,S_humidity,S_temperature);

  delay(1000);

}
void post(float S_distancia, int S_temperature, float S_humidity) {
  server = "http://144.202.17.134:5000/sensores";
  WiFiClient client;
  HTTPClient http;
  String json;
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["distancia"] = S_distancia;
  root["temperature"] = S_temperature;
  root["humidity"] = S_humidity;
  root.printTo(json);
  Serial.println(""); // salto de linea para http.writeToStream(&Serial);
  http.begin(client, server); //HTTP
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
}
