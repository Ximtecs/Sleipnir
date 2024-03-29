// main_program.hpp - Part of the DISPATCH_CPP framework
#ifndef MAIN_PROGRAM_HPP
#define MAIN_PROGRAM_HPP

#include "task.hpp"
#include "timing.hpp"
#include <deque>
#include <mutex>
#include <thread>
#include <omp.h>

enum ProgramStatus {
    RUNNING,
    COMPLETED
};


class MainProgram {
private:
    std::deque<Task*> tasks;
    double endTime;
    std::mutex tasksMutex; // Mutex to protect access to tasks
    ProgramStatus status; // program status
    int tasksCreated = 0; // Number of tasks created
    int tasksFinished = 0 ; // Number of tasks finished

public:
    void initialize(int numberOfTasks);
    void pushTask(Task* task);

    const std::deque<Task*>& getTasks() const; // Added this line

    void run();
};
#endif // MAIN_PROGRAM_HPP
