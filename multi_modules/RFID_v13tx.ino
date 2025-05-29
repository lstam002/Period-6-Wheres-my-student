#include <SPI.h>
#include <RFID.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ss 10  // --
#define rst 9  // --

#define ce 6   // --
#define csn 5  // --

int i;
unsigned char tx[11];
unsigned char location[6] = {' ', '-', ' ', 'H', '3', 'A'}; // building, floor, device #
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
}



void loop() {
  if (rfid.isCard()) {
    rfid.readCardSerial();

    for (int i = 0; i < 5; i++) {
      txUID[i] = rfid.serNum[i];
      tx[i] = txUID[i];
    } // records UID

    for (int j = 5; j < 11; j++) {
      tx[j] = location[j - 5];
    } // adds location onto it

    radio.write(&tx, sizeof(tx));

    for (int i = 0; i < 5; i++) {
      Serial.print(tx[i], HEX);
    } // prints UID
    for (int i = 0; i < 6; i++) {
      Serial.print((char)tx[i + 5]);
    } // prints location

    Serial.println();
  }
  delay(1500);
}