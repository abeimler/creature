#include "Timer.hpp"

namespace data {

Timer::Timer() { this->start(); }

void Timer::start() {
    this->isstart_ = true;
    this->ispause_ = false;

    this->starttime_ = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch());
}
void Timer::pause() {
    // If the timer is running and isn't already paused
    if (this->isstart_ && !this->ispause_) {
        this->ispause_ = true;
        // Calculate the paused time
        std::chrono::nanoseconds now_sec =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch());
        this->pausetime_ = now_sec - this->starttime_;
    }
}
void Timer::unpause() {
    // If the timer is paused
    if (this->ispause_) {
        this->ispause_ = false;
        // Reset the starting ticks
        std::chrono::nanoseconds now_sec =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch());
        this->starttime_ =
            (now_sec > this->pausetime_) ? now_sec - this->pausetime_ : now_sec;
        this->pausetime_ = std::chrono::nanoseconds(0); // Reset the paused time
    }
}
void Timer::restart() {
    this->stop();
    this->start();
}
void Timer::stop() {
    this->ispause_ = false;
    this->isstart_ = false;
}

std::chrono::nanoseconds Timer::getTimeNanosec() const {
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch();

    auto timesincestart = (now > this->starttime_)
                              ? now - this->starttime_
                              : std::chrono::nanoseconds::zero();

    auto time = (this->ispause_)
                    ? std::chrono::duration_cast<std::chrono::nanoseconds>(
                          this->pausetime_)
                    : timesincestart;

    return (this->isstart_) ? time : std::chrono::nanoseconds::zero();
}

} // namespace model
