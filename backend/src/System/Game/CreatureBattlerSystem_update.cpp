#include "System/Game/CreatureBattlerSystem.h"

namespace gamesystem {

void CreatureBattlerSystem::update(EntityManager& entities,
                                   EventBus& events,
                                   TimeDelta dt) {

    Component<gamecomp::CreatureDataComponent> creature_data;
    Component<gamecomp::CreatureBattlerComponent> creature_battler;
    Component<gamecomp::BattlerStatusesComponent> battler_statuses;

    for (auto entity : entities.entities_with_components(creature_data, creature_battler, battler_statuses)) {
        this->updateCreatureBattlerAttribute(creature_battler, battler_statuses,
                                             creature_data);

        this->updateCreatureHitRate(creature_battler, battler_statuses,
                                    creature_data);

        this->updateCreatureCriticalHitRate(creature_battler, battler_statuses,
                                            creature_data);

        this->updateCreatureEvaRate(creature_battler, battler_statuses,
                                    creature_data);

        this->updateCreatureStatusRestriction(creature_battler,
                                              battler_statuses, creature_data);
    }
}

} // namespace gamesystem
