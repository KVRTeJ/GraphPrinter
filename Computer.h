#ifndef COMPUTER_H
#define COMPUTER_H

#include "IOC_Contaner.h"
#include "Processor.h"

class Computer {
public:
    Computer() = default;
    Computer(std::shared_ptr<Processor> p)
        : m_processor(p)
    {}
    void setProcessor(IOCContainer& serviceLocator)
    {
        m_processor = serviceLocator.GetObject<Processor>();
    }
    void configure() const
    {
        std::cout << m_processor->getProcessorInfo() << std::endl;
    }
private:
    std::shared_ptr<Processor> m_processor;
};

#endif // COMPUTER_H
