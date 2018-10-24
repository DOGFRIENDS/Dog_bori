#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

int temp = 23;
int humi = 10;

//--------------------Json 인코딩----------------
  String jsondata = ""; //Json을 담을 곳
  String result = "";

  char* ssid = "tjoeun604";
  char* password = "029381119";
  char* serverip = "192.168.0.83";

  // Json변환에 필요한 버퍼 용량은 200
  StaticJsonBuffer<200> jsonBuffer;
  WiFiClient client;

  // Json형식을 만들어 낼 수 있는객체를 선언한다.
  JsonObject & root = jsonBuffer.createObject();

void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting");

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

Serial.println("success!");
Serial.print("IP Address is: ");
Serial.println(WiFi.localIP());
}

void loop() {
 root["temp"] = temp;
 root["humi"] = humi;

 root.printTo(jsondata);

  SendTemp();
  jsondata = "";
}

void SendTemp(){
  if(client.connect(serverip, 8080)){
    //온습도 받는 페이지 get방식
    client.print("POST /setTempHumi");
    client.print(" HTTP/1.1\r\n");
    client.print("Host: 192.168.0.83:8080\r\n");
    client.print("Content-Type:application/json\r\n");
    client.print("Content-Length: ");
    client.println(jsondata.length());
    client.println();
    client.println(jsondata);
    client.println("\r\n\r\n");
  }
}
