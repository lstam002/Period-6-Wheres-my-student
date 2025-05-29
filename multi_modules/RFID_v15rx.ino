#include <SPI.h>
#include <RFID.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ss 10  // --
#define rst 9  // --

#define ce 7   // --
#define csn 6  // --

unsigned char rx[11];
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
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {

  radio.
  radio.read(&rx, sizeof(rx));

  for (int i = 0; i < 5; i++) {
    Serial.print(rx[i], HEX);
  }

  for (int j = 5; j < 11; j++) {
    Serial.print((char)rx[j]);
  }
  Serial.println();
}