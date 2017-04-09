#ifndef ENTITY_GAME_ENTITYS_H_
#define ENTITY_GAME_ENTITYS_H_

#include "basic.h"

#include <registry.hpp>

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
using GameComponents = entt::ComponentPool<
    gamecomp::CreatureDataComponent, gamecomp::CreatureProgressTimersComponent,

    gamecomp::BattlerStatusesComponent, gamecomp::BattlerBattleStateComponent,
    gamecomp::BattlerResistsComponent,

    gamecomp::CreatureBattlerComponent,

    gamecomp::CreatureBattlerGeneComponent, gamecomp::CreatureGeneComponent,

    gamecomp::CreatureMemoryComponent, gamecomp::CreaturePersonalityComponent,

    gamecomp::CreatureHungerComponent, gamecomp::CreatureEvolveComponent,
    gamecomp::CreatureSleepComponent, gamecomp::CreatureTrainingComponent,
    gamecomp::CreatureBodilyStateComponent, gamecomp::CreatureBodyComponent,
    gamecomp::CreaturePsycheComponent, gamecomp::CreatureLifeComponent
>;



using EntityManager = entt::Registry<GameComponents>;

template <typename C>
using Component = C;

using Entity = EntityManager::entity_type;

} // namespace gameentity

#endif // ENTITY_GAME_ENTITYS_H_
