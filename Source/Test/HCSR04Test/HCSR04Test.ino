int TrigPin = 8; //회색
int EchoPin = 9; //보라

void setup(){
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  Serial.begin(9600);
  
}

void loop(){
  float distance, duration;   //거리, 시간
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH);  //갔다오는 시간을 구함
  //Serial.println("시간 : " + String(duration));
  //delay(500);

  //시간 = 거리/속도
  //거리 = 속도*시간
  //속도 = 거리/시간
  
  //공기가 1초에 340m를 가는데 아래에서 cm로 변환했으니까 거기다 100을 곱해
  //34000이란 수치가 나온다. 
  //거기에 마이크로초(센서가 음파를 주고받는 속도의 단위)로 나눠주고,
  //왕복된 거리이기때문에 /2를 한다.  
  distance = (duration * 34000)/1000000/2;
  Serial.println("거리 : " + String(distance) + "cm");
  delay(500);
}
