#ifndef SYSTEM_GAME_CREATUREBATTLERSYSTEM_H_
#define SYSTEM_GAME_CREATUREBATTLERSYSTEM_H_


#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "Entity/Game/DateTimerUtil.h"
#include "Entity/Game/ProgressTimerUtil.h"
#include "Entity/Game/TimerUtil.h"

#include "Entity/Game/CreatureEntityCreator.h"

#include "System/Events.h"
#include "System/System.h"

namespace gamesystem {



class CreatureBattlerSystem : public System {
    private:
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;
    gameentity::CreatureEntityCreator creaturecreator_;
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gameentity::DataManager& datamanager_;

    public:
    static constexpr int DEFAULT_HITRATE = 90;
    static constexpr int DEFAULT_CRITICAL_HITRATE = 30;
    static constexpr int DEFAULT_EVARATE = 20;

    CreatureBattlerSystem(gameentity::DataManager& datamanager);


    void updateCreatureBattlerAttribute(
        Component<gamecomp::CreatureBattlerComponent>& creature_battler,
        Component<gamecomp::BattlerStatusesComponent>& battler_statuses,
        Component<gamecomp::CreatureDataComponent>& creature_data);

    void updateCreatureHitRate(
        Component<gamecomp::CreatureBattlerComponent>& creature_battler,
        Component<gamecomp::BattlerStatusesComponent>& battler_statuses,
        Component<gamecomp::CreatureDataComponent>& creature_data);

    void updateCreatureCriticalHitRate(
        Component<gamecomp::CreatureBattlerComponent>& creature_battler,
        Component<gamecomp::BattlerStatusesComponent>& battler_statuses,
        Component<gamecomp::CreatureDataComponent>& creature_data);

    void updateCreatureEvaRate(
        Component<gamecomp::CreatureBattlerComponent>& creature_battler,
        Component<gamecomp::BattlerStatusesComponent>& battler_statuses,
        Component<gamecomp::CreatureDataComponent>& creature_data);

    void updateCreatureStatusRestriction(
        Component<gamecomp::CreatureBattlerComponent>& creature_battler,
        Component<gamecomp::BattlerStatusesComponent>& battler_statuses,
        Component<gamecomp::CreatureDataComponent>& creature_data);

    void update(EntityManager& entities, EventBus& events,
                TimeDelta dt) override;
};

} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREBATTLERSYSTEM_H_
