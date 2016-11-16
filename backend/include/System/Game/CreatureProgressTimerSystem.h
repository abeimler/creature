#ifndef SYSTEM_GAME_CREATUREPROGRESSTIMERSYSTEM_H_
#define SYSTEM_GAME_CREATUREPROGRESSTIMERSYSTEM_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Game/DateTimerUtil.h"
#include "Entity/Game/ProgressTimerUtil.h"
#include "Entity/Game/TimerUtil.h"

#include "Entity/Game/CreatureEntityCreator.h"

#include "System/Events.h"
#include "System/System.h"

namespace gamesystem {

class CreatureProgressTimerSystem : public System {
    private:
    // computil::TimerUtil timer_util_;
    computil::DateTimerUtil datetimer_util_;
    gamecomputil::ProgressTimerUtil progresstimer_util_;

    bool ignortimer_ = false;

    double updateTimer(gamecomp::ProgressTimer& timer,
                       data::CreatureLevel level);



    double updateCallbackTimer(EventBus& events, Entity entity,
                               gamecomp::ProgressTimerCallback& timer,
                               data::CreatureLevel level,
                               gamecomp::CreatureProgressTimerCallback type);

    double updateIncrementTimer(EventBus& events, Entity entity,
                                gamecomp::ProgressTimerIncrement& timer,
                                data::CreatureLevel level,
                                gamecomp::CreatureProgressTimerIncrement type);

    double updateStarvationPhaseTimer(EventBus& events, Entity entity,
                                      gamecomp::ProgressTimerCallback& timer,
                                      data::CreatureLevel level,
                                      gamecomp::StarvationPhase type);

    double updateShortTermMemoryTimer(EventBus& events, Entity entity,
                                      gamecomp::ProgressTimerCallback& timer,
                                      data::CreatureLevel level,
                                      gamecomp::CreatureActivity activity);

    double updateMediumTermMemoryTimer(EventBus& events, Entity entity,
                                       gamecomp::ProgressTimerCallback& timer,
                                       data::CreatureLevel level,
                                       gamecomp::CreatureActivity activity);

    public:
    CreatureProgressTimerSystem() = default;

    void setIgnoreTimer(bool ignortimer) { this->ignortimer_ = ignortimer; }
    bool isIgnoreTimer() const { return this->ignortimer_; }

    void update(EntityManager& entities, EventBus& events,
                TimeDelta dt) override;
};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREPROGRESSTIMERSYSTEM_H_
