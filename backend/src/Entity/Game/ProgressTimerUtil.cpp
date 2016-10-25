#include "ProgressTimerUtil.h"

namespace gamecomputil {

void ProgressTimerUtil::start(gamecomp::ProgressTimer& proctimer) {
    if (!proctimer.timer.isstart) {
        datetimer_util_.start(proctimer.timer);
        datetimer_util_.stop(proctimer.fulltimer);

        proctimer.isfull = false;
    }
}

void ProgressTimerUtil::addTime(gamecomp::ProgressTimer& proctimer,
                                const std::chrono::hours& time) {
    datetimer_util_.addTime(proctimer.timer, time);
}
void ProgressTimerUtil::addTime(gamecomp::ProgressTimer& proctimer,
                                const std::chrono::seconds& time) {
    datetimer_util_.addTime(proctimer.timer, time);
}
void ProgressTimerUtil::addTime(gamecomp::ProgressTimer& proctimer,
                                const std::chrono::milliseconds& time) {
    datetimer_util_.addTime(proctimer.timer, time);
}

void ProgressTimerUtil::restart(gamecomp::ProgressTimer& proctimer) {
    datetimer_util_.restart(proctimer.timer);
    datetimer_util_.stop(proctimer.fulltimer);

    proctimer.isfull = false;
    proctimer.value = 0.0;
    proctimer.overlayvalue = 0.0;
}

void ProgressTimerUtil::stop(gamecomp::ProgressTimer& proctimer) {
    datetimer_util_.stop(proctimer.timer);
    datetimer_util_.stop(proctimer.fulltimer);

    proctimer.isfull = false;
    proctimer.value = 0.0;
    proctimer.overlayvalue = 0.0;
}

void ProgressTimerUtil::pause(gamecomp::ProgressTimer& proctimer) {
    datetimer_util_.pause(proctimer.timer);
    datetimer_util_.pause(proctimer.fulltimer);
}

void ProgressTimerUtil::unpause(gamecomp::ProgressTimer& proctimer) {
    datetimer_util_.unpause(proctimer.timer);
    datetimer_util_.unpause(proctimer.fulltimer);
}
} // namespace gamecomputil
