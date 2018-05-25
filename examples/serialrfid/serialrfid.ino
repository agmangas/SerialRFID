#include <SoftwareSerial.h>
#include <SerialRFID.h>

const byte RX_PIN = 10;
const byte TX_PIN = 11;

SoftwareSerial sSerial(RX_PIN, TX_PIN);
SerialRFID rfid(sSerial);

char newTag[LEN_TAG_ID + 1];
char matchTag[LEN_TAG_ID + 1] = "5C00CADB5A17";

void setup() {
  Serial.begin(9600);
  sSerial.begin(9600);

  Serial.println(">> Starting SerialRFID example program");
}

void loop() {
  if (rfid.readTag(newTag)) {
    Serial.print("Tag: ");
    Serial.print(newTag);

    if (SerialRFID::isEqualTag(newTag, matchTag)) {
      Serial.println(" / Match: OK");
    } else {
      Serial.println(" / Match: No");
    }
  }
}