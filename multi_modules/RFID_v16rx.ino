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
const int address = 1; // device # defines address: a = 1, b = 2, etc

RFID rfid(ss, rst);
RF24 radio(ce, csn);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  radio.begin();


  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, address);
  radio.startListening();

}


void loop() {
  if (radio.available()) {
    radio.read(&rx, sizeof(rx));

    if (rx.length() == 16) {
      Serial.println(rx);
    }
  }
}