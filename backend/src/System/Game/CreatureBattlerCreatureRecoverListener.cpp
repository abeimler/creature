#include "System/Game/CreatureBattlerCreatureRecoverListener.h"

namespace gamesystem {


void CreatureBattlerCreatureRecoverListener::recover(
    gamecomp::CreatureBattlerComponent& creature_battler) {
    creature_battler.hp =
        earr::enum_array_at(creature_battler.attr, +data::Attribute::MaxHP);
    creature_battler.mp =
        earr::enum_array_at(creature_battler.attr, +data::Attribute::MaxMP);
}

void CreatureBattlerCreatureRecoverListener::update(
    const gameevent::CreatureRecoverEvent& /*event*/, EntityManager& entities,
    EventBus& /*events*/, TimeDelta /*dt*/) {

    for(auto entity : entities.view<gamecomp::CreatureBattlerComponent>()) {
        auto& creature_battler = entities.get<gamecomp::CreatureBattlerComponent>(entity);

        recover(creature_battler);
    }
}

} // namespace gamesystem