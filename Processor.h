#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>

enum ProcessorType {
    x64 = 0,
    x86
};

static const std::vector<std::string> PROCESSOR_TYPE = {"x64", "x86"};

class IntelProcessor {
public:
    explicit IntelProcessor(std::string version, ProcessorType type, double speed)
        : m_version(version), m_type(type), m_speed(speed)
    {}

    //TODO: get/set

    std::string GetProcessorInfo() {
        return "Processor for " + m_version + ' ' + std::to_string(m_speed) +
               ' ' + PROCESSOR_TYPE[m_type];
    }

private:
    std::string m_version = "";
    ProcessorType m_type;
    double m_speed = 0;
};

#endif // PROCESSOR_H
