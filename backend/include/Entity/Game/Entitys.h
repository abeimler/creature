#ifndef ENTITY_GAME_ENTITYS_H_
#define ENTITY_GAME_ENTITYS_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Component/DateTimer.h"

#include "Component/Game/Battler.h"
#include "Component/Game/Creature.h"
#include "Component/Game/CreatureBattler.h"
#include "Component/Game/CreatureGene.h"
#include "Component/Game/CreatureMemory.h"

#include "Entity/Game/DateTimerUtil.h"
#include "Entity/Game/ProgressTimerUtil.h"
#include "Entity/Game/TimerUtil.h"

#include "Entity/EntityCreator.h"

#include "Entity/Game/CreatureBattlerCreator.h"

namespace gameentity {

// Convenience types for our entity system.
using GameComponents = entityx::Components<
    gamecomp::CreatureDataComponent, gamecomp::CreatureProgressTimersComponent,

    gamecomp::BattlerStatusesComponent, gamecomp::BattlerBattleStateComponent,
    gamecomp::BattlerResistsComponent,

    gamecomp::CreatureBattlerComponent,

    gamecomp::CreatureBattlerGeneComponent, gamecomp::CreatureGeneComponent,

    gamecomp::CreatureMemoryComponent, gamecomp::CreaturePersonalityComponent,

    gamecomp::CreatureHungerComponent, gamecomp::CreatureEvolveComponent,
    gamecomp::CreatureSleepComponent, gamecomp::CreatureTrainingComponent,
    gamecomp::CreatureBodilyStateComponent, gamecomp::CreatureBodyComponent,
    gamecomp::CreaturePsycheComponent, gamecomp::CreatureLifeComponent>;


constexpr size_t COLUMNSTORAGE_CAPACITY = 20480;

using EntityManager =
    entityx::EntityX<GameComponents, entityx::ColumnStorage<GameComponents, COLUMNSTORAGE_CAPACITY>>;
template <typename C>
using Component = EntityManager::Component<C>;
using Entity = EntityManager::Entity;
using EntityId = entityx::Id;

typedef std::uint64_t entity_id_t;

inline EntityId to_EntityId(entity_id_t id) {
    return EntityId(id);
}

inline entity_id_t to_EntityId(const EntityId& eid) {
    return eid.id();
}

} // namespace gameentity

namespace std {
template <>
struct hash<const gameentity::Entity> {
    std::size_t operator()(const gameentity::Entity& entity) const {
        return static_cast<std::size_t>(entity.id().index() ^
                                        entity.id().version());
    }
};
}


#endif // ENTITY_GAME_ENTITYS_H_
