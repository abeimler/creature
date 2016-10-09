#ifndef DATA_TIMER_HPP_
#define DATA_TIMER_HPP_

#include "basic.hpp"

#include "Data/BaseModel.hpp"

namespace data {

/// Simple Timer
class Timer {

    private:
    bool isstart_ = false;
    bool ispause_ = false;

    std::chrono::nanoseconds starttime_;
    std::chrono::nanoseconds pausetime_;

    public:
    Timer();

    void start();   ///< start Timer
    void pause();   ///< pause Timer
    void unpause(); ///< continue Timer
    void restart(); ///< restart/reset Timer
    void stop();    ///< stop Timer

    /// is Timer started
    bool isStarted() const { return this->isstart_; }

    /// is Timer paused
    bool isPaused() const { return this->ispause_; }

    /// get current Time in sec
    std::chrono::seconds getTime() const {
        return std::chrono::duration_cast<std::chrono::seconds>(
            this->getTimeNanosec());
    }

    /// get current Time in millisec
    std::chrono::milliseconds getTimeMillisec() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            this->getTimeNanosec());
    }

    /// get current Time in nanosec
    std::chrono::nanoseconds getTimeNanosec() const;
};
} // namespace data

#endif // DATA_TIMER_HPP_
