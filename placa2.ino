#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

String server = "";

//------ para conectar a internet

HTTPClient http;


const char* ssid     = "INFINITUMB(X^2)";
const char* password = "Gsg26#Ji$80A&16";
int inputPinuno = 5; //D1 izquierda
int inputPincero = 16; //D0 derecha
const int sensorPin = D2;

int valor1 = LOW;
int valor2 = LOW;

 String estado= "";


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
  pinMode(inputPinuno, INPUT);
  pinMode(inputPincero, INPUT);
  pinMode(sensorPin , INPUT);  //definir pin como entrada
}
 
void loop(){
  int value = 0;
  int valor = 0;
  int movimiento;
  value = digitalRead(sensorPin );  //lectura digital de pin
 
if(value == HIGH) {
    valor = 1;
    movimiento = valor;
   
    Serial.println("1");
  }
   valor1 = digitalRead(inputPinuno);  //lectura digital de pin
 valor2 = digitalRead(inputPincero);  //lectura digital de pin
// Serial.println(valor1);
 //Serial.println(valor2);
 if(valor1 == HIGH && valor2 == LOW){
  estado = "2";

  Serial.println("v2");
  post(movimiento,estado);
 }
 else
   if(valor2 == HIGH && valor1 == LOW){
    estado = "1";

    Serial.println("v1");
post(movimiento,estado);
 }
 else
 if(valor1==LOW && valor2 == LOW)
 {
  estado = "0";
post(movimiento,estado);
  Serial.println("v0");

 }
  
  delay(1000);
}
void post(int movimiento,String estado) {
  server = "http://144.202.17.134:5000/sensores";
  WiFiClient client;
  HTTPClient http;
  String json;
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["estado"] = estado;
  root["movimiento"] = movimiento;
  root.printTo(json);
  Serial.println(""); // salto de linea para http.writeToStream(&Serial);
  http.begin(client, server); //HTTP
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
}
