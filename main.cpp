#include <iostream>

#include "Computer.h"

template <typename ProcType>
void makeRegister(IOCContainer& ioc) {
    ioc.RegisterFunctor<Processor, std::string, Processor::ProcessorType, double>(
        std::function<std::shared_ptr<Processor>(std::shared_ptr<std::string>,
                                                 std::shared_ptr<Processor::ProcessorType>,
                                                 std::shared_ptr<double>)>([] (std::shared_ptr<std::string> version,
                                                                              std::shared_ptr<Processor::ProcessorType> type,
                                                                              std::shared_ptr<double> speed)->std::shared_ptr<Processor>
                                                                           {
                                                                               return std::make_shared<ProcType>(*version, *type, *speed);
                                                                           }));
}

int main() {
    IOCContainer ioc;

    std::cout << "\n\tПример" << std::endl;
    ioc.RegisterInstance<std::string>(std::make_shared<std::string>("version 2"));
    ioc.RegisterInstance<Processor::ProcessorType>(std::make_shared<Processor::ProcessorType>(Processor::x64));
    ioc.RegisterInstance<double>(std::make_shared<double>(3.111));

    makeRegister<IntelProcessor>(ioc);

    ioc.RegisterFactory<Computer, Computer, Processor>();
    auto boo = ioc.GetObject<Computer>();
    boo->configure();

    makeRegister<AmdProcessor>(ioc);
    boo->setProcessor(ioc);
    boo->configure();


    std::cout << "\n\tПример" << std::endl;
    ioc.RegisterInstance<Processor>(std::make_shared<IntelProcessor>("version 3.1", Processor::ProcessorType::x86, 4.555));
    Computer comp(ioc.GetObject<Processor>());
    comp.configure();

    ioc.RegisterInstance<Processor>(std::make_shared<AmdProcessor>("version 3.1", Processor::ProcessorType::x86, 3.111));
    comp.setProcessor(ioc);
    comp.configure();


    return 0;
}
