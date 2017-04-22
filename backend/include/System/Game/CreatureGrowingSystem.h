#ifndef SYSTEM_GAME_CREATUREGROWINGSYSTEM_H_
#define SYSTEM_GAME_CREATUREGROWINGSYSTEM_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {



class CreatureGrowingSystem : public System {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gamecomputil::ProgressTimerUtil progresstimer_util_{};
    computil::DateTimerUtil datetimer_util_{};

  public:

    CreatureGrowingSystem();

    
    void updateGrowingTimer(gamecomp::CreatureProgressTimersComponent& timers);
    
    void update(EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREGROWINGSYSTEM_H_
