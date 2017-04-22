#ifndef DATA_TIMER_H_
#define DATA_TIMER_H_

#include "basic.h"

#include "Data/BaseModel.h"

#include "Data/Types.h"

namespace data {

/// Simple Timer
class Timer {

    private:
    boolean_t isstart_ = false;
    boolean_t ispause_ = false;

    std::chrono::nanoseconds starttime_{};
    std::chrono::nanoseconds pausetime_{};

  public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("isstart", isstart_));
        ar(cereal::make_nvp("ispause", ispause_));
        ar(cereal::make_nvp("starttime", starttime_));
        ar(cereal::make_nvp("pausetime", pausetime_));
    }

    public:
    Timer();

    void start();   ///< start Timer
    void pause();   ///< pause Timer
    void unpause(); ///< continue Timer
    void restart(); ///< restart/reset Timer
    void stop();    ///< stop Timer

    /// is Timer started
    boolean_t isStarted() const { return this->isstart_; }

    /// is Timer paused
    boolean_t isPaused() const { return this->ispause_; }

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

#endif // DATA_TIMER_H_
