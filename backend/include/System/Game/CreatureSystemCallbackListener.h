#ifndef SYSTEM_GAME_CREATURESYSTEMCALLBACKLISTENER_H_
#define SYSTEM_GAME_CREATURESYSTEMCALLBACKLISTENER_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {

class CreatureSystemCallbackListener : public Listener<gameevent::ProgressTimerCallbackEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gamecomputil::ProgressTimerUtil progresstimer_util_{};
    computil::DateTimerUtil datetimer_util_{};

  public:
    CreatureSystemCallbackListener();

    void runAwayUnhappyStart(EventBus& events, Entity entity,
                              gamecomp::CreatureProgressTimersComponent& timers,
                              gamecomp::CreatureLifeComponent& life);

    void updateBored(EventBus& events, Entity entity,
                      gamecomp::CreatureProgressTimersComponent& timers,
                      gamecomp::CreatureLifeComponent& life);

    void runAwayUnhappy(EventBus& events, Entity entity,
                        gamecomp::CreatureProgressTimersComponent& timers);

    
    void update(const gameevent::ProgressTimerCallbackEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATURESYSTEMCALLBACKLISTENER_H_
