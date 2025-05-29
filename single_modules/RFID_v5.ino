#include <SPI.h>
#include <RFID.h>

#define ss 10 // change depending on wiring
#define rst 9 // change depending on wiring
#define tags_in_circulation 3 // tags in circulation
int databasesize = 3; // how many tags can be in one location
String setlocation = "H3F"; // building, floor number + F

RFID rfid(ss, rst);

class card {
  public:
    unsigned char UID[5];
    String location;
    String entry;
};

card database[tags_in_circulation];
card detected_card;
int current_slot;
int existing_slot;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  current_slot = 0;
  existing_slot = 0;
}

void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      record_to_detected();  // UID is stored to detected_card
      existing(); // if there is an entry in the database already, we know if its an exiting or entering tag
      printcard(); // print the card info, stored on detected_card
      transfer_to_database(); // UID is transferred to database slot from detected_card
      current_slot = (current_slot + 1) % databasesize;
    }
    delay(1500);
  }
}

void record_to_detected() {
  for (int i = 0; i < 4; i++) {
    detected_card.UID[i] = rfid.serNum[i];
  }
  detected_card.location = setlocation;
}

void existing() {
  for (int i = 0; i < databasesize; i++) {
    if (detected_card.UID == database[i].UID) {
      detected_card.entry = "exit";

      for (int j = 0; j < 4; j++) { // if there is an existing entry, it wipes that entry in the database and saves it in detected_card instead
        database[i].UID[j] = 0;
      }
      existing_slot = i;
    } else {
      detected_card.entry = "entry";
    }
  }
}

void printcard() {
  for (int i = 0; i < 4; i++) {
    Serial.print(detected_card.UID[i], HEX);
  }
  Serial.print(" ");
  Serial.print(detected_card.location);
  Serial.print(" - ");
  Serial.print(detected_card.entry);
  Serial.println(); Serial.println();
}

void transfer_to_database() {
  if (existing_slot == 0) {
    database[current_slot] = detected_card;
  }
}
