#include <SPI.h>
#include <RFID.h>

#define ss 10
#define rst 9
 
RFID rfid(ss, rst);

class card {
  public:
    byte UID[4];
    String lastlocation;
    String inside;
};
card database[4];
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
      counter = (counter + 1) % 5;
    }
    delay(1500);
  }
}

void record() {
  for (int i = 0; i < 4; i++) {
    database[counter].UID[i] = rfid.serNum[i], HEX;
    if (database[counter].lastlocation[4] = 'I') {
      database[counter].lastlocation = "H3F-O";
    } else {
      database[counter].lastlocation = "H3F-I";
    }
  }
}

void printcard() {
  for (int x = 0; x < 4; x++) {
    Serial.print(database[counter].UID[x], HEX);
  }
  Serial.print (" ");
  Serial.print(database[counter].lastlocation);
  Serial.println();
  Serial.println();
}
