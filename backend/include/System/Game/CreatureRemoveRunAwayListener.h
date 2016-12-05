#ifndef SYSTEM_GAME_CREATUREREMOVERUNAWAYLISTENER_H_
#define SYSTEM_GAME_CREATUREREMOVERUNAWAYLISTENER_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {



class CreatureRemoveRunAwayListener : public Listener<gameevent::CreatureRemoveRunAwayEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;

    public:

    CreatureRemoveRunAwayListener();

    void removeCreaturerRunAway(EventBus& events, Entity entity,
                                gamecomp::CreatureProgressTimersComponent& timers,
                                gamecomp::CreatureLifeComponent& life);
    
    void update(const gameevent::CreatureRemoveRunAwayEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREREMOVERUNAWAYLISTENER_H_
