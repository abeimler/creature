#ifndef ENTITY_GAME_DATETIMERUTIL_HPP_
#define ENTITY_GAME_DATETIMERUTIL_HPP_

#include "basic.h"

#include "Component/DateTimer.h"

#include "TimerUtil.h"

namespace computil {

class DateTimerUtil {
    protected:
    TimerUtil timer_util_;

    static constexpr std::chrono::system_clock::time_point TIMEEPOCHE =
        std::chrono::system_clock::time_point();

    public:
    std::chrono::system_clock::time_point
    getRealTime(comp::DateTimer& datetimer) {
        auto realTime_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                datetimer.realtime);
        return TIMEEPOCHE + realTime_ms;
    }

    void setRealTime(comp::DateTimer& datetimer,
                     std::chrono::system_clock::time_point datetime,
                     double realtime_factor);
    inline void setRealTime(comp::DateTimer& datetimer,
                            std::chrono::system_clock::time_point datetime) {
        setRealTime(datetimer, datetime, 1.0);
    }

    void addTime(comp::DateTimer& datetimer, std::chrono::milliseconds time);

    void init(comp::DateTimer& datetimer,
              std::chrono::system_clock::time_point datetime,
              double realtime_factor) {
        setRealTime(datetimer, datetime, realtime_factor);
    }
    inline void init(comp::DateTimer& datetimer,
                     std::chrono::system_clock::time_point datetime) {
        init(datetimer, datetime, 1.0);
    }
    inline void init(comp::DateTimer& datetimer) {
        setRealTime(datetimer, std::chrono::system_clock::now(), 1.0);
    }

    void start(comp::DateTimer& datetimer);
    void restart(comp::DateTimer& datetimer);
    void stop(comp::DateTimer& datetimer);
    void pause(comp::DateTimer& datetimer);
    void unpause(comp::DateTimer& datetimer);

    std::chrono::milliseconds getTime(const comp::DateTimer& datetimer);

    void update(comp::DateTimer& datetimer, bool ignortimer);
    inline void update(comp::DateTimer& datetimer) { update(datetimer, false); }
};
} // namespace computil

#endif // ENTITY_GAME_DATETIMERUTIL_HPP_
