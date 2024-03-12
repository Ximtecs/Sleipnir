// test1.cpp - Test for the DISPATCH_CPP framework
#include <iostream>
#include "../../src/main/main.hpp"

int main() {
    std::cout << "Running test1 for SLEIPNIR framework." << std::endl;

    MainProgram program;
    program.initialize(10); // Initialize with 10 tasks

    // Access and print the IDs of the tasks
    for (const auto& task : program.getTasks()) {
        std::cout << "Task ID: " << task->getId() << std::endl;
    }


    program.run(); // This will now also print the IDs of the initialized tasks


    std::cout << "Test completed." << std::endl;

    return 0;
}

