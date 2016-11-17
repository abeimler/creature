#ifndef COMPONENT_GAME_PROGRESSTIMERCALLBACK_H_
#define COMPONENT_GAME_PROGRESSTIMERCALLBACK_H_

#include "Component/Game/ProgressTimer.h"

namespace gamecomp {

struct ProgressTimerCallback {
    ProgressTimer base;

    progresstimer_percent_t oldvalue = 0.0;
    bool isendless = false;
};
} // namespace gamecomp

#endif // COMPONENT_GAME_PROGRESSTIMERCALLBACK_H_
