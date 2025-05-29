#include <SPI.h>
#include <RFID.h>

#define ss 10
#define rst 9
 
RFID rfid(ss, rst);

// Init array that will store new NUID 
byte nuidPICC[4];

void setup() { 
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      Serial.print("The card's number is  : ");
      Serial.print(rfid.serNum[0],HEX);
      Serial.print(rfid.serNum[1],HEX);
      Serial.print(rfid.serNum[2],HEX);
      Serial.print(rfid.serNum[3],HEX);
      Serial.print(rfid.serNum[4],HEX);
      Serial.println(" ");
    }
  }
}
