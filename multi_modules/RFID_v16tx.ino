#include <SPI.h>
#include <RFID.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <bits/basic_string.h>

#define ss 10  // --
#define rst 9  // --

#define ce 7   // --
#define csn 6  // --

String tx; String location = " - H3A";
const int address = 1;        // device # defines address: a = 1, b = 2, etc
long double aux;

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
      tx = tx + String(rfid.serNum[i], HEX);
    }
    tx = tx + location;

    radio.write(&tx, sizeof(tx));

    Serial.println(tx);
  }
  delay(1000);
  tx = "";
}