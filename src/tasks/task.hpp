#ifndef TASK_HPP
#define TASK_HPP

enum TaskStatus {
    READY,
    UPDATING,
    FINISHED
};

class Task {
private:
    static int nextId; // Static variable to track the next ID
    int id; // Unique ID for each task instance
    double endTime;
    double time; // Time variable
    double dt; // Time step
    TaskStatus status; // Task status


public:
    Task(); // Constructor
    ~Task(); // Destructor

    int getId() const; // Getter for the task's ID
    void update(); // Renamed function
    TaskStatus getStatus() const; // Getter for the task's status
    void setStatus(TaskStatus newStatus); // Setter for the task's status

};

#endif // TASK_HPP
