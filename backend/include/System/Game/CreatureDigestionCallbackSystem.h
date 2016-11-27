#ifndef SYSTEM_GAME_CREATURERUNAWAYSYSTEM_H_
#define SYSTEM_GAME_CREATUREEUNAWAYSYSTEM_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {



class CreatureDigestionCallbackSystem : public Listener<gameevent::ProgressTimerCallbackEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;

    public:
    constexpr gamecomp::counter_t RATE_UNLUCK_BY_MORETHENMAXPOOPSTACK = 60;
    constexpr data::luck_t UNLUCK_BY_MORETHENMAXPOOPSTACK = 5.0;
    constexpr data::luck_t UNLUCK_BY_MAXPOOPSTACK = 5.0;
    constexpr data::disc_t UNDISC_BY_MAXPOOPSTACK = 5.0;
    constexpr gamecomp::progresstimer_percent_t PAUSE_DIGISTATION_BY_HUNGRY_OVERLAYVALUE = 200.0;

    CreatureDigestionCallbackSystem();

    void makePoop(EventBus& events, Entity entity,
                    gamecomp::CreatureProgressTimersComponent& timers,
                    gamecomp::CreatureHungerComponent& hunger,
                    gamecomp::CreatureGeneComponent& gene, gamecomp::CreatureBodyComponent& body,
                    gamecomp::CreaturePsycheComponent& psyche, bool usetoilet);

    void lostWeightbyStool(
        gamecomp::CreatureBodyComponent& body, gamecomp::CreatureGeneComponent& gene);

    void fullPoopStack(
        gamecomp::CreatureProgressTimersComponent& timers,
        gamecomp::CreatureHungerComponent& hunger,
        gamecomp::CreatureGeneComponent& gene,
        gamecomp::CreaturePsycheComponent& psyche);

    void pauseDigestionbyHunger(
        gamecomp::CreatureProgressTimersComponent& timers);

    void illByFullPoopStack(Entity entity, EventBus& events);


    
    void update(const gameevent::CreatureMakeRunAwayEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREEUNAWAYSYSTEM_H_
