#include "System/Game/CreatureDoNotingSystem.h"

namespace gamesystem {


CreatureDoNotingSystem::CreatureDoNotingSystem() {}


void CreatureDoNotingSystem::updateDoNothing(
    EventBus& events, Entity entity,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life) {

    auto isrunaway =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::RunAway);
    auto issleep =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Sleep);
    auto isinhospital =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::InHospital);
    auto isrestinhospital = earr::enum_array_at(
        life.hasstatus, +data::CreatureStatus::RestInHospital);
    auto isrest =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Rest);
    auto istraining =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Training);

    auto& bored_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::Bored);
    gamecomp::ProgressTimer& bored_progresstimer = bored_timer.base;

    if (!isrunaway && !issleep && !isinhospital && !isrestinhospital &&
        !isrest && !istraining) {
        life.isbusy = false;
    } else {
        life.isbusy = true;
    }

    if (!life.isbusy && !bored_progresstimer.timer.isstart) {
        emit_event<gameevent::CreatureDoNotingEvent>(events, entity);
        progresstimer_util_.start(bored_progresstimer);
    } else {
        progresstimer_util_.stop(bored_progresstimer);
    }
}


void CreatureDoNotingSystem::update(EntityManager& entities, EventBus& events,
                                    TimeDelta /*dt*/) {
                                        
    for(auto entity : entities.view<gamecomp::CreatureProgressTimersComponent, 
            gamecomp::CreatureLifeComponent>()) {
        
        auto& timers = entities.get<gamecomp::CreatureProgressTimersComponent>(entity);
        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);
        
        updateDoNothing(events, entity, timers, life);
    }
}

} // namespace gamesystem