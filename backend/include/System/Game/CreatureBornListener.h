#ifndef SYSTEM_GAME_CREATUREBORNLISTENER_H_
#define SYSTEM_GAME_CREATUREBORNLISTENER_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {


class CreatureBornListener : public Listener<gameevent::CreatureBornEvent> {
    private:
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;
    gameentity::CreatureEntityCreator creaturecreator_;
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gameentity::DataManager& datamanager_;


    public:
    
    static constexpr gamecomp::progresstimer_percent_t GROWING_PROGRESS_AFTER_BORN_PERCENT = 80;


    CreatureBornListener(gameentity::DataManager& datamanager);

    void born(gameentity::Entity entity, EventBus& events,
                gamecomp::CreatureProgressTimersComponent& timers,
                gamecomp::CreatureTrainingComponent& training,
                gamecomp::CreatureGeneComponent& gene, gamecomp::CreatureBodyComponent& body,
                gamecomp::CreatureBodilyStateComponent& bodilystate,
                gamecomp::CreatureLifeComponent& life);

    
    void update(const gameevent::CreatureBornEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREBORNLISTENER_H_
