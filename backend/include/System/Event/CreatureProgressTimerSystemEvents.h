#ifndef SYSTEM_EVENT_CREATUREPROGRESSTIMERSYSTEMEVENTS_H_
#define SYSTEM_EVENT_CREATUREPROGRESSTIMERSYSTEMEVENTS_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Game/DateTimerUtil.h"
#include "Entity/Game/ProgressTimerUtil.h"
#include "Entity/Game/TimerUtil.h"

#include "Entity/Game/CreatureEntityCreator.h"

namespace gameevent {

struct ProgressTimerCallbackEvent {
    gameentity::Entity entity;
    gamecomp::CreatureProgressTimerCallback type;
    data::CreatureLevel level;

    ProgressTimerCallbackEvent(gameentity::Entity p_entity,
                               gamecomp::CreatureProgressTimerCallback p_type,
                               data::CreatureLevel p_level)
        : entity(p_entity), type(p_type), level(p_level) {}
};

struct ProgressTimerIncrementEvent {
    gameentity::Entity entity;
    gamecomp::CreatureProgressTimerIncrement type;
    data::CreatureLevel level;
    double addvalue;

    ProgressTimerIncrementEvent(gameentity::Entity p_entity,
                                gamecomp::CreatureProgressTimerIncrement p_type,
                                data::CreatureLevel p_level, double p_addvalue)
        : entity(p_entity), type(p_type), level(p_level), addvalue(p_addvalue) {
    }
};

struct ProgressTimerStarvationPhaseEvent {
    gameentity::Entity entity;
    gamecomp::StarvationPhase type;
    data::CreatureLevel level;

    ProgressTimerStarvationPhaseEvent(gameentity::Entity p_entity,
                                      gamecomp::StarvationPhase p_type,
                                      data::CreatureLevel p_level)
        : entity(p_entity), type(p_type), level(p_level) {}
};

struct ProgressTimerShortTermMemoryEvent {
    gameentity::Entity entity;
    gamecomp::CreatureActivity activity;
    data::CreatureLevel level;

    ProgressTimerShortTermMemoryEvent(gameentity::Entity p_entity,
                                      gamecomp::CreatureActivity p_activity,
                                      data::CreatureLevel p_level)
        : entity(p_entity), activity(p_activity), level(p_level) {}
};

struct ProgressTimerMediumTermMemoryEvent {
    gameentity::Entity entity;
    gamecomp::CreatureActivity activity;
    data::CreatureLevel level;

    ProgressTimerMediumTermMemoryEvent(gameentity::Entity p_entity,
                                       gamecomp::CreatureActivity p_activity,
                                       data::CreatureLevel p_level)
        : entity(p_entity), activity(p_activity), level(p_level) {}
};

} // namespace gamesystem

#endif // SYSTEM_EVENT_CREATUREPROGRESSTIMERSYSTEMEVENTS_H_
