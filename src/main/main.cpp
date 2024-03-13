// main_program.cpp - Part of the DISPATCH_CPP framework
#include "main.hpp"

#include <iostream>
#include <omp.h>

// Initialize the tasks
void MainProgram::initialize(int numberOfTasks) {
    for (int i = 0; i < numberOfTasks; ++i) {
        tasks.push_back(new Task()); // Dynamically allocate a new Task
        tasksCreated++;
    }
}

void MainProgram::pushTask(Task* task) {
    tasks.push_back(task);
    tasksCreated++;
}


const std::deque<Task*>& MainProgram::getTasks() const {
    return tasks;
}

/**
 * Runs the main program.
 * This function is responsible for executing the tasks in parallel until all tasks are finished.
 */
void MainProgram::run() {
    Timing::start("main_program");
//TODO add timing module


    #pragma omp parallel
    {
        #pragma omp single
        {
            //omp_set_num_threads(4);
            int numThreads = omp_get_num_threads();
            this->status = RUNNING;
            std::cout << "Running the main program with " << numThreads << " threads" << std::endl;

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
                        if (taskPtr->getStatus() == FINISHED) {
                            #pragma omp critical (update_finished_status)
                            {
                                tasksFinished++;
                            }
                            taskFinished = true;
                        }

                        if (!taskFinished) {
                            #pragma omp critical (tasks_access)
                            {
                                tasks.push_back(taskPtr);
                            }
                        } else {
                            delete taskPtr; // Clean up finished task
                        }


                    }
                } else {
                    // Wait for all tasks to finish
                    //TODO this may impact performance now since thread0 has very little work to do
                    #pragma omp taskwait

                    // Update program status if all tasks are finished
                    #pragma omp critical (update_program_status)
                    {
                        if (tasksFinished == tasksCreated) {
                            status = COMPLETED;
                        }
                    }
                }
            }
        }
    }
    Timing::end("main_program");
}