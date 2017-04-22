#ifndef SYSTEM_GAME_CREATUREDIGESTIONSYSTEM_H_
#define SYSTEM_GAME_CREATUREDIGESTIONSYSTEM_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {



class CreatureDigestionSystem : public System {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gamecomputil::ProgressTimerUtil progresstimer_util_{};
    computil::DateTimerUtil datetimer_util_{};

  public:

    CreatureDigestionSystem();

    
    void updatePauseDigestionHungry(
        gamecomp::CreatureProgressTimersComponent& timers);

    
    void updateFullPoopStack(
        gamecomp::CreatureProgressTimersComponent& timers,
        gamecomp::CreatureHungerComponent& hunger,
        gamecomp::CreatureGeneComponent& gene);
    
    void update(EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREDIGESTIONCALLBACKSYSTEM_H_
