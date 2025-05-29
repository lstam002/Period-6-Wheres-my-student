#include <SPI.h>
#include <RFID.h>

#define ss 10 // change depending on wiring
#define rst 9 // change depending on wiring

unsigned char txlocation[3] = {'H', '3', 'A'}; unsigned char in[1] = {'I'}; unsigned char out[1] = {'P'};

unsigned char rxlocation[3]; unsigned char heading[1];

RFID rfid(ss, rst);
bool testing;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  testing = true;
}



void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfid.write(4, txlocation);
      rfid.write(7, in);
      readold();
    }
    delay(1500);
  }
}

void readold() {
  Serial.print("UID: ");
  for (int i = 0; i < 5; i++) {
    Serial.print(rfid.serNum[i]);
  }
  Serial.println();

  rfid.read(4, rxlocation);
  rfid.read(7, heading);
  
  Serial.print("last signal: ");
  for (int i = 0; i < 3; i++) {
    Serial.print(rxlocation[i]);
  }
  Serial.println();

  Serial.print("heading: ");
  Serial.print(heading[0]);

  Serial.println();
  Serial.println("-------------------------------");

}
