#ifndef COMPONENT_GAME_PROGRESSTIMERINCREMENT_H_
#define COMPONENT_GAME_PROGRESSTIMERINCREMENT_H_

#include "Component/Game/ProgressTimer.h"

namespace gamecomp {

struct ProgressTimerIncrement {
    ProgressTimer base;

    progresstimer_percent_t addvalue_per_percent = 1.0;
    bool isendless = false;
};
} // namespace gamecomp

#endif // COMPONENT_GAME_PROGRESSTIMERINCREMENT_H_
