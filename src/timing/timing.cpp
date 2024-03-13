#include "timing.hpp"

std::unordered_map<std::string, Timing::TimerInfo> Timing::timers;
omp_lock_t Timing::lock;
thread_local std::vector<std::string> Timing::activeTimers;

void Timing::initLock() {
    omp_init_lock(&lock);
}

void Timing::destroyLock() {
    omp_destroy_lock(&lock);
}

std::string Timing::generateThreadSpecificLabel(const std::string& label) {
    std::stringstream ss;
    ss << label << "@" << omp_get_thread_num(); // Append thread ID to label
    return ss.str();
}

void Timing::start(const std::string& label) {
    std::string threadSpecificLabel = generateThreadSpecificLabel(label);

    omp_set_lock(&lock); // Acquire the lock
    if (timers.find(threadSpecificLabel) == timers.end()) {
        timers[threadSpecificLabel] = TimerInfo(); // Initialize if not present
    }
    timers[threadSpecificLabel].startTime = omp_get_wtime(); // Record start time
    activeTimers.push_back(threadSpecificLabel); // Push onto the thread-local stack of active timers
    omp_unset_lock(&lock); // Release the lock
}

void Timing::end(const std::string& label) {
    std::string threadSpecificLabel = generateThreadSpecificLabel(label);
    double endTime = omp_get_wtime(); // Get current time

    omp_set_lock(&lock); // Acquire the lock
    if (!activeTimers.empty() && timers.find(threadSpecificLabel) != timers.end()) {
        auto& timer = timers[threadSpecificLabel];
        if (timer.startTime != 0.0) { // Ensure start was called
            double elapsedTime = endTime - timer.startTime;
            timer.totalTime += elapsedTime; // Accumulate elapsed time
            timer.callCount++; // Increment call count
            timer.startTime = 0.0; // Reset start time

            // Adjust the parent timer if there is one
            if (activeTimers.size() > 1) {
                std::string parentLabel = activeTimers[activeTimers.size() - 2];
                timers[parentLabel].totalTime -= elapsedTime;
            }
        }
        activeTimers.pop_back(); // Pop from the thread-local stack of active timers
    }
    omp_unset_lock(&lock); // Release the lock
}

void Timing::printResults() {
    omp_set_lock(&lock); // Acquire the lock

    // Map to aggregate results by base label
    std::unordered_map<std::string, TimerInfo> aggregatedResults;

    // Aggregate results
    for (const auto& pair : timers) {
        // Extract the base label by removing the thread ID
        std::string baseLabel = pair.first.substr(0, pair.first.find('@'));

        // Aggregate totalTime and callCount for each base label
        aggregatedResults[baseLabel].totalTime += pair.second.totalTime;
        aggregatedResults[baseLabel].callCount += pair.second.callCount;
    }

    // Calculate total time across all timings for percentage calculation
    double grandTotalTime = 0.0;
    for (const auto& pair : aggregatedResults) {
        grandTotalTime += pair.second.totalTime;
    }

    // Convert map to a vector for sorting
    std::vector<std::pair<std::string, TimerInfo>> sortedTimings(aggregatedResults.begin(), aggregatedResults.end());

    // Sort by highest total time
    std::sort(sortedTimings.begin(), sortedTimings.end(), [](const auto& a, const auto& b) {
        return a.second.totalTime > b.second.totalTime;
    });

    // Determine the maximum width for the label column
    int maxLabelWidth = 0;
    for (const auto& pair : sortedTimings) {
        if (pair.first.length() > maxLabelWidth) {
            maxLabelWidth = pair.first.length();
        }
    }

    // Print header
    std::cout << "\nTiming Results:\n";
    std::cout << std::left << std::setw(maxLabelWidth) << "Label" << "  "
              << std::right << std::setw(10) << "Time(s)" << "  "
              << std::setw(6) << "Calls" << "  "
              << std::setw(10) << "Avg Time" << "  "
              << std::setw(15) << "Percentage of Total" << "\n";

    // Print sorted and aggregated results with percentage of total time
    for (const auto& pair : sortedTimings) {
        double percentage = (pair.second.totalTime / grandTotalTime) * 100;
        std::cout << std::left << std::setw(maxLabelWidth) << pair.first << "  "
                  << std::right << std::setw(10) << std::fixed << std::setprecision(5) << pair.second.totalTime << "  "
                  << std::setw(6) << pair.second.callCount << "  "
                  << std::setw(10) << std::fixed << std::setprecision(5) << pair.second.totalTime / pair.second.callCount << "  "
                  << std::setw(15) << std::fixed << std::setprecision(5) << percentage << "%\n";
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
