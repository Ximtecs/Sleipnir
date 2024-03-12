#ifndef TIMING_HPP
#define TIMING_HPP

#include <omp.h>
#include <string>
#include <unordered_map>
#include <iostream>

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
    };

    static std::unordered_map<std::string, TimerInfo> timers;
    static omp_lock_t lock; // OpenMP lock for thread safety
};

#endif // TIMING_HPP
