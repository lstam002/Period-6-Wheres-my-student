#include <SPI.h>
#include <RFID.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <bits/basic_string.h>

#define ss 10  // --
#define rst 9  // --

#define ce 7   // --
#define csn 8  // --

unsigned char tx[16]; unsigned char location[] = " - H3A";
const byte address[6] = {0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0};


RFID rfid(ss, rst);
RF24 radio(ce, csn);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop() {
  if (rfid.isCard()) {
    rfid.readCardSerial();


    for (int i = 0; i < 5; i++) {
      tx[i] = rfid.serNum[i], HEX;
    }
    for (int j = 6; j < 16; j++) {
      tx[j] = location[j - 6];
    }

    radio.write(&tx, sizeof(tx));

    for (int k = 0; k < 5; k++) {
      Serial.print(tx[k], HEX);
    }
    for (int l = 6; l < 16; l++) {
      Serial.print((char)tx[l]);
    }
    Serial.println();
    delay(100);
  }
}