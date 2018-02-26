#ifndef GSOC_STOPWATCH_H
#define GSOC_STOPWATCH_H

#include <chrono>

/**
 * \class A simple stopwatch class to measure time.
 */
class Stopwatch {
public:
    Stopwatch() = default;
    Stopwatch(const Stopwatch&) = delete; 
    Stopwatch& operator=(const Stopwatch&) = delete; 

    /**
     * \brief Start stopwatch
     */
    void start() {
        starting_time = std::chrono::steady_clock::now();
    }

    /**
     * \brief Stop stopwatch
     */
    void stop() {
        stopping_time = std::chrono::steady_clock::now();
    }

    /**
     * \brief Get elapsed time, i.e., the time difference between start and 
     * stop
     * \return Elapsed time
     */
    template<typename T>
    T elapsed() {
        return std::chrono::duration_cast<T>(stopping_time-starting_time);
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> starting_time;
    std::chrono::time_point<std::chrono::steady_clock> stopping_time;
};

#endif /* GSOC_STOPWATCH_H */