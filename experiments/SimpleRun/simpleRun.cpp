// test1.cpp - Test for the DISPATCH_CPP framework
#include <iostream>
#include "main.hpp"

int main() {
    std::cout << "Running simpleRun for SLEIPNIR framework." << std::endl;

    MainProgram program;
    program.initialize(10); // Initialize with 10 tasks

    program.run(); // This will now also print the IDs of the initialized tasks


    return 0;
}

