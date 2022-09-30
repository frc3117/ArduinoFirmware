#include "WString.h"
#pragma once

#define MESSAGE_SIZE 256

class FirmwareMessage
{
  public:
    FirmwareMessage();

    FirmwareMessage& reset();

    FirmwareMessage& setMessageType(unsigned char messageType);
    unsigned char getMessageType();

    unsigned char getMessageLength();

    FirmwareMessage& addUnsignedChar(unsigned char value);
    unsigned char getUnsignedChar();

    FirmwareMessage& addChar(char value);
    char getChar();

    FirmwareMessage& addShort(short value);
    short getShort();

    FirmwareMessage& addInt(int value);
    int getInt();

    FirmwareMessage& addString(String value);
    String getString();

    FirmwareMessage& sendMessage();

  private:
    FirmwareMessage& updateMessageLength();

    unsigned char bufferPosition = 0;
    unsigned char messageBuffer[MESSAGE_SIZE];
};

/*
  $$: Start of message
  uint8: MessageLength
  uint8: MessageType

  byte[sizeof(type)] : Param1
  byte[sizeof(type)] : Param2
  ...
*/