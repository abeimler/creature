#ifndef SYSTEM_GAME_CREATURESYSTEM_H_
#define SYSTEM_GAME_CREATURESYSTEM_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {


class CreatureSystem : public System {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gameentity::DataManager& datamanager_;
    gamecomputil::ProgressTimerUtil progresstimer_util_{};
    computil::DateTimerUtil datetimer_util_{};

  public:

    CreatureSystem(gameentity::DataManager& datamanager);

    void updateUnhappy(EventBus& events, Entity entity,
                       gamecomp::CreatureProgressTimersComponent& timers,
                       gamecomp::CreatureLifeComponent& life);

    void updateBored(EventBus& events, Entity entity,
                     gamecomp::CreatureProgressTimersComponent& timers,
                     gamecomp::CreatureLifeComponent& life);

    void updateLuck(EventBus& events, Entity entity,
                    gamecomp::CreatureProgressTimersComponent& timers,
                    gamecomp::CreaturePsycheComponent& psyche,
                    gamecomp::CreatureLifeComponent& life);

    void updateHasStatuses(gamecomp::BattlerStatusesComponent& battlerstatuses,
                           gamecomp::CreatureLifeComponent& life);
    
    void updateBMI(gamecomp::CreatureBodyComponent& body,
                   gamecomp::CreatureGeneComponent& gene,
                   gamecomp::CreatureDataComponent& creature_data);

    void updateLifeAttribute(EventBus& events, Entity entity,
                             gamecomp::CreatureProgressTimersComponent& timers,
                             gamecomp::CreatureLifeComponent& life, 
                             gamecomp::CreatureGeneComponent& gene,
                             gamecomp::CreatureBattlerComponent& creature_battler,
                             gamecomp::CreatureDataComponent& creature_data);

    void updateCanGoSleep(gamecomp::CreatureProgressTimersComponent& timers,
                          gamecomp::CreatureLifeComponent& life, 
                          gamecomp::CreatureGeneComponent& gene,
                          gamecomp::CreatureSleepComponent& sleep);

    void updatePsycheValues(gamecomp::CreaturePsycheComponent& psyche);

    void updateCreatureTimers(gamecomp::CreatureProgressTimersComponent& timers,
                              gamecomp::CreatureLifeComponent& life);

    void updateCreatureTimersFactor(gamecomp::CreatureProgressTimersComponent& timers,
                                    gamecomp::CreatureLifeComponent& life);

    
    void update(EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREADDSTATUSSYSTEM_H_
