// test1.cpp - Test for the DISPATCH_CPP framework
#include <iostream>
#include "../../src/main/main.hpp"

int main() {
    std::cout << "Running test1 for DISPATCH_CPP framework." << std::endl;

    MainProgram program;

    // Example usage of the components in a test scenario
    program.run();

    std::cout << "Test completed." << std::endl;
    return 0;
}
