#include <SPI.h>
#include <RFID.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <bits/basic_string.h>

#define ss 10  // --
#define rst 9  // --

#define ce 7   // --
#define csn 8  // --

String tx; String location = " - H3A";
const byte address[6] = {0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0};


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
  if (rfid.isCard()) {
    rfid.readCardSerial();


    for (int i = 0; i < 5; i++) {
      tx += String(rfid.serNum[i], HEX);
    }
    tx = tx + location;
    tx.toUpperCase();

    radio.write(&tx, tx.length());

    Serial.println(tx);
  }
  delay(750);
  tx = "";
}