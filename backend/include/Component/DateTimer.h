#ifndef COMPONENT_DATETIMER_H_
#define COMPONENT_DATETIMER_H_

#include "Component/Basic.h"

namespace comp {

using timertime_t = std::chrono::nanoseconds;
using ticks_t = std::chrono::milliseconds;

/// Simple Timer
struct Timer {
    bool isstart = false;
    bool ispause = false;

    timertime_t starttime;
    timertime_t pausetime;
};

/**
 * Timer als DateTime (Timer mit Tage, Monate, und Jahre)
 * Die Zeit selber kann mit den RealTime Factor manipuliert werden.
 * Der RealTime ist die interen Zeit angabe für "now",
 * dieser kann gesetzt werden um die Zeit zu manipuluieren.
 */
struct DateTimer {
    /// Echzeit Timer um den realTime z.b. +1 sec hinzuzufügen wenn beim
    /// Timer 1 sec vergangen ist
    Timer realtimer;

    bool isstart = false;
    bool ispause = false;

    /// realTime, wird benutzt um die starttime und pausetime zu setzen,
    /// Millisekunden (millisec) seit 01.01.1970 (UTC)
    ticks_t realtime;

    /// realTime Faktor, realTime += timer_time * realTimeFactor
    double realtime_factor = 1.0;

    ticks_t starttime;
    ticks_t pausetime;
};
} // namespace comp

#endif // COMPONENT_DATETIMER_H_
