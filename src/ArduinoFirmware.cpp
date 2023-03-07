#include "Arduino.h"

#include "../lib/FRC-CAN-Arduino/frc_mcp2515.h"
#include "../lib/FRC-CAN-Arduino/frc_CAN.h"
#include "../lib/ArduinoFirmware/FirmwareBase.h"
#include "../lib/ArduinoFirmware/DigitalInputs.h"

#define PROGRAM_VERSION "1.0.0"
#define FIRMWARE_BAUDRATE 9600

#define CAN_CS 4
#define CAN_INTERRUPT 2

#define SEGMENT_0_MIN 8
#define SEGMENT_0_MAX 9
#define SEGMENT_1_MIN 3
#define SEGMENT_1_MAX 5
#define SEGMENT_2_MIN 6
#define SEGMENT_2_MAX 7

frc::MCP2515 mcp2515{CAN_CS};
frc::CAN frcCANDevice{0};

frc::DigitalInputs limitSwitches{};

FirmwareBase firmware(PROGRAM_VERSION, FIRMWARE_BAUDRATE);

void CANCallback(frc::CAN* can, int apiId, bool rtr, const frc::CANData& data)
{
    Serial.println(apiId, HEX);
}

void setup()
{
    firmware.init();

    auto err = mcp2515.reset();
    err = mcp2515.setBitrate(frc::CAN_1000KBPS, frc::CAN_CLOCK::MCP_16MHZ);
    err = mcp2515.setNormalMode();

    pinMode(CAN_INTERRUPT, INPUT);

    frc::CAN::SetCANImpl(&mcp2515, CAN_INTERRUPT, CANCallback, nullptr);
    frcCANDevice.AddToReadList();

    limitSwitches.addInput(SEGMENT_0_MIN);
    limitSwitches.addInput(SEGMENT_0_MAX);

    limitSwitches.addInput(SEGMENT_1_MIN);
    limitSwitches.addInput(SEGMENT_1_MAX);

    limitSwitches.addInput(SEGMENT_2_MIN);
    limitSwitches.addInput(SEGMENT_2_MAX);
}

unsigned long long lastSent = 0;

void loop() 
{
    firmware.loop();
    frc::CAN::Update();

    auto now = millis();
    if (now - lastSent > 20)
    {
        lastSent = now;

        auto packet = limitSwitches.generatePacket(false);
        frcCANDevice.WritePacket(packet.data, 8, 0);
    }
}