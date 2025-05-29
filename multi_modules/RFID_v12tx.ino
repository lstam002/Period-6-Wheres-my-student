#include <SPI.h>
#include <RFID.h>
#include <nRF24L01.h>
#include <RF24.h>

#define cs 10  // change depending on wiring
#define ss 10  // --
#define rst 9  // --

#define ce 6   // --
#define csn 5  // --

int i;
String tx;
String location = " - H3A"; // building, floor, device #
const int address = 1; // device # defines address: a = 1, b = 2, etc
unsigned char txUID[5];


RFID rfid(ss, rst);
RF24 radio(ce, csn);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();

  radio.openWritingPipe(address);
  radio.stopListening();
  i = 0;
}



void loop() {
  if (rfid.isCard()) {
    rfid.readCardSerial();
    for (i = 0; i < 5; i++) {
      tx[i] = rfid.serNum[i], HEX;
    }
    tx = tx + location;
    radio.write(&tx, sizeof(tx));
  }
}