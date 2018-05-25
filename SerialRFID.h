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

const char TAG_CHAR_STX = 2;
const char TAG_CHAR_CR = 13;
const char TAG_CHAR_LF = 10;
const char TAG_CHAR_ETX = 3;

// Each tag is 16 bytes but the last four are to be discarded.
const int LEN_TAG = 16;
const int LEN_ID = 13;
const int LEN_ID_PRINTABLE = 12;

class SerialRFID
{
public:
  SerialRFID(Stream &s) : serial(s){};
  static bool isEqualTag(char *nTag, char *oTag);

private:
  Stream &serial;
  void clearStream();
  static bool isPrintableTagChar(char theChar);
  static void findTagInBuffer(char *buf, int bufSize, char *newTag);
};

#endif