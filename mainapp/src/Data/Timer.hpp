#ifndef MODEL_TIMER_HPP_
#define MODEL_TIMER_HPP_

#include "basic.hpp"

#include "Model/BaseModel.hpp"

namespace model {

/// Simple Timer
#pragma db value table("model_timer")
class Timer {
    ODB_ACCESS

    private:
    bool isstart_ = false;
    bool ispause_ = false;

    std::chrono::nanoseconds get_starttime() const;      // By-value accessor.
    void set_starttime(std::chrono::nanoseconds const&); // By-value modifier.
    std::chrono::nanoseconds get_pausetime() const;      // By-value accessor.
    void set_pausetime(std::chrono::nanoseconds const&); // By-value modifier.

#pragma db get(get_starttime) set(set_starttime)
    std::chrono::nanoseconds starttime_;

#pragma db get(get_pausetime) set(set_pausetime)
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
} // namespace model

#endif // MODEL_TIMER_HPP_
