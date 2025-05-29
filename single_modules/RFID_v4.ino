#include <SPI.h>
#include <RFID.h>

#define ss 10
#define rst 9
#define databasesize 15;

RFID rfid(ss, rst);

class card {
  public:
    unsigned char UID[5];
    String location;
    String entry;
};

card database[15];
card detected_card;
int current_slot;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  current_slot = 0;
}

void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      record_to_detected();  // UID is stored to detected_card
      check_data();
      entry_or_exit();
      transfer_to_database(); // UID is transferred to database slot from detected_card
      printcard();
      current_slot = (current_slot + 1) % databasesize;
    }
    delay(1500);
  }
}

void record_to_detected() {
  for (int i = 0; i < 4; i++) {
    detected_card.UID[i] = rfid.serNum[i];
  }
}

void transfer_to_database() {
  for (int i = 0; i < 4; i++) {
    database[current_slot].UID[i] = detected_card.UID[i];
  }
  database[current_slot].location = detected_card.location;
  database[current_slot].entry = detected_card.entry;
}
void check_data() {
  for (int i = 0; i < 15; i++) {
    if (database[i].UID == detected_card.UID) {
      detected_card = database[i];
    }
  }
}

void printcard() {
  for (int i = 0; i < 4; i++) {
    Serial.print(database[current_slot].UID[i], HEX);
  }
  Serial.print(" ");
  Serial.print(database[current_slot].location);
  Serial.print(" - ");
  Serial.print(database[current_slot].entry);
  Serial.println();
  Serial.println();
}

void entry_or_exit() {
  detected_card.location = "H3F";
  if (detected_card.entry == "entry") {
    detected_card.entry = "exit";
  } else {
    detected_card.entry = "entry";
  }
}