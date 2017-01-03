#ifndef ENTITY_GAME_TIMERUTIL_HPP_
#define ENTITY_GAME_TIMERUTIL_HPP_

#include "basic.h"

#include "Component/DateTimer.h"

namespace computil {

class TimerUtil {
    public:
    void start(comp::Timer& timer);
    void pause(comp::Timer& timer);
    void unpause(comp::Timer& timer);
    void stop(comp::Timer& timer);

    void restart(comp::Timer& timer) {
        stop(timer);
        start(timer);
    }

    std::chrono::nanoseconds getTime(const comp::Timer& timer);
};
} // namespace computil

#endif // ENTITY_GAME_TIMERUTIL_HPP_
