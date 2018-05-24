/*
  SerialRFID.h - Interact with ID-innovations RFID readers using serial
*/

#include "SerialRFID.h"

bool SerialRFID::isPrintableTagChar(char theChar)
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

bool SerialRFID::isEqualTag(char nTag[], char oTag[])
{
  if (strlen(nTag) != LEN_ID_PRINTABLE ||
      strlen(oTag) != LEN_ID_PRINTABLE)
  {
    return false;
  }

  for (int i = 0; i < LEN_ID; i++)
  {
    if (nTag[i] != oTag[i])
    {
      return false;
    }
  }

  return true;
}

void SerialRFID::findTagInBuffer(char buf[], int bufSize, char newTag[])
{
  memset(newTag, 0, LEN_ID);

  if (bufSize < LEN_TAG)
  {
    return;
  }

  int stxIdx = bufSize - LEN_TAG;

  if (buf[stxIdx] != TAG_CHAR_STX)
  {
    return;
  }

  int counter = 0;

  for (int i = stxIdx; i < bufSize; i++)
  {
    if (isPrintableTagChar(buf[i]))
    {
      // Check if we are reading more bytes than expected
      if (counter >= (LEN_ID - 1))
      {
        memset(newTag, 0, LEN_ID);
        return;
      }

      newTag[counter] = buf[i];
      counter++;
    }
  }

  // Check if the output array length is not the expected
  if (strlen(newTag) != LEN_ID_PRINTABLE)
  {
    memset(newTag, 0, LEN_ID);
  }
}