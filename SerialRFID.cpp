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

  for (int i = 0; i < LEN_TAG_ID; i++)
  {
    if (nTag[i] != oTag[i])
    {
      return false;
    }
  }

  return true;
}

bool SerialRFID::findTagInBuffer(char *buf, int bufSize, char *newTag)
{
  memset(newTag, 0, LEN_TAG_ID + 1);

  if (bufSize < LEN_TAG)
  {
    return false;
  }

  int stxIdx = bufSize - LEN_TAG;

  if (buf[stxIdx] != TAG_CHAR_STX)
  {
    return false;
  }

  int counter = 0;

  for (int i = stxIdx; i < bufSize; i++)
  {
    if (isTagIdChar(buf[i]))
    {
      // Check if we are reading more bytes than expected
      if (counter >= LEN_TAG_ID)
      {
        memset(newTag, 0, LEN_TAG_ID + 1);
        return false;
      }

      newTag[counter] = buf[i];
      counter++;
    }
  }

  // Check if the output array length is not the expected
  if (strlen(newTag) != LEN_TAG_ID)
  {
    memset(newTag, 0, LEN_TAG_ID + 1);
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

bool SerialRFID::readTag(char *newTag)
{
  if (stream.available() > 0 && stream.peek() != TAG_CHAR_STX)
  {
    clearStream();
  }

  if (stream.available() < LEN_TAG)
  {
    return false;
  }

  int bufSize = stream.available();
  char buf[bufSize];

  for (int i = 0; i < bufSize; i++)
  {
    buf[i] = stream.read();
  }

  return findTagInBuffer(buf, bufSize, newTag);
}