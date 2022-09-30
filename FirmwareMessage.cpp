#include "WString.h"
#include "FirmwareMessage.h"
#include "HardwareSerial.h"

#include <string.h>

FirmwareMessage::FirmwareMessage()
{
  messageBuffer[0] = '$';
  messageBuffer[1] = '$';

  setMessageType(0).reset().updateMessageLength();
}

FirmwareMessage& FirmwareMessage::reset()
{
  bufferPosition = 4;

  return *this;
}

FirmwareMessage& FirmwareMessage::setMessageType(unsigned char messageType)
{
  memcpy(&messageBuffer + 3, &messageType, sizeof(char));

  return *this;
}
unsigned char FirmwareMessage::getMessageType()
{
  unsigned value = 0;

  memcpy(&value, &messageBuffer + 3, sizeof(char));

  return value;
}

unsigned char FirmwareMessage::getMessageLength()
{
  unsigned char value = 0;

  memcpy(&value, &messageBuffer + 2, sizeof(char));

  return value;
}

FirmwareMessage& FirmwareMessage::addUnsignedChar(unsigned char value)
{
  memcpy(&messageBuffer + bufferPosition, &value, sizeof(unsigned char));
  bufferPosition += sizeof(unsigned char);

  return updateMessageLength();
}
unsigned char FirmwareMessage::getUnsignedChar()
{
  unsigned char value = 0;

  memcpy(&value, &messageBuffer + bufferPosition, sizeof(unsigned char));
  bufferPosition += sizeof(unsigned char);

  return value;
}

FirmwareMessage& FirmwareMessage::addChar(char value)
{
  memcpy(&messageBuffer + bufferPosition, &value, sizeof(char));
  bufferPosition += sizeof(char);

  return updateMessageLength();
}
 char FirmwareMessage::getChar()
{
  char value = 0;

  memcpy(&value, &messageBuffer + bufferPosition, sizeof(char));
  bufferPosition += sizeof(char);

  return value;
}

FirmwareMessage& FirmwareMessage::addShort(short value)
{
  memcpy(&messageBuffer + bufferPosition, &value, sizeof(short));
  bufferPosition += sizeof(short);

  return updateMessageLength();
}
short FirmwareMessage::getShort()
{
  short value = 0;

  memcpy(&value, &messageBuffer + bufferPosition, sizeof(short));
  bufferPosition += sizeof(short);

  return value;
}

FirmwareMessage& FirmwareMessage::addInt(int value)
{
  memcpy(&messageBuffer + bufferPosition, &value, sizeof(int));
  bufferPosition += sizeof(int);

  return updateMessageLength();
}
int FirmwareMessage::getInt()
{
  int value = 0;

  memcpy(&value, &messageBuffer + bufferPosition, sizeof(int));
  bufferPosition += sizeof(int);

  return value;
}

FirmwareMessage& FirmwareMessage::addString(String value)
{
  unsigned char length = value.length();

  addUnsignedChar(length);
  memcpy(&messageBuffer + bufferPosition, value.c_str(), length);
  bufferPosition += length;

  return updateMessageLength();
}
String FirmwareMessage::getString()
{
  unsigned char length = getUnsignedChar();
  char* value = new char[length + 1];

  memcpy(value, &messageBuffer + bufferPosition, length);
  bufferPosition += length;

  value[length] = '\0';

  return String(value);
}

FirmwareMessage& FirmwareMessage::sendMessage()
{
  Serial.write(messageBuffer, getMessageLength() + 3);
  Serial.println();

  return *this;
}

FirmwareMessage& FirmwareMessage::updateMessageLength()
{
  bufferPosition -= 3;
  memcpy(&messageBuffer + 2, &bufferPosition, sizeof(char));
  bufferPosition += 3;

  return *this;
}