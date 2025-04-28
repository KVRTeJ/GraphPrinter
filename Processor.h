#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>
#include <memory.h>

class Processor {
public:
    enum ProcessorType {
        x64 = 0,
        x86
    };

    static const std::vector<std::string> PROCESSOR_TYPE;
public:
    virtual ~Processor() = default;

    virtual std::string getVersion() const = 0;
    virtual Processor::ProcessorType getType() const = 0;
    virtual double getSpeed() const = 0;

    virtual void setVersion(const std::string& version) = 0;
    virtual void setType(Processor::ProcessorType type) = 0;
    virtual void setSpeed(double speed) = 0;

    virtual std::string getProcessorInfo() {return {};}
};

const std::vector<std::string> Processor::PROCESSOR_TYPE = {"x64", "x86"};

class IntelProcessor : public Processor {
public:
    IntelProcessor(std::string version = "v1",
                   Processor::ProcessorType type = x64,
                   double speed = 1.5)
        : m_version(version), m_type(type), m_speed(speed)
    {}
    IntelProcessor(std::shared_ptr<std::string> version,
                   std::shared_ptr<ProcessorType> type,
                   std::shared_ptr<double> speed)
        :m_version(*version), m_type(*type), m_speed(*speed)
    {}
    ~IntelProcessor() override = default;

    std::string getVersion() const override {return m_version;}
    Processor::ProcessorType getType() const override {return m_type;}
    double getSpeed() const override {return m_speed;}

    void setVersion(const std::string& version) override {m_version = version;}
    void setType(Processor::ProcessorType type) override {m_type = type;}
    void setSpeed(double speed) override {m_speed = speed;}

    std::string getProcessorInfo() override {
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
    AmdProcessor(std::string version = "v1",
                 Processor::ProcessorType type = x64,
                 double speed = 1.5)
        : m_version(version), m_type(type), m_speed(speed)
    {}
    AmdProcessor(std::shared_ptr<std::string> version,
                   std::shared_ptr<ProcessorType> type,
                   std::shared_ptr<double> speed)
        :m_version(*version), m_type(*type), m_speed(*speed)
    {}
    ~AmdProcessor() override = default;

    std::string getVersion() const override {return m_version;}
    Processor::ProcessorType getType() const override {return m_type;}
    double getSpeed() const override {return m_speed;}

    void setVersion(const std::string& version) override {m_version = version;}
    void setType(Processor::ProcessorType type) override {m_type = type;}
    void setSpeed(double speed) override {m_speed = speed;}

    std::string getProcessorInfo() override {
        return "AMD Processor for " + m_version + ' ' + std::to_string(m_speed) +
               ' ' + Processor::PROCESSOR_TYPE[m_type];
    }

private:
    std::string m_version = "";
    Processor::ProcessorType m_type;
    double m_speed = 0;
};

#endif // PROCESSOR_H
