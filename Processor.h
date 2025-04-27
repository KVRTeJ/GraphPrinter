#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>

class Processor {
public:
    enum ProcessorType {
        x64 = 0,
        x86
    };

    static const std::vector<std::string> PROCESSOR_TYPE;
public:
    virtual ~Processor() = default;

    virtual std::string GetProcessorInfo() {return {};}
};

const std::vector<std::string> Processor::PROCESSOR_TYPE = {"x64", "x86"};

class IntelProcessor : public Processor {
public:
    explicit IntelProcessor(std::string version, Processor::ProcessorType type, double speed)
        : m_version(version), m_type(type), m_speed(speed)
    {}
    ~IntelProcessor() override = default;

    std::string getVersion() const {return m_version;}
    Processor::ProcessorType getType() const {return m_type;}
    double getSpeed() const {return m_speed;}

    void setVersion(const std::string& version) {m_version = version;}
    void setType(Processor::ProcessorType type) {m_type = type;}
    void setSpeed(double speed) {m_speed = speed;}

    std::string GetProcessorInfo() override {
        return "INTEL Processor for " + m_version + ' ' + std::to_string(m_speed) +
               ' ' + Processor::PROCESSOR_TYPE[m_type];
    }

private:
    std::string m_version = "";
    Processor::ProcessorType m_type;
    double m_speed = 0;
};

class AmdProcessor : public Processor {
public:
    explicit AmdProcessor(std::string version, Processor::ProcessorType type, double speed)
        : m_version(version), m_type(type), m_speed(speed)
    {}
    ~AmdProcessor() override = default;

    std::string getVersion() const {return m_version;}
    Processor::ProcessorType getType() const {return m_type;}
    double getSpeed() const {return m_speed;}

    void setVersion(const std::string& version) {m_version = version;}
    void setType(Processor::ProcessorType type) {m_type = type;}
    void setSpeed(double speed) {m_speed = speed;}

    std::string GetProcessorInfo() override {
        return "AMD Processor for " + m_version + ' ' + std::to_string(m_speed) +
               ' ' + Processor::PROCESSOR_TYPE[m_type];
    }

private:
    std::string m_version = "";
    Processor::ProcessorType m_type;
    double m_speed = 0;
};

#endif // PROCESSOR_H
