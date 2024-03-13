#include "task.hpp"
int Task::nextId = 0; // Initialize static variable

// Constructor
Task::Task() {
    #pragma omp critical
    {
        id = nextId++; // Ensure unique ID assignment is thread-safe
    }
    time = 0.0;
    dt = 0.1;
    endTime = 1.0;
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
    Timing::start("task_update"); // Start timing the task update
    // Placeholder for task-specific functionality
    // Implement your task updating logic here.

    this->time += this->dt; // Increment the time variable by the time step   
    //std::cout << "Task " << id << " updated to time " << this->time << std::endl;



    if (this->time >= this->endTime) {
        status = TaskStatus::FINISHED;
        //std::cout << "Task " << id << " has finished" << std::endl;
    }
    Timing::end("task_update"); // End timing the task update
}

// Getter for the task's status
TaskStatus Task::getStatus() const {
    return status;
}

// Setter for the task's status 
void Task::setStatus(TaskStatus newStatus) {
    status = newStatus;
}
