#include "System/Game/CreatureBattlerCreatureRecoverSystem.h"

namespace gamesystem {


void CreatureBattlerCreatureRecoverSystem::update(
    const gameevent::CreatureRecoverEvent& /*event*/, EntityManager& entities,
    EventBus& /*events*/, TimeDelta /*dt*/) {
    Component<gamecomp::CreatureBattlerComponent> creature_battler;
    for (auto entity : entities.entities_with_components(creature_battler)) {
        creature_battler->hp = earr::enum_array_at(creature_battler->attr,
                                                   +data::Attribute::MaxHP);
        creature_battler->mp = earr::enum_array_at(creature_battler->attr,
                                                   +data::Attribute::MaxMP);
    }
}
} // namespace gamesystem