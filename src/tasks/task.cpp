#include "task.hpp"
#include <omp.h> // Include OpenMP header for multithreading support
#include <iostream>

int Task::nextId = 0; // Initialize static variable

// Constructor
Task::Task() {
    #pragma omp critical
    {
        id = nextId++; // Ensure unique ID assignment is thread-safe
    }
    time = 0.0;
    status = TaskStatus::READY;
}

// Destructor
Task::~Task() {
    // Destructor implementation (if needed)
}

// Getter for the task's ID
int Task::getId() const {
    return id;
}

// Implementation of the updated function
void Task::update() {
    // Placeholder for task-specific functionality
    // Implement your task updating logic here.
    std::cout << "Task " << id << " updated." << std::endl;
}

// Getter for the task's status
TaskStatus Task::getStatus() const {
    return status;
}

// Setter for the task's status 
void Task::setStatus(TaskStatus newStatus) {
    status = newStatus;
}
