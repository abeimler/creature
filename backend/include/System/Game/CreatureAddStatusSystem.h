#ifndef SYSTEM_GAME_CREATUREADDSTATUSSYSTEM_H_
#define SYSTEM_GAME_CREATUREADDSTATUSSYSTEM_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {



class CreatureAddStatusSystem : public Listener<gameevent::CreatureAddStatusEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gameentity::DataManager& datamanager_;
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;

    public:

    CreatureAddStatusSystem(gameentity::DataManager& datamanager);

    void addCreatureStatus(EventBus& events, Entity entity,
                           gamecomp::BattlerStatusesComponent& battlerstatuses,
                           gamecomp::CreatureBodilyStateComponent& bodilystate,
                           data::CreatureStatus addcreaturestatus);
    
    void update(const gameevent::CreatureAddStatusEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREADDSTATUSSYSTEM_H_
