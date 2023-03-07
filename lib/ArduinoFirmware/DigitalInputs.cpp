#include "DigitalInputs.h"
#include "Arduino.h"

void frc::DigitalInputs::addInput(int id)
{
    pinMode(id, INPUT_PULLUP);
    _inputs[_inputsCount++] = id;
}

void frc::DigitalInputs::clearInputs()
{
    _inputsCount = 0;
}

frc::DigitalInputsPacket frc::DigitalInputs::generatePacket(bool reversed)
{
    frc::DigitalInputsPacket packet{0};

    for(int i = 0; i < _inputsCount; i++)
    {
        packet.num |= (digitalRead(_inputs[i]) != reversed) << i;
    }

    return packet;
}