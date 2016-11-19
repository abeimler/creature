#include "System/Game/CreatureDoNotingSystem.h"

namespace gamesystem {


CreatureDoNotingSystem::CreatureDoNotingSystem(
    gameentity::DataManager& datamanager)
    : datamanager_(datamanager) {}


void CreatureDoNotingSystem::updateDoNothing(
    EventBus& events, Entity entity,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life) {

    bool isrunaway =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::RunAway);
    bool issleep =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Sleep);
    bool isinhospital =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::InHospital);
    bool isrestinhospital = earr::enum_array_at(
        life.hasstatus, +data::CreatureStatus::RestInHospital);
    bool isrest =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Rest);
    bool istraining =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Training);

    auto& bored_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::Bored);
    gamecomp::ProgressTimer& bored_progresstimer = bored_timer.base;

    if (!isrunaway && !issleep && !isinhospital && !isrestinhospital &&
        !isrest && !istraining) {
        life.isbusy = false;
        emit_event<gameevent::CreatureDoNotingEvent>(events, entity);
    } else {
        life.isbusy = true;
    }

    if (!life.isbusy && bored_progresstimer.timer.isstart) {
        progresstimer_util_.start(bored_progresstimer);
    } else {
        progresstimer_util_.stop(bored_progresstimer);
    }
}


void CreatureDoNotingSystem::update(
    const gameevent::CreatureDoNotingEvent& event, EntityManager& entities,
    EventBus& events, TimeDelta /*dt*/) {
    Component<gamecomp::CreatureProgressTimersComponent> timers;
    Component<gamecomp::CreatureLifeComponent> life;

    for (auto entity : entities.entities_with_components(timers, life)) {
        updateDoNothing(events, entity, *timers.get(), *life.get());
    }
}

} // namespace gamesystem