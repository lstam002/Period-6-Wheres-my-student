#include <SPI.h>
#include <RFID.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ss 10  // --
#define rst 9  // --

#define ce 7   // --
#define csn 6  // --

unsigned char tx[11];
unsigned char location[6] = { ' ', '-', ' ', 'H', '3', 'A' };  // building, floor, device #
const int address = 1;                                         // device # defines address: a = 1, b = 2, etc


RFID rfid(ss, rst);
RF24 radio(ce, csn);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  radio.begin();


  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(address);
  radio.stopListening();

}


void loop() {
  if (rfid.isCard()) {
    rfid.readCardSerial();

    for (int i = 0; i < 5; i++) {
      tx[i] = rfid.serNum[i];
    }  // records UID

    for (int j = 5; j < 11; j++) {
      tx[j] = location[j - 5];
    }  // adds location onto it

    radio.write(&tx, sizeof(tx));

    for (int i = 0; i < 5; i++) {
      Serial.print(tx[i], HEX);
    }  // prints UID (implies successful radio write)
    for (int j = 5; j < 11; j++) {
      Serial.print((char)tx[j]);
    }  // prints location

    Serial.println();
  }
  delay(1000);
}