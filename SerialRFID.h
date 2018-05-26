/*
  SerialRFID.h - Interact with ID-innovations RFID readers using serial
*/

#ifndef SERIAL_RFID
#define SERIAL_RFID

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Chars that appear in a tag but are not part of the tag ID
const char TAG_CHAR_STX = 2;
const char TAG_CHAR_CR = 13;
const char TAG_CHAR_LF = 10;
const char TAG_CHAR_ETX = 3;

// Each tag is 16 bytes but the last 4 do not
// contain any useful data and can be discarded
const int SIZE_TAG = 16;
const int LEN_TAG_ID = 12;
// Size of a C-style string ('\0' terminated) to contain a tag ID
const int SIZE_TAG_ID = 13;

class SerialRFID
{
public:
  SerialRFID(Stream &s) : stream(s){};
  static bool isEqualTag(char *nTag, char *oTag);
  bool readTag(char *tag, int tagSize);

private:
  Stream &stream;
  static bool isTagIdChar(char theChar);
  static bool findTagInBuffer(char *buf, int bufSize, char *tag, int tagSize);
  void clearStream();
};

#endif