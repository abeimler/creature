#include "System/Game/CreatureDigestionSystem.h"

namespace gamesystem {

CreatureDigestionSystem::CreatureDigestionSystem() {}


void CreatureDigestionSystem::updatePauseDigestionHungry(
    gamecomp::CreatureProgressTimersComponent& timers) {

    auto& hungry_timer = earr::enum_array_at(timers.timer, 
        +gamecomp::CreatureProgressTimer::Hungry);
    gamecomp::ProgressTimer& hungry_progresstimer = hungry_timer;
    // float hungry_value = hungry_progresstimer.value;
    // float hungry_overlayvalue = hungry_progresstimer.overlayvalue;
    bool ishungry = hungry_progresstimer.isfull;

    auto& digistation_timer = earr::enum_array_at(timers.callback, 
        +gamecomp::CreatureProgressTimerCallback::Digestion);
    gamecomp::ProgressTimer& digistation_progresstimer = digistation_timer.base;

    auto& pause_digistation_timer = earr::enum_array_at(timers.callback,
        +gamecomp::CreatureProgressTimerCallback::PauseDigestionHungry);
    gamecomp::ProgressTimer& pause_digistation_progresstimer =
        pause_digistation_timer.base;

    if (ishungry) {
        progresstimer_util_.start(pause_digistation_progresstimer);
    } else {
        progresstimer_util_.stop(pause_digistation_progresstimer);
        progresstimer_util_.start(digistation_progresstimer);
        progresstimer_util_.unpause(digistation_progresstimer);
    }
}

void CreatureDigestionSystem::updateFullPoopStack(
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureHungerComponent& hunger,
    gamecomp::CreatureGeneComponent& gene) {

    if (hunger.poopstack < gene.max_poopstack) {
        auto& full_poop_stack_timer = earr::enum_array_at(timers.callback,
            +gamecomp::CreatureProgressTimerCallback::FullPoopStack);
        gamecomp::ProgressTimer& full_poop_stack_progresstimer =
            full_poop_stack_timer.base;

        progresstimer_util_.stop(full_poop_stack_progresstimer);
    } else {
        // start progresstimer by event, see CreatureDigestionCallbackSystem::fullPoopStack
    }
}


void CreatureDigestionSystem::update(EntityManager& entities, EventBus& events, TimeDelta /*dt*/) {
    Component<gamecomp::CreatureProgressTimersComponent> timers;
    Component<gamecomp::CreatureHungerComponent> hunger;
    Component<gamecomp::CreatureGeneComponent> gene;

    for (auto entity : entities.entities_with_components(timers, hunger, gene)) {

        updatePauseDigestionHungry(*timers.get());
        updateFullPoopStack(*timers.get(), *hunger.get(), *gene.get());
        
    }
}

} // namespace gamesystem