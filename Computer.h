#ifndef COMPUTER_H
#define COMPUTER_H

#include "Processor.h"

class Computer {
public:
    IntelProcessor* GetProcessor(std::string version, ProcessorType type, double speed)
    {
        return new IntelProcessor(version, type, speed);
    }
};

#endif // COMPUTER_H
