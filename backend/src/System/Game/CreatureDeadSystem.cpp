#include "System/Game/CreatureDeadSystem.h"

namespace gamesystem {


CreatureDeadSystem::CreatureDeadSystem() {}


void CreatureDeadSystem::makeCreatureDead(
    EventBus& events, Entity entity,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life,
    gamecomp::CreatureBattlerComponent& creature_battler,
    gamecomp::CauseOfDeath causeofdeath) {
    if (!life.isdead &&
        !earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Dead)) {
        emit_event<gameevent::CreatureRemoveRunAwayEvent>(events, entity);
        emit_event<gameevent::CreatureAddStatusEvent>(
            events, entity, data::CreatureStatus::Dead);

        for (auto& timer : timers.timer) {
            this->progresstimer_util_.pause(timer);
        }
        for (auto& timer : timers.callback) {
            this->progresstimer_util_.stop(timer.base);
        }
        for (auto& timer : timers.increment) {
            this->progresstimer_util_.stop(timer.base);
        }
        this->datetimer_util_.pause(timers.lifetimer);

        creature_battler.hp = 0;
        creature_battler.mp = 0;

        life.causeofdeath = causeofdeath;
        life.isdead = true;
    }
}


void CreatureDeadSystem::update(const gameevent::CreatureMakeDeadEvent& event,
                                EntityManager& entities, EventBus& events,
                                TimeDelta /*dt*/) {
    Component<gamecomp::CreatureProgressTimersComponent> timers;
    Component<gamecomp::CreatureLifeComponent> life;
    Component<gamecomp::CreatureBattlerComponent> creature_battler;

    for (auto entity :
         entities.entities_with_components(timers, life, creature_battler)) {
        makeCreatureDead(events, entity, *timers.get(), *life.get(),
                         *creature_battler.get(), event.causeofdeath);
    }
}

} // namespace gamesystem