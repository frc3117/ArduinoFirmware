#pragma once

#define MESSAGE_SIZE 256

class FirmwareMessage
{
  public:
    FirmwareMessage();

    FirmwareMessage& reset();

    FirmwareMessage& setMessageType(unsigned char messageType);
    unsigned char getMessageType();

    unsigned char getMessageLenght();

    FirmwareMessage& addChar(char value);
    char getChar();

    FirmwareMessage& addShort(short value);
    short getShort();

    FirmwareMessage& addInt(int value);
    int getInt();

    FirmwareMessage& sendMessage();

  private:
    FirmwareMessage& updateMessageLenght();

    unsigned char bufferPosition = 0;
    char messageBuffer[MESSAGE_SIZE];
};

/*
  $$: Start of message
  uint8: MessageLenght
  uint8: MessageType

  byte[sizeof(type)] : Param1
  byte[sizeof(type)] : Param2
  ...
*/