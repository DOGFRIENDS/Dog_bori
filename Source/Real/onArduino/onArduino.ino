#include <SoftwareSerial.h>
//왼쪽 바퀴
int Lin1 = 8;
int Lin2 = 7;
int LENA = 11;
//오른쪽 바퀴
int Rin1 = 6;
int Rin2 = 5;
int RENA = 3;

char Mode;

int TrigPin = 12; //회색
int EchoPin = 13; //보라색

boolean driving = true;

float distance, duration;

char OldMode;

void AutoDrive(){
  driving = true;
  while(driving){
    if(driving = false){
      Stop();
    }
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    
    duration = pulseIn(EchoPin, HIGH);  //갔다오는 시간을 구함
    distance = (duration * 34000)/1000000/2;
    Serial.println("거리 : " + String(distance) + "cm");
    delay(500);
    
    if (distance >= 20) {
      Go();
    } else if (distance < 20) {
      Back();
      delay(3000);
      TurnLeft();
      delay(3000);
    }
  }
}

void TurnLeft(){
  driving = true;
  while(driving){
    if(driving = false){
      Stop();
    }
    //왼쪽바퀴는 정지한 상태에서 오른쪽바퀴만 돌면됨
    digitalWrite(8, 0);   
    digitalWrite(7, 0);   
  
    digitalWrite(6, 1);
    digitalWrite(5, 0);   
    analogWrite(3, 255);
  }
}

void Go(){
  driving = true;
  while(driving){
    if(driving = false){
      Stop();
    }
    digitalWrite(8, 1);   
    digitalWrite(7, 0);   
    analogWrite(11, 255);
  
    digitalWrite(6, 1);
    digitalWrite(5, 0);   
    analogWrite(3, 255);    
  }
}

void Back(){
  driving = true;
  while(driving){
    if(driving = false){
      Stop();
    }
    digitalWrite(8, 0);   
    digitalWrite(7, 1);   
    analogWrite(11, 255);
  
    digitalWrite(6, 0);
    digitalWrite(5, 1);   
    analogWrite(3, 255);    
  }
}

void Left(){
  if(OldMode == '3'){
    driving = true;
    while(driving){
      if(driving = false){
        Stop();
      }
      digitalWrite(8, 0);   
      digitalWrite(7, 0);   
    
      digitalWrite(6, 1);
      digitalWrite(5, 0);   
      analogWrite(3, 255);    
    }
  }else if(OldMode == '4'){
    driving = true;
    while(driving){
      if(driving = false){
        Stop();
      }
      digitalWrite(8, 0);   
      digitalWrite(7, 0);  

      digitalWrite(6, 0);
      digitalWrite(5, 1);   
      analogWrite(3, 255);    
    }
  }
}

void Right(){
  if(OldMode == '3'){
    driving = true;
    while(driving){
      if(driving = false){
        Stop();
      }
      digitalWrite(8, 1);   
      digitalWrite(7, 0);   
      analogWrite(11, 255);
    
      digitalWrite(6, 0);
      digitalWrite(5, 0);   
    }    
  }else if(OldMode == '4'){
    driving = true;
    while(driving){
      if(driving = false){
        Stop();
      }
      digitalWrite(8, 0);   
      digitalWrite(7, 1);   
      analogWrite(11, 255);
    
      digitalWrite(6, 0);
      digitalWrite(5, 0);   
    }
  }
}

void Stop(){
  driving = false;
  
  digitalWrite(8, 0);   
  digitalWrite(7, 0);   

  digitalWrite(6, 0);
  digitalWrite(5, 0);   
}

void setup() {
  Serial.begin(9600);
  pinMode(Lin1, OUTPUT);
  pinMode(Lin2, OUTPUT);
  pinMode(LENA, OUTPUT);
  pinMode(Rin1, OUTPUT);
  pinMode(Rin2, OUTPUT);
  pinMode(RENA, OUTPUT);

  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}
 
void loop(){
  if(Serial.available()){
    Mode = Serial.read();
    switch(Mode){
      case '0':
        Stop();
        break;
      case '1':
        AutoDrive();
        break;
      case '3':
        Go();
        OldMode = Mode;
        break;
      case '4':
        Back();
        OldMode = Mode;
        break;
      case '5':
        Left();
        break;
      case '6':
        Right();
        break;
    }
  }
}
