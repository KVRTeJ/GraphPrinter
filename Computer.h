#ifndef COMPUTER_H
#define COMPUTER_H

#include "Processor.h"

class Computer {
public:
    Processor* GetProcessor(std::string version, Processor::ProcessorType type, double speed)
    {
        return new IntelProcessor(version, type, speed);
    }
};

#endif // COMPUTER_H
