#include <SoftwareSerial.h>
#include <SerialRFID.h>

const byte RX_PIN = 10;
const byte TX_PIN = 11;

SoftwareSerial sSerial(RX_PIN, TX_PIN);
SerialRFID rfid(sSerial);

char matchTag[SIZE_TAG_ID] = "5C00CAC9633C";

void onTagCallback(char *tag)
{
  Serial.print("Tag match: ");
  Serial.println(tag);
}

void setup()
{
  Serial.begin(9600);
  sSerial.begin(9600);

  rfid.onTag(onTagCallback, matchTag);

  Serial.println(">> Starting SerialRFID callback example program");
}

void loop()
{
  rfid.run();
}