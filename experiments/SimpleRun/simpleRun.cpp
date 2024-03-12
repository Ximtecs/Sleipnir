// test1.cpp - Test for the DISPATCH_CPP framework
#include <iostream>
#include "patch.hpp"
#include "main.hpp"


int main() {
    std::cout << "Running simpleRun for SLEIPNIR framework." << std::endl;

    MainProgram program;
    //program.initialize(10); // Initialize with 10 tasks

    for (int i = 0; i < 10; i++) {
        Patch* task = new Patch();
        task->SetPatchSize(10000000);
        task->AllocateMemory();
        program.pushTask(task);
    }

    
    program.run(); // This will now also print the IDs of the initialized tasks


    Timing::printResults(); // Print the timing results

    return 0;
}

