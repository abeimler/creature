#ifndef SYSTEM_GAME_CREATURERUNAWAYSYSTEM_H_
#define SYSTEM_GAME_CREATUREEUNAWAYSYSTEM_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {



class CreatureRunAwaySystem : public Listener<gameevent::CreatureMakeRunAwayEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gameentity::DataManager& datamanager_;
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;

    public:

    CreatureRunAwaySystem(gameentity::DataManager& datamanager);

    void makeCreaturerRunAway(EventBus& events, Entity entity,
                              gamecomp::CreatureProgressTimersComponent& timers,
                              gamecomp::CreatureLifeComponent& life,
                              gamecomp::CauseOfRunAway causeofrunaway,
                              gamecomp::waittime_t waittime);
    
    void update(const gameevent::CreatureMakeRunAwayEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREEUNAWAYSYSTEM_H_
