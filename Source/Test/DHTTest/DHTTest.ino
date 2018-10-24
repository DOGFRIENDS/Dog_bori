#include "DHT.h"

#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int temp;
int humi;

void setup() {
  Serial.begin(9600);    
  dht.begin();
}
void loop() {  
  humi = dht.readHumidity();
  temp = dht.readTemperature();

  if (isnan(humi) || isnan(temp) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print(temp); Serial.print(" *C, ");
  Serial.print(humi); Serial.println(" %");
  delay(2000);
}
