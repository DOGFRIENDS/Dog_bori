#include <SoftwareSerial.h>
SoftwareSerial BT05(12, 13); // RX, TX
void setup() {
  Serial.begin(9600);
  while (!Serial);
  BT05.begin(9600);
}

void loop() {
  if (BT05.available()) {
    Serial.write(BT05.read());
  }
  if (Serial.available()) {
    BT05.write(Serial.read());
  }
}

//참고 링크 : http://www.makeshare.org/bbs/board.php?bo_table=arduinocom&wr_id=28
