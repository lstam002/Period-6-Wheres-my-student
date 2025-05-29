#include <SPI.h>
#include <RFID.h>

#define ss 10
#define rst 9
 
RFID rfid(ss, rst);

class card {
  public:
    unsigned char UID[5];
    String location;
};
card database[10];
int counter;

void setup() { 
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  counter = 0;
}

void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      record();
      printcard();
      counter = (counter + 1) % 10;
    }
    delay(1500);
  }
}

void record() {
  for (int i = 0; i < 4; i++) {
    database[counter].UID[i] = rfid.serNum[i], HEX;
    for (int j = 0; j < 4; j++) {
      if (database[j].UID == rfid.serNum) {
        database[counter].location = "O-3HF";
      } else {
        database[counter].location = "I-3HF";
      }
    }
  }
}

void printcard() {
  for (int x = 0; x < 4; x++) {
    Serial.print(database[counter].UID[x], HEX);
  }
  Serial.print (" ");
  Serial.print(database[counter].location);
  Serial.println();
  Serial.println();
}
