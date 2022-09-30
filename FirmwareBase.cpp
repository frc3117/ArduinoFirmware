#include "HardwareSerial.h"
#include "FirmwareBase.h"

FirmwareBase::FirmwareBase(const char* programVersion, const int baudrate)
{
  ProgramVersion = programVersion;
  Baudrate = baudrate;
}

void FirmwareBase::init()
{
  Serial.begin(Baudrate);
}
void FirmwareBase::loop() {}