#include "System/Game/CreatureRemoveRunAwayListener.h"

namespace gamesystem {


CreatureRemoveRunAwayListener::CreatureRemoveRunAwayListener() {}


void CreatureRemoveRunAwayListener::removeCreaturerRunAway(
    EventBus& events, Entity entity,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life) {
    bool isrunaway =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::RunAway);


    if(isrunaway){
        emit_event<gameevent::CreatureRemoveStatusEvent>(
            events, entity, +data::CreatureStatus::RunAway);
        life.causeofrunaway = gamecomp::CauseOfRunAway::NotRunAway;

        auto& runaway_timer = earr::enum_array_at(
            timers.timer, +gamecomp::CreatureProgressTimer::RunAway);
        gamecomp::ProgressTimer& runaway_progresstimer = runaway_timer;

        progresstimer_util_.stop(runaway_progresstimer);

        emit_event<gameevent::CreatureDoActivityEvent>(
            events, entity, gamecomp::CreatureActivity::ComeBackFromRunAway);
    }
}

void CreatureRemoveRunAwayListener::update(
    const gameevent::CreatureRemoveRunAwayEvent& event, EntityManager& entities,
    EventBus& events, TimeDelta /*dt*/) {
    Component<gamecomp::CreatureProgressTimersComponent> timers;
    Component<gamecomp::CreatureLifeComponent> life;

    for (auto entity : entities.entities_with_components(timers, life)) {
        removeCreaturerRunAway(events, entity, *timers.get(), *life.get());
    }
}

} // namespace gamesystem