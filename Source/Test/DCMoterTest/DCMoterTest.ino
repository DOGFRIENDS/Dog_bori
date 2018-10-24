//왼쪽 바퀴
int Lin1 = 8;
int Lin2 = 7;
int LENA = 11;

//오른쪽 바퀴
int Rin1 = 6;
int Rin2 = 5;
int RENA = 3;

void setup() {
  // set up serial port
  Serial.begin(9600); 

  // set all the motor pins OUTPUT mode
  pinMode(LENA, OUTPUT);
  pinMode(Lin1, OUTPUT);
  pinMode(Lin2, OUTPUT);
  pinMode(RENA, OUTPUT);
  pinMode(Rin1, OUTPUT);
  pinMode(Rin2, OUTPUT);

  // wait 2 seconds after power up
  delay(2000);

}

void loop() {
  
  // set motors to move forward 
  pinMode(Lin1, HIGH);
  pinMode(Lin2, LOW);
  pinMode(Rin1, HIGH);
  pinMode(Rin2, LOW);  
  
  for (int pwm = 200; pwm <= 255; pwm++) {
    Serial.println(pwm);
    analogWrite(LENA, pwm);
    analogWrite(RENA, pwm);
    delay(100);
  }

  // set motors to move backward
  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, HIGH);
  digitalWrite(Rin1, LOW);
  digitalWrite(Rin2, HIGH);
 
  for (int pwm = 200; pwm <= 255; pwm++) {
    Serial.println(pwm);
    analogWrite(LENA, pwm);
    analogWrite(RENA, pwm);
    delay(100);
  }

  // stop motors
  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, LOW);
  digitalWrite(Rin1, LOW);
  digitalWrite(Rin2, LOW);
}
