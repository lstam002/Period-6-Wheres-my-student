#include <SPI.h>
#include <RFID.h>

#define ss 10  // change depending on wiring
#define rst 9  // change depending on wiring

unsigned char txbuilding = 'H';  // block address 25
unsigned char txfloor = '3';     // block address 26
unsigned char txdevice = 'D';    // block address 27
unsigned char in = 'I';
unsigned char out = 'X';  // block address 28
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
  pinMode(6, OUTPUT);
}



void loop() {
  if (rfid.isCard()) {
    rfid.readCardSerial();

    readold();
    rfid.writeMFRC522(25, txbuilding);
    rfid.writeMFRC522(26, txfloor);
    rfid.writeMFRC522(27, txdevice);
    if (rxbuilding == txbuilding and rxfloor == txfloor and rxdevice == txdevice) {
      if (rxheading != in) {
        txheading = in;
      } else {
        txheading = out;
      }
    } else {
      txheading = in;
    }
    rfid.writeMFRC522(28, txheading);
    txheading = 0;
    readnew();
    tone(6, 2500, 750);
    delay(1500);

    for (int i = 0; i < 15; i++) {
      Serial.println();
    }
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
  Serial.println("-----------");
}

void readnew() {
  rxbuilding = rfid.readMFRC522(25);
  rxfloor = rfid.readMFRC522(26);
  rxdevice = rfid.readMFRC522(27);
  rxheading = rfid.readMFRC522(28);

  Serial.print("new signal: ");
  Serial.print((char)rxbuilding);
  Serial.print((char)rxfloor);
  Serial.print((char)rxdevice);
  Serial.println();

  Serial.print("heading: ");
  Serial.print((char)rxheading);


  Serial.println();
  Serial.println("----------------------------");
}