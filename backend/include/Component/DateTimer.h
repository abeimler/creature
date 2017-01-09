#ifndef COMPONENT_DATETIMER_H_
#define COMPONENT_DATETIMER_H_

#include "Component/Basic.h"

namespace comp {

using timertime_t = std::chrono::nanoseconds;
using ticks_t = std::chrono::milliseconds;

using option_t = data::option_t;
using time_factor_t = ts::double_t;

/// Simple Timer
struct Timer {
    option_t isstart = false;
    option_t ispause = false;

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

    option_t isstart = false;
    option_t ispause = false;

    /// realTime, wird benutzt um die starttime und pausetime zu setzen,
    /// Millisekunden (millisec) seit 01.01.1970 (UTC)
    ticks_t realtime;

    /// realTime Faktor, realTime += timer_time * realTimeFactor
    time_factor_t realtime_factor = 1.0;

    ticks_t starttime;
    ticks_t pausetime;
};
} // namespace comp

#endif // COMPONENT_DATETIMER_H_
