#ifndef SYSTEM_GAME_CREATUREMAKEDEADLISTENER_H_
#define SYSTEM_GAME_CREATUREMAKEDEADLISTENER_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {



class CreatureMakeDeadListener : public Listener<gameevent::CreatureMakeDeadEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;

    public:

    CreatureMakeDeadListener();

    void makeCreatureDead(EventBus& events, Entity entity,
        gamecomp::CreatureProgressTimersComponent& timers,
        gamecomp::CreatureLifeComponent& life,
        gamecomp::CreatureBattlerComponent& creature_battler,
        gamecomp::CauseOfDeath causeofdeath);
    
    void update(const gameevent::CreatureMakeDeadEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREMAKEDEADLISTENER_H_
