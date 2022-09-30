#include "FirmwareBase.h"

#define PROGRAM_VERSION "1.0.0"
#define FIRMWARE_BAUDRATE 9600

FirmwareBase firmware(PROGRAM_VERSION, FIRMWARE_BAUDRATE);

void setup()
{
  firmware.init();
}

void loop() 
{
  firmware.loop();
}