// main_program.hpp - Part of the DISPATCH_CPP framework
#ifndef MAIN_PROGRAM_HPP
#define MAIN_PROGRAM_HPP

#include "task.hpp"
#include <vector>

class MainProgram {
private:
    std::vector<Task> tasks;
    double endTime;

public:
    void initialize(int numberOfTasks);
    const std::vector<Task>& getTasks() const; // Added this line

    void run();
};
#endif // MAIN_PROGRAM_HPP
