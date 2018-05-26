#include <SoftwareSerial.h>
#include <SerialRFID.h>

const byte RX_PIN = 10;
const byte TX_PIN = 11;

SoftwareSerial sSerial(RX_PIN, TX_PIN);
SerialRFID rfid(sSerial);

char tag[SIZE_TAG_ID];
char matchTag[SIZE_TAG_ID] = "5C00CADB5A17";

void setup()
{
  Serial.begin(9600);
  sSerial.begin(9600);

  Serial.println(">> Starting SerialRFID example program");
}

void loop()
{
  if (rfid.readTag(tag, sizeof(tag)))
  {
    Serial.print("Tag: ");
    Serial.print(tag);

    if (SerialRFID::isEqualTag(tag, matchTag))
    {
      Serial.println(" / Match: OK");
    }
    else
    {
      Serial.println(" / Match: No");
    }
  }
}