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
    Component<gamecomp::CreatureBattlerComponent> creature_battler;
    for (auto entity : entities.entities_with_components(creature_battler)) {
        recover(*creature_battler.get());
    }
}

} // namespace gamesystem