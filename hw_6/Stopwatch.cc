#include "Stopwatch.h"

Stopwatch::Stopwatch() : total_duration(0), is_running(false) {}

void Stopwatch::start() {
    if (!is_running) {
        start_time = std::chrono::high_resolution_clock::now();
        is_running = true;
    }
}

void Stopwatch::stop() {
    if (is_running) {
        total_duration += std::chrono::high_resolution_clock::now() - start_time;
        is_running = false;
    }
}

void Stopwatch::reset() {
    total_duration = std::chrono::duration<double>(0);
    is_running = false;
}

double Stopwatch::get_minutes() {
    return std::chrono::duration_cast<std::chrono::minutes>(total_duration).count();
}

double Stopwatch::get_seconds() {
    return total_duration.count();
}

double Stopwatch::get_milliseconds() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(total_duration).count();
}

double Stopwatch::get_nanoseconds() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(total_duration).count();
}
