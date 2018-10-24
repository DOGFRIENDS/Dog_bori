int FSR402_LED = 2; 
void setup() {
  // 센서값을 측정하기위해 시리얼통신을 준비합니다.
  Serial.begin(9600); 
}

void loop() {
  //아날로그 0번 핀에 압력센서를 연결합니다.
  int sensorval = analogRead(A0);
  // 0부터 1023의 센서값을 PWM 값 범위(0-255)로 변환 합니다.
  int brightness = map(sensorval, 0 , 1023, 0, 255);
  
  // 아나로그 입력을 통해 LED를 밝기를 조절합니다..
  analogWrite(FSR402_LED,brightness); 
  
  //시리얼 모니터를 통해 센서값과 LED의 밝기를 표기합니다. 
  Serial .println("Sensorvalue : " +String(sensorval) + ", LED Output : " + String(brightness));
  
  //100ms동안 대기합니다. 
  delay(500);
}
