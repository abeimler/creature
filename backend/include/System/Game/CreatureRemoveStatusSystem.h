#ifndef SYSTEM_GAME_CREATUREREMOVESTATUSSYSTEM_H_
#define SYSTEM_GAME_CREATUREREMOVESTATUSSYSTEM_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {



class CreatureRemoveStatusSystem : public Listener<gameevent::CreatureRemoveStatusEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gameentity::DataManager& datamanager_;
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;

    public:

    CreatureRemoveStatusSystem(gameentity::DataManager& datamanager_);

    void removeCreatureStatus(EventBus& events, Entity entity,
                              gamecomp::BattlerStatusesComponent& battlerstatuses,
                              gamecomp::CreatureBodilyStateComponent& bodilystate,
                              data::CreatureStatus removecreaturestatus);
    
    void update(const gameevent::CreatureRemoveStatusEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREREMOVESTATUSSYSTEM_H_
