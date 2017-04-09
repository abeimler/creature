#include "System/Game/CreatureMakeRunAwayListener.h"

namespace gamesystem {


CreatureMakeRunAwayListener::CreatureMakeRunAwayListener() {}


void CreatureMakeRunAwayListener::makeCreaturerRunAway(
    EventBus& events, Entity entity,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life,
    gamecomp::CauseOfRunAway causeofrunaway, gamecomp::waittime_t waittime) {
    auto isrunaway =
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

    for(auto entity : entities.view<gamecomp::CreatureProgressTimersComponent, 
            gamecomp::CreatureLifeComponent>()) {
        
        auto& timers = entities.get<gamecomp::CreatureProgressTimersComponent>(entity);
        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);

        makeCreaturerRunAway(events, entity, timers, life,
                             event.causeofrunaway, event.waittime);
    }
}

} // namespace gamesystem