#ifndef SYSTEM_GAME_CREATUREDONOTINGSYSTEM_H_
#define SYSTEM_GAME_CREATUREDONOTINGSYSTEM_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {


class CreatureDoNotingSystem : public Listener<gameevent::CreatureDoNotingEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gameentity::DataManager& datamanager_;
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;

    public:

    CreatureDoNotingSystem(gameentity::DataManager& datamanager);

    void updateDoNothing(EventBus& events, Entity entity,
                         gamecomp::CreatureProgressTimersComponent& timers,
                         gamecomp::CreatureLifeComponent& life);
    
    void update(const gameevent::CreatureDoNotingEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};

} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREDONOTINGSYSTEM_H_
