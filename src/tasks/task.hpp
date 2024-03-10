#ifndef TASK_HPP
#define TASK_HPP

class Task {
private:
    static int nextId; // Static variable to track the next ID
    int id; // Unique ID for each task instance

public:
    Task(); // Constructor
    ~Task(); // Destructor

    int getId() const; // Getter for the task's ID
    void update(); // Renamed function
};

#endif // TASK_HPP
