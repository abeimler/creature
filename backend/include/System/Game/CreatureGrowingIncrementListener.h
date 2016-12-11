#ifndef SYSTEM_GAME_CREATUREGROWINGINCREMENTLISTENER_H_
#define SYSTEM_GAME_CREATUREGROWINGINCREMENTLISTENER_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {



class CreatureGrowingIncrementListener : public Listener<gameevent::ProgressTimerIncrementEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;

    public:

    CreatureGrowingIncrementListener();

    void updateBodySize(const gameevent::ProgressTimerIncrementEvent& increment_event,
                        gamecomp::CreatureBodyComponent& body,
                        gamecomp::CreatureGeneComponent& gene);


    
    void update(const gameevent::ProgressTimerIncrementEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREGROWINGINCREMENTLISTENER_H_
