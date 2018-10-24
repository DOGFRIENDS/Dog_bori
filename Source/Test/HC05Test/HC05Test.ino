#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3);   //bluetooth module Tx:Digital 2 Rx:Digital 3

void setup() {
  pinMode(8, OUTPUT);    //HC-05
  digitalWrite(8,HIGH);
  
  Serial.begin(9600);
  BTSerial.begin(38400);
  Serial.println("ATcommand");  //ATcommand Start
}

void loop() {
  if (BTSerial.available())
    Serial.write(BTSerial.read());
  if (Serial.available())
    BTSerial.write(Serial.read());
}

//참고 링크 : https://kocoafab.cc/tutorial/view/619
//참고 링크 : http://www.linotux.ch/arduino/HC-0305_serial_module_AT_commamd_set_201104_revised.pdf
