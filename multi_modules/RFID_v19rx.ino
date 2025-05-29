#include <SPI.h>
#include <RFID.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <bits/basic_string.h>
#include <string>

#define ss 10  // --
#define rst 9  // --

#define ce 7   // --
#define csn 8  // --

const byte address[6] = {0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0};


RFID rfid(ss, rst);
RF24 radio(ce, csn);

void setup() {
  Serial.begin(9600);
  SPI.begin();

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}


void loop() {
  if (radio.available()) {
    String rx;
    radio.read(&rx, 16);
    Serial.print("Read: ");
    if (rx == "0") {
      Serial.print(rx);
    }
    Serial.println();
    rx = "0";
  }
}