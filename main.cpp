#include <iostream>

#include "Computer.h"

int main(int argc, const char *argv[]) {
    Computer boo;

    std::cout << boo.GetProcessor("test", ProcessorType::x86, 3.1)->GetProcessorInfo() << std::endl;

    return 0;
}
