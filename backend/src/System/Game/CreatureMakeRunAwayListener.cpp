#include "System/Game/CreatureMakeRunAwayListener.h"

namespace gamesystem {


CreatureMakeRunAwayListener::CreatureMakeRunAwayListener() {}


void CreatureMakeRunAwayListener::makeCreaturerRunAway(
    EventBus& events, Entity entity,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life,
    gamecomp::CauseOfRunAway causeofrunaway, gamecomp::waittime_t waittime) {
    bool isrunaway =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::RunAway);


    if (!isrunaway) {
        emit_event<gameevent::CreatureAddStatusEvent>(
            events, entity, +data::CreatureStatus::RunAway);
        life.causeofrunaway = causeofrunaway;

        auto& runaway_timer = earr::enum_array_at(
            timers.timer, +gamecomp::CreatureProgressTimer::RunAway);
        gamecomp::ProgressTimer& runaway_progresstimer = runaway_timer;

        runaway_progresstimer.waittime.fill(waittime);
        progresstimer_util_.restart(runaway_progresstimer);

        emit_event<gameevent::CreatureDoActivityEvent>(
            events, entity, gamecomp::CreatureActivity::RunAway);
    }
}

void CreatureMakeRunAwayListener::update(
    const gameevent::CreatureMakeRunAwayEvent& event, EntityManager& entities,
    EventBus& events, TimeDelta /*dt*/) {
    Component<gamecomp::CreatureProgressTimersComponent> timers;
    Component<gamecomp::CreatureLifeComponent> life;

    for (auto entity : entities.entities_with_components(timers, life)) {
        makeCreaturerRunAway(events, entity, *timers.get(), *life.get(),
                             event.causeofrunaway, event.waittime);
    }
}

} // namespace gamesystem