#include "FirmwareBase.h"

#define PROGRAM_VERSION "1.0.0"

FirmwareBase firmware(PROGRAM_VERSION);

void setup() 
{
  firmware.init();
}

void loop() 
{
  firmware.loop();
}
