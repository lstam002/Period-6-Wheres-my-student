#include <SPI.h>
#include <RFID.h>

#define ss 10  // change depending on wiring
#define rst 9  // change depending on wiring

unsigned char txbuilding = 'H';  // block address 5
unsigned char txfloor = '3';     // block address 6
unsigned char txdevice = 'A';    // block address 7
unsigned char in = 'i'; unsigned char out = 'o';  // block address 8
unsigned char txheading;

unsigned char rxbuilding;
unsigned char rxfloor;
unsigned char rxdevice;
unsigned char rxheading;

RFID rfid(ss, rst);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}



void loop() {
  if (rfid.isCard()) {
    rfid.readCardSerial();
    rfid.writeMFRC522(25, txbuilding);
    rfid.writeMFRC522(26, txfloor);
    rfid.writeMFRC522(27, txdevice);
    rfid.writeMFRC522(28, in);
    readold();
    delay(1500);
  }
}

void readold() {
  rxbuilding = rfid.readMFRC522(25);
  rxfloor = rfid.readMFRC522(26);
  rxdevice = rfid.readMFRC522(27);
  rxheading = rfid.readMFRC522(28);

  Serial.print("UID: ");
  for (int i = 0; i < 5; i++) {
    Serial.print(rfid.serNum[i]);
  }
  Serial.println();

  Serial.print("last signal: ");
  Serial.print((char)rxbuilding);
  Serial.print((char)rxfloor);
  Serial.print((char)rxdevice);
  Serial.println();

  Serial.print("heading: ");
  Serial.print((char)rxheading);

  Serial.println();
  Serial.println("-------------------------------");
}
