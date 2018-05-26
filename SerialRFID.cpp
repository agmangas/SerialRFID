/*
  SerialRFID.h - Interact with ID-innovations RFID readers using serial
*/

#include "SerialRFID.h"

bool SerialRFID::isTagIdChar(char theChar)
{
  if (theChar != TAG_CHAR_STX &&
      theChar != TAG_CHAR_CR &&
      theChar != TAG_CHAR_LF &&
      theChar != TAG_CHAR_ETX)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool SerialRFID::isEqualTag(char *nTag, char *oTag)
{
  if (strlen(nTag) != LEN_TAG_ID ||
      strlen(oTag) != LEN_TAG_ID)
  {
    return false;
  }

  return strcmp(nTag, oTag) == 0;
}

bool SerialRFID::findTagInBuffer(char *buf, int bufSize, char *tag, int tagSize)
{
  if (tagSize < SIZE_TAG_ID || bufSize < SIZE_TAG)
  {
    return false;
  }

  memset(tag, 0, tagSize);

  int stxIdx = bufSize - SIZE_TAG;

  if (buf[stxIdx] != TAG_CHAR_STX)
  {
    return false;
  }

  int counter = 0;

  for (int i = stxIdx; i < bufSize; i++)
  {
    if (isTagIdChar(buf[i]))
    {
      // Check if we are reading more bytes than we should
      if (counter >= LEN_TAG_ID)
      {
        return false;
      }

      tag[counter++] = buf[i];
    }
  }

  // Check if the output array length is not the expected
  if (strlen(tag) != LEN_TAG_ID)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void SerialRFID::clearStream()
{
  while (stream.available())
  {
    stream.read();
  }
}

bool SerialRFID::readTag(char *tag, int tagSize)
{
  if (tagSize < SIZE_TAG_ID)
  {
    return false;
  }

  if (stream.available() > 0 && stream.peek() != TAG_CHAR_STX)
  {
    clearStream();
  }

  if (stream.available() < SIZE_TAG)
  {
    return false;
  }

  int bufSize = stream.available();
  char buf[bufSize];

  for (int i = 0; i < bufSize; i++)
  {
    buf[i] = stream.read();
  }

  return findTagInBuffer(buf, bufSize, tag, tagSize);
}