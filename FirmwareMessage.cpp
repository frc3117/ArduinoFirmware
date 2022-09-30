#include "FirmwareMessage.h"
#include "HardwareSerial.h"

#include <string.h>

FirmwareMessage::FirmwareMessage()
{
  messageBuffer[0] = '$';
  messageBuffer[1] = '$';

  setMessageType(0).reset().updateMessageLenght();
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

unsigned char FirmwareMessage::getMessageLenght()
{
  unsigned char value = 0;

  memcpy(&value, &messageBuffer + 2, sizeof(char));

  return value;
}

FirmwareMessage& FirmwareMessage::addChar(char value)
{
  memcpy(&messageBuffer + bufferPosition, &value, sizeof(char));
  bufferPosition += sizeof(char);

  return updateMessageLenght();
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

  return updateMessageLenght();
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

  return updateMessageLenght();
}
int FirmwareMessage::getInt()
{
  int value = 0;

  memcpy(&value, &messageBuffer + bufferPosition, sizeof(int));
  bufferPosition += sizeof(int);

  return value;
}

FirmwareMessage& FirmwareMessage::sendMessage()
{
  Serial.write(messageBuffer, getMessageLenght() + 3);
  Serial.println();

  return *this;
}

FirmwareMessage& FirmwareMessage::updateMessageLenght()
{
  bufferPosition -= 3;
  memcpy(&messageBuffer + 2, &bufferPosition, sizeof(char));
  bufferPosition += 3;

  return *this;
}