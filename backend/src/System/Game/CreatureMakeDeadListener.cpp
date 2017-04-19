#include "System/Game/CreatureMakeDeadListener.h"

namespace gamesystem {


CreatureMakeDeadListener::CreatureMakeDeadListener() {}


void CreatureMakeDeadListener::makeCreatureDead(
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


void CreatureMakeDeadListener::update(
    const gameevent::CreatureMakeDeadEvent& event, EntityManager& entities,
    EventBus& events, TimeDelta /*dt*/) {
        
    for(auto entity : entities.view<gamecomp::CreatureProgressTimersComponent, 
            gamecomp::CreatureLifeComponent, gamecomp::CreatureBattlerComponent>()) {
        
        auto& timers = entities.get<gamecomp::CreatureProgressTimersComponent>(entity);
        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);
        auto& creature_battler = entities.get<gamecomp::CreatureBattlerComponent>(entity);

        makeCreatureDead(events, entity, timers, life,
                         creature_battler, event.causeofdeath);
    }
}

} // namespace gamesystem