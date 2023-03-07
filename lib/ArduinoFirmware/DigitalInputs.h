#pragma once

#include "stdint.h"

namespace frc
{
    typedef union
    {
        uint64_t num;
        uint8_t data[8];
    } DigitalInputsPacket;

    class DigitalInputs
    {
    public:
        void addInput(int id);
        void clearInputs();

        DigitalInputsPacket generatePacket(bool reversed);

    private:
        uint8_t _inputs[64];
        uint8_t _inputsCount = 0;
    };
}