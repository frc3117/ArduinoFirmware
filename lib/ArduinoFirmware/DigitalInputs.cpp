#include "DigitalInputs.h"
#include "Arduino.h"
#include "EEPROM.h"

void frc::DigitalInputs::init()
{
    EEPROM.get(DIGITAL_INPUTS_ADDRESS, _inputList.Buffer);

    for (auto input : _inputList.Inputs)
        pinMode(input.Pin, INPUT_PULLUP);
}
void frc::DigitalInputs::loop(frc::CAN* canDevice)
{
    auto now = millis();
    if (now - _lastSent >= DIGITAL_INPUTS_FREQUENCY)
    {
        _lastSent = now;

        auto packet = generatePacket();
        canDevice->WritePacket(packet.data, 8, 0);
    }
}

void frc::DigitalInputs::setInput(uint8_t id, uint8_t index, bool reversed)
{
    uint8_t offset_id = id + 1;

    auto input = _inputList.Inputs[index];
    if (input.Pin != offset_id || input.Reversed != reversed)
    {
        input.Pin = offset_id;
        input.Reversed = reversed;

        EEPROM.put(DIGITAL_INPUTS_ADDRESS, _inputList);
    }

    pinMode(id, INPUT_PULLUP);
}
void frc::DigitalInputs::clearInputs()
{
    for (auto input : _inputList.Inputs)
    {
        input.Pin = 0;
        input.Reversed = false;
    }

    EEPROM.put(DIGITAL_INPUTS_ADDRESS, _inputList);
}

frc::DigitalInputsPacket frc::DigitalInputs::generatePacket()
{
    frc::DigitalInputsPacket packet;

    for(int i = 0; i < DIGITAL_INPUTS_SIZE; i++)
    {
        auto input = _inputList.Inputs[i];

        boolean value;
        if (input.Pin == 0)
            value = false;
        else
            value = digitalRead(input.Pin - 1) != input.Reversed;

        packet.num |= value << i;
    }

    return packet;
}