#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
public:
    Stopwatch();

    void start();
    void stop();
    void reset();
    double get_minutes();
    double get_seconds();
    double get_milliseconds();
    double get_nanoseconds();

private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::duration<double> total_duration;
    bool is_running;
};

#endif // STOPWATCH_H
