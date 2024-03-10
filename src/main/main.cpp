// main_program.cpp - Part of the DISPATCH_CPP framework
#include "main.hpp"

#include <iostream>

// Initialize the tasks
void MainProgram::initialize(int numberOfTasks) {
    for (int i = 0; i < numberOfTasks; ++i) {
        tasks.emplace_back(); // Utilize Task's constructor
    }
}

const std::vector<Task>& MainProgram::getTasks() const {
    return tasks;
}

// Existing run method (adjust if necessary)
void MainProgram::run() {
    std::cout << "Running the main program" << std::endl;
}

