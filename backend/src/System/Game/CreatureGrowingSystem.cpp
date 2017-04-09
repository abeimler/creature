#include "System/Game/CreatureGrowingSystem.h"

namespace gamesystem {

CreatureGrowingSystem::CreatureGrowingSystem() {}


void CreatureGrowingSystem::updateGrowingTimer(gamecomp::CreatureProgressTimersComponent& timers) {

    auto& growing_timer = earr::enum_array_at(timers.increment, 
        +gamecomp::CreatureProgressTimerIncrement::Growing);
    gamecomp::ProgressTimer& growing_progresstimer = growing_timer.base;
    auto growing_value = growing_progresstimer.value;

    if (!growing_progresstimer.timer.ispause && growing_progresstimer.isfull && growing_value >= 100.0) {
        this->progresstimer_util_.pause(growing_progresstimer);
    } else if (growing_value < 100.0 && !growing_progresstimer.timer.isstart) {
        this->progresstimer_util_.start(growing_progresstimer);
        this->progresstimer_util_.unpause(growing_progresstimer);
    }
}



void CreatureGrowingSystem::update(EntityManager& entities, EventBus& events, TimeDelta /*dt*/) {
    for(auto entity : entities.view<gamecomp::CreatureProgressTimersComponent>()) {
        
        auto& timers = entities.get<gamecomp::CreatureProgressTimersComponent>(entity);

        updateGrowingTimer(timers);
    }
}

} // namespace gamesystem