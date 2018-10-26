#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <WiFiClient.h>
#include <ArduinoJson.h>

#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int temp = 0;
int humi = 0;

int TX = D7;
int RX = D8;
SoftwareSerial BTSerial(TX, RX);
String ssidString         = "";
String passwordString     = "";

char ssid[50];
char password[50];

const char* serverip = "www.dogfriends.site"; //GCP was서버 ip
const char* productSerial = "abcd1234";   //To-Do 제품키 사용할때 쓸 변수

String jsondata = ""; 
String result = "";
StaticJsonBuffer<200> jsonBuffer;
JsonObject & root = jsonBuffer.createObject();

WiFiClient client;

///////////////////////////////////////////////////////////////////////////////////////////////

void receiveWiFiData(){
  if(BTSerial.available() > 0){
    Serial.println("Waiting data from Bluetooth......");
    String receivedBTMessage = BTSerial.readString();
    Serial.println("receivedBTMessage : " + receivedBTMessage);

    int cutPoint       = receivedBTMessage.indexOf("\n");
    ssidString         = receivedBTMessage.substring(0, cutPoint);
    passwordString     = receivedBTMessage.substring(cutPoint+1);
    Serial.println("ssidString : " + ssidString);
    Serial.println("passwordString : " + passwordString);
    connectWiFi();
  }
}

void connectWiFi(){
  if(ssidString != ""){
    Serial.println("start connect WiFi......");
      
    ssidString.toCharArray(ssid, ssidString.length()+1);
    passwordString.toCharArray(password, passwordString.length());

    WiFi.begin(ssid, password);

    Serial.println("connecting......");
    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }

    Serial.println("WiFi Connect success!"); 
    Serial.print("IP Address is: ");
    Serial.println(WiFi.localIP());
  }
}

void checkTemp(){
  temp = dht.readTemperature();
  humi = dht.readHumidity();  

  sendTempToServer();
}

void sendTempToServer(){  
  root["temp"] = temp;
  root["humi"] = humi;

  root.printTo(jsondata);
//  Serial.println(jsondata);
  
  if(client.connect(serverip, 80)){
    //온습도 받는 페이지 get방식
    client.print("GET /settemphumi?temp="+(String)temp+"&humi="+(String)humi);
    client.print(" HTTP/1.1\r\n");
    client.print("Host: www.dogfriends.site\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Content-Length: ");
    client.println(jsondata.length());
    client.println();
    client.println(jsondata);
    client.println("\r\n\r\n");
  }
//  Serial.print("GET /settempHumi?temp="+(String)temp+"&humi="+(String)humi);  
  jsondata = ""; 
}
                                                                            
void receiveMessageFromServer(){  
  if(client.connect(serverip, 80)){
    String receiveURI = "/arduino/handle\r\n";
    client.print("GET " + receiveURI);
//    client.print("GET " + receiveURI + " HTTP/1.1\r\n" + "Host: " + serverip + "\r\n" + "Connection: close\r\n\r\n");
    while(client.available() == 0);
    while ( client.available() > 0 ) {
      char c = client.read();
      Serial.println(c);
    }
  }

  if (!client.connected()) {
    client.stop();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  dht.begin();  
  WiFi.disconnect();
}

void loop() {
//  receiveWiFiData();  
//  
//  while(WiFi.status() == WL_CONNECTED){
//    receiveMessageFromServer();     
//    checkTemp();
//  }
  char a = '1';
  Serial.println(a);
  delay(1000);     
}
