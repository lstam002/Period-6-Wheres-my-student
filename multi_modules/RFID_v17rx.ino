#include <SPI.h>
#include <RFID.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <bits/basic_string.h>

#define ss 10  // --
#define rst 9  // --

#define ce 7   // --
#define csn 6  // --

String rx;
const byte address[6] = "00001";

RFID rfid(ss, rst);
RF24 radio(ce, csn);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}


void loop() {
  if (radio.available()) {
    radio.read(&rx, sizeof(rx));
    Serial.println(rx);
  }
}