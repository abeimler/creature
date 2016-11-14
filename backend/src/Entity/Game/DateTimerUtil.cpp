#include "Entity/Game/DateTimerUtil.h"

namespace computil {

constexpr std::chrono::system_clock::time_point DateTimerUtil::TIMEEPOCHE;

void DateTimerUtil::setRealTime(comp::DateTimer& datetimer,
                                std::chrono::system_clock::time_point datetime,
                                double realtime_factor) {
    auto realTime = datetime.time_since_epoch();
    datetimer.realtime =
        std::chrono::duration_cast<std::chrono::milliseconds>(realTime);
    datetimer.realtime_factor = realtime_factor;
}

void DateTimerUtil::addTime(comp::DateTimer& datetimer,
                            std::chrono::milliseconds time) {
    if (datetimer.isstart) {
        if (datetimer.ispause) {
            datetimer.pausetime += time;
        } else {
            datetimer.starttime -= time;
        }
    }
}

void DateTimerUtil::restart(comp::DateTimer& datetimer) {
    timer_util_.restart(datetimer.realtimer);

    datetimer.isstart = true;
    datetimer.ispause = false;

    datetimer.starttime = datetimer.realtime;
    datetimer.pausetime = std::chrono::milliseconds::zero();
}

void DateTimerUtil::start(comp::DateTimer& datetimer) {
    timer_util_.start(datetimer.realtimer);

    datetimer.isstart = true;
    datetimer.ispause = false;

    datetimer.starttime = datetimer.realtime;
}
void DateTimerUtil::stop(comp::DateTimer& datetimer) {
    timer_util_.stop(datetimer.realtimer);

    datetimer.isstart = false;
    datetimer.ispause = false;

    datetimer.starttime = std::chrono::milliseconds::zero();
    datetimer.pausetime = std::chrono::milliseconds::zero();
}
void DateTimerUtil::pause(comp::DateTimer& datetimer) {
    timer_util_.pause(datetimer.realtimer);

    if (datetimer.isstart && !datetimer.ispause) {
        datetimer.ispause = true;
        datetimer.pausetime = (datetimer.realtime > datetimer.starttime)
                                  ? datetimer.realtime - datetimer.starttime
                                  : std::chrono::milliseconds::zero();
    }
}
void DateTimerUtil::unpause(comp::DateTimer& datetimer) {
    timer_util_.unpause(datetimer.realtimer);

    if (datetimer.ispause) {
        datetimer.ispause = false;
        datetimer.starttime = (datetimer.realtime > datetimer.pausetime)
                                  ? datetimer.realtime - datetimer.pausetime
                                  : datetimer.realtime;
        datetimer.pausetime = std::chrono::milliseconds::zero();
    }
}

std::chrono::milliseconds
DateTimerUtil::getTime(const comp::DateTimer& datetimer) {
    auto timesincestart = (datetimer.realtime > datetimer.starttime)
                              ? datetimer.realtime - datetimer.starttime
                              : std::chrono::milliseconds::zero();

    auto time = (datetimer.ispause) ? datetimer.pausetime : timesincestart;

    return (datetimer.isstart) ? time : std::chrono::milliseconds::zero();
}

void DateTimerUtil::update(comp::DateTimer& datetimer, bool ignortimer) {
    if (!util::iszero(datetimer.realtime_factor)) {
        std::chrono::milliseconds add_ms(0);
        if (!ignortimer) {
            std::chrono::milliseconds realtimer_ms(0);
            realtimer_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    timer_util_.getTime(datetimer.realtimer));
            double add_ms_f = static_cast<double>(realtimer_ms.count()) *
                              static_cast<double>(datetimer.realtime_factor);
            add_ms = std::chrono::milliseconds(static_cast<int64_t>(add_ms_f));
        } else {
            std::chrono::milliseconds realtimer_ms(0);

            double realTimeFactor_ms_f =
                static_cast<double>(datetimer.realtime_factor) *
                std::chrono::milliseconds::period::den;

            realtimer_ms = std::chrono::milliseconds(
                static_cast<int64_t>(realTimeFactor_ms_f));
            add_ms = realtimer_ms;
        }

        if (add_ms > std::chrono::milliseconds::zero()) {
            datetimer.realtime += add_ms;
            timer_util_.restart(datetimer.realtimer);
        } else if (ignortimer) {
            timer_util_.restart(datetimer.realtimer);
        }
    }
}
} // namespace computil
