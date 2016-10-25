#ifndef ENTITY_GAME_PROGRESSTIMERUTIL_HPP_
#define ENTITY_GAME_PROGRESSTIMERUTIL_HPP_

#include "basic.h"

#include "Component/Game/ProgressTimer.h"
#include "Component/Game/ProgressTimerCallback.h"
#include "Component/Game/ProgressTimerIncrement.h"

#include "DateTimerUtil.h"

namespace gamecomputil {

class ProgressTimerUtil {
    private:
    // computil::TimerUtil timer_util_;
    computil::DateTimerUtil datetimer_util_;

    public:
    void init(gamecomp::ProgressTimer& progtimer,
              std::chrono::system_clock::time_point time,
              double realtime_factor) {
        datetimer_util_.setRealTime(progtimer.timer, time, realtime_factor);
        datetimer_util_.setRealTime(progtimer.fulltimer, time, realtime_factor);
    }
    inline void init(gamecomp::ProgressTimer& progtimer,
                     std::chrono::system_clock::time_point time) {
        init(progtimer, time, 1.0);
    }
    inline void init(gamecomp::ProgressTimer& progtimer) {
        init(progtimer, std::chrono::system_clock::now());
    }


    inline void init(gamecomp::ProgressTimerCallback& progtimer,
                     std::chrono::system_clock::time_point time,
                     double realtime_factor) {
        init(progtimer.base, time, realtime_factor);
    }
    inline void init(gamecomp::ProgressTimerCallback& progtimer,
                     std::chrono::system_clock::time_point time) {
        init(progtimer.base, time);
    }
    inline void init(gamecomp::ProgressTimerCallback& progtimer) {
        init(progtimer.base);
    }


    inline void init(gamecomp::ProgressTimerIncrement& progtimer,
                     std::chrono::system_clock::time_point time,
                     double realtime_factor) {
        init(progtimer.base, time, realtime_factor);
    }
    inline void init(gamecomp::ProgressTimerIncrement& progtimer,
                     std::chrono::system_clock::time_point time) {
        init(progtimer.base, time);
    }
    inline void init(gamecomp::ProgressTimerIncrement& progtimer) {
        init(progtimer.base);
    }

    void start(gamecomp::ProgressTimer& progtimer);
    void restart(gamecomp::ProgressTimer& progtimer);
    void stop(gamecomp::ProgressTimer& progtimer);
    void pause(gamecomp::ProgressTimer& progtimer);
    void unpause(gamecomp::ProgressTimer& progtimer);

    void addTime(gamecomp::ProgressTimer& progtimer,
                 const std::chrono::hours& time);
    void addTime(gamecomp::ProgressTimer& progtimer,
                 const std::chrono::seconds& time);
    void addTime(gamecomp::ProgressTimer& progtimer,
                 const std::chrono::milliseconds& time);
};
} // namespace gamecomputil

#endif // ENTITY_GAME_PROGRESSTIMERUTIL_HPP_