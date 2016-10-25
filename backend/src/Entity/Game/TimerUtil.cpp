#include "TimerUtil.h"

namespace computil {

void TimerUtil::start(comp::Timer& timer) {
    timer.isstart = true;
    timer.ispause = false;

    timer.starttime = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch());
}
void TimerUtil::pause(comp::Timer& timer) {
    // If the timer is running and isn't already paused
    if (timer.isstart && !timer.ispause) {
        timer.ispause = true;
        // Calculate the paused time
        auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
        timer.pausetime = now - timer.starttime;
    }
}
void TimerUtil::unpause(comp::Timer& timer) {
    // If the timer is paused
    if (timer.ispause) {
        timer.ispause = false;
        // Reset the starting ticks
        auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
        timer.starttime = (now > timer.pausetime) ? now - timer.pausetime : now;
        timer.pausetime =
            std::chrono::nanoseconds::zero(); // Reset the paused time
    }
}
void TimerUtil::stop(comp::Timer& timer) {
    timer.ispause = false;
    timer.isstart = false;
}

std::chrono::nanoseconds TimerUtil::getTime(const comp::Timer& timer) {
    
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto timesincestart = (now > timer.starttime) 
                            ? now - timer.starttime
                            : std::chrono::nanoseconds::zero();
    
    auto time = (timer.ispause)
                    ? std::chrono::duration_cast<std::chrono::nanoseconds>(timer.pausetime) 
                    : timesincestart;
    
    return  (timer.isstart)? time : std::chrono::nanoseconds::zero();
}
} // namespace computil
