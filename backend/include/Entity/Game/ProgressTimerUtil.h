#ifndef ENTITY_GAME_PROGRESSTIMERUTIL_HPP_
#define ENTITY_GAME_PROGRESSTIMERUTIL_HPP_

#include "basic.h"

#include "Component/Game/ProgressTimer.h"
#include "Component/Game/ProgressTimerCallback.h"
#include "Component/Game/ProgressTimerIncrement.h"
#include "Component/Game/CreatureProgressTimers.h"

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

    void start(gamecomp::ProgressTimer& proctimer);
    void restart(gamecomp::ProgressTimer& proctimer);
    void stop(gamecomp::ProgressTimer& proctimer);
    void pause(gamecomp::ProgressTimer& proctimer);
    void unpause(gamecomp::ProgressTimer& proctimer);

    void addTime(gamecomp::ProgressTimer& proctimer,
                 const std::chrono::hours& time);
    void addTime(gamecomp::ProgressTimer& proctimer,
                 const std::chrono::seconds& time);
    void addTime(gamecomp::ProgressTimer& proctimer,
                 const std::chrono::milliseconds& time);
    
    gamecomp::ProgressTimer& getProgressTimer(earr::enum_array<gamecomp::CreatureProgressTimer, gamecomp::ProgressTimer>& timer, gamecomp::CreatureProgressTimer type){
        auto& type_timer = earr::enum_array_at(timer, type);
        gamecomp::ProgressTimer& type_progresstimer = type_timer;
        return type_progresstimer;
    }

    gamecomp::ProgressTimer& getProgressTimer(earr::enum_array<gamecomp::CreatureProgressTimerCallback, gamecomp::ProgressTimerCallback>& callback, gamecomp::CreatureProgressTimerCallback type){
        auto& type_timer = earr::enum_array_at(callback, type);
        gamecomp::ProgressTimer& type_progresstimer = type_timer.base;
        return type_progresstimer;
    }

    gamecomp::ProgressTimer& getProgressTimer(earr::enum_array<gamecomp::CreatureProgressTimerIncrement, gamecomp::ProgressTimerIncrement>& increment, gamecomp::CreatureProgressTimerIncrement type){
        auto& type_timer = earr::enum_array_at(increment, type);
        gamecomp::ProgressTimer& type_progresstimer = type_timer.base;
        return type_progresstimer;
    }


    gamecomp::ProgressTimer& getProgressTimer(gamecomp::CreatureProgressTimersComponent& timers, gamecomp::CreatureProgressTimer type) {
        return getProgressTimer(timers.timer, type);
    }

    gamecomp::ProgressTimer& getProgressTimer(gamecomp::CreatureProgressTimersComponent& timers, gamecomp::CreatureProgressTimerCallback type) {
        return getProgressTimer(timers.callback, type);
    }
    gamecomp::ProgressTimer& getCallbackProgressTimer(gamecomp::CreatureProgressTimersComponent& timers, gamecomp::CreatureProgressTimerCallback type) {
        return getProgressTimer(timers, type);
    }

    gamecomp::ProgressTimer& getProgressTimer(gamecomp::CreatureProgressTimersComponent& timers, gamecomp::CreatureProgressTimerIncrement type) {
        return getProgressTimer(timers.increment, type);
    }
    gamecomp::ProgressTimer& getIncrementProgressTimer(gamecomp::CreatureProgressTimersComponent& timers, gamecomp::CreatureProgressTimerIncrement type) {
        return getProgressTimer(timers, type);
    }
    
};
} // namespace gamecomputil

#endif // ENTITY_GAME_PROGRESSTIMERUTIL_HPP_