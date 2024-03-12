#include "timing.hpp"

std::unordered_map<std::string, Timing::TimerInfo> Timing::timers;
omp_lock_t Timing::lock;

// Initialize the OpenMP lock
void Timing::initLock() {
    omp_init_lock(&lock);
}

// Destroy the OpenMP lock
void Timing::destroyLock() {
    omp_destroy_lock(&lock);
}

void Timing::start(const std::string& label) {
    omp_set_lock(&lock); // Acquire the lock
    if (timers.find(label) == timers.end()) {
        timers[label] = TimerInfo(); // Initialize if not present
    }
    timers[label].startTime = omp_get_wtime(); // Record start time
    omp_unset_lock(&lock); // Release the lock
}

void Timing::end(const std::string& label) {
    double endTime = omp_get_wtime(); // Get current time

    omp_set_lock(&lock); // Acquire the lock
    if (timers.find(label) != timers.end()) {
        auto& timer = timers[label];
        if (timer.startTime != 0.0) { // Ensure start was called
            timer.totalTime += endTime - timer.startTime; // Accumulate elapsed time
            timer.startTime = 0.0; // Reset start time
        }
    }
    omp_unset_lock(&lock); // Release the lock
}

void Timing::printResults() {
    omp_set_lock(&lock); // Acquire the lock
    for (const auto& pair : timers) {
        std::cout << pair.first << ": " << pair.second.totalTime << " seconds\n";
    }
    omp_unset_lock(&lock); // Release the lock
}

// Static initializer to set up and tear down the OpenMP lock
struct StaticInitializer {
    StaticInitializer() {
        Timing::initLock(); // Initialize the lock at program start
    }
    ~StaticInitializer() {
        Timing::destroyLock(); // Destroy the lock at program end
    }
};

static StaticInitializer initializer; // Ensures the above constructor and destructor are called
