#ifndef SYSTEM_GAME_CREATUREDIGESTIONCALLBACKLISTENER_H_
#define SYSTEM_GAME_CREATUREDIGESTIONCALLBACKLISTENER_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {



class CreatureDigestionCallbackListener : public Listener<gameevent::ProgressTimerCallbackEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;

    public:
    static constexpr data::percent_rate_t RATE_UNLUCK_BY_MORETHENMAXPOOPSTACK = 60;
    static constexpr data::luck_t UNLUCK_BY_MORETHENMAXPOOPSTACK = 5.0;
    static constexpr data::luck_t UNLUCK_BY_MAXPOOPSTACK = 5.0;
    static constexpr data::disc_t UNDISC_BY_MAXPOOPSTACK = 5.0;
    static constexpr gamecomp::progresstimer_percent_t PAUSE_DIGESTION_BY_HUNGRY_OVERLAYVALUE = 200.0;

    CreatureDigestionCallbackListener();

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

    void illByFullPoopStack(Entity entity, EventBus& events, gamecomp::CreatureGeneComponent& gene);


    
    void update(const gameevent::ProgressTimerCallbackEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREDIGESTIONCALLBACKLISTENER_H_
