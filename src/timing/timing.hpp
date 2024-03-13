#ifndef TIMING_HPP
#define TIMING_HPP

#include <omp.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip> 


class Timing {
public:
    static void start(const std::string& label);
    static void end(const std::string& label);
    static void printResults();

    // Public static methods for lock management
    static void initLock();
    static void destroyLock();

private:
    struct TimerInfo {
        double startTime = 0.0;
        double totalTime = 0.0;
        int callCount = 0; // Track number of calls
    };

    static std::unordered_map<std::string, TimerInfo> timers;
    static omp_lock_t lock; // OpenMP lock for thread safety

    // Thread-local stack to track active timers for each thread
    static thread_local std::vector<std::string> activeTimers;

    // Helper method to generate a unique label for each timer including the thread ID
    static std::string generateThreadSpecificLabel(const std::string& label);
};

#endif // TIMING_HPP
