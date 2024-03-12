// main_program.cpp - Part of the DISPATCH_CPP framework
#include "main.hpp"

#include <iostream>

// Initialize the tasks
void MainProgram::initialize(int numberOfTasks) {
    for (int i = 0; i < numberOfTasks; ++i) {
        tasks.push_back(new Task()); // Dynamically allocate a new Task
        tasksCreated++;
    }
}


const std::deque<Task*>& MainProgram::getTasks() const {
    return tasks;
}

void MainProgram::run() {
    int numThreads = omp_get_num_threads();
    this->status = RUNNING;
    std::cout << "Running the main program" << std::endl;

    #pragma omp parallel
    {
        #pragma omp single
        {
            while (status == RUNNING) {
                Task* taskPtr = nullptr;

                #pragma omp critical (tasks_access)
                {
                    if (!tasks.empty()) {
                        taskPtr = tasks.front();
                        tasks.pop_front();
                    }
                }

                if (taskPtr != nullptr) {
                    #pragma omp task firstprivate(taskPtr) if(numThreads > 1)
                    {
                        taskPtr->update();

                        bool taskFinished = false;
                        #pragma omp critical (update_finished_status)
                        {
                            if (taskPtr->getStatus() == FINISHED) {
                                tasksFinished++;
                                taskFinished = true;
                            }
                        }

                        if (!taskFinished) {
                            #pragma omp critical (tasks_access)
                            {
                                tasks.push_back(taskPtr);
                            }
                        } else {
                            delete taskPtr; // Clean up finished task
                        }

                        // Update program status if all tasks are finished
                        #pragma omp critical (update_program_status)
                        {
                            if (tasksFinished == tasksCreated) {
                                status = COMPLETED;
                            }
                        }
                    }
                } else {
                    // Small sleep to prevent busy waiting if all tasks are currently being processed
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            }
        }
    }
}