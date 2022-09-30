#pragma once

#include "FirmwareMessage.h"

class FirmwareBase
{
  public:
    const char* FirmwareVersion = "1.0.0";
    
    char* ProgramVersion;
    int Baudrate;

    FirmwareMessage OutgoingMessage;

    FirmwareBase(const char* programVersion, const int baudrate);

    void init();
    void loop();

    void SendMessage(FirmwareMessage& message);
};