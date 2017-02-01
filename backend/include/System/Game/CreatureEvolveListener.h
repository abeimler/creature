#ifndef SYSTEM_GAME_CREATUREEVOLVELISTENER_H_
#define SYSTEM_GAME_CREATUREEVOLVELISTENER_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {


class CreatureEvolveListener : public Listener<gameevent::CreatureEvolveEvent> {
    private:
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;
    gameentity::CreatureEntityCreator creaturecreator_;
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gameentity::DataManager& datamanager_;


    public:

    static constexpr data::luck_t ADD_LUCK_BYGOODEVOLUTION = 5.0;
    static constexpr data::disc_t ADD_DISC_BYGOODEVOLUTION = 5.0;

    static constexpr data::luck_t ADD_LUCK_BYBADEVOLUTION = -10.0;
    static constexpr data::disc_t ADD_DISC_BYBADEVOLUTION = -5.0;
    
    static constexpr gamecomp::progresstimer_percent_t GROWING_PROGRESS_AFTER_GOOD_EVOLVE_PERCENT = 80.0;
    static constexpr gamecomp::progresstimer_percent_t GROWING_PROGRESS_AFTER_BAD_EVOLVE_PERCENT = 60.0;

    static constexpr gamecomp::lifetime_t ADD_MAXLIFETIME_BYGOODEVOLUTION = std::chrono::hours(24);
    static constexpr gamecomp::lifetime_t ADD_MAXLIFETIME_BYBADEVOLUTION = std::chrono::hours(12);


    void evolution(gameentity::Entity entity, EventBus& events,
        const gameevent::CreatureEvolveEvent& evolve_event,
        gamecomp::CreatureProgressTimersComponent& timers,
        gamecomp::CreatureDataComponent& creature_data,
        gamecomp::CreatureGeneComponent& gene,
        gamecomp::CreatureBattlerGeneComponent& creature_battlergene,
        gamecomp::CreatureBattlerComponent& creature_battler,
        gamecomp::CreatureTrainingComponent& training,
        gamecomp::CreatureBodyComponent& body,
        gamecomp::CreatureBodilyStateComponent& bodilystate,
        gamecomp::CreaturePsycheComponent& psyche,
        gamecomp::CreatureLifeComponent& life,
        gamecomp::CreatureEvolveComponent& evolve);

    CreatureEvolveListener(gameentity::DataManager& datamanager);

    
    void update(const gameevent::CreatureEvolveEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREEVOLVELISTENER_H_
