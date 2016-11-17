#ifndef SYSTEM_EVENT_CREATURESYSTEM_H_
#define SYSTEM_EVENT_CREATURESYSTEM_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Game/DateTimerUtil.h"
#include "Entity/Game/ProgressTimerUtil.h"
#include "Entity/Game/TimerUtil.h"

#include "Entity/Game/CreatureEntityCreator.h"

namespace gameevent {

struct CreatureAddStatusEvent {
    gameentity::Entity entity;
    data::CreatureStatus addstatus;

    CreatureAddStatusEvent(gameentity::Entity p_entity,
                           data::CreatureStatus p_addstatus)
        : entity(p_entity), addstatus(p_addstatus) {}
};

struct CreatureRemoveStatusEvent {
    gameentity::Entity entity;
    data::CreatureStatus removestatus;

    CreatureRemoveStatusEvent(gameentity::Entity p_entity,
                              data::CreatureStatus p_removestatus)
        : entity(p_entity), removestatus(p_removestatus) {}
};

struct CreatureDoNotingEvent {
    gameentity::Entity entity;

    explicit CreatureDoNotingEvent(gameentity::Entity p_entity)
        : entity(p_entity) {}
};

struct CreatureMakeDeadEvent {
    gameentity::Entity entity;
    gamecomp::CauseOfDeath causeofdeath;

    CreatureMakeDeadEvent(gameentity::Entity p_entity,
                          gamecomp::CauseOfDeath p_causeofdeath)
        : entity(p_entity), causeofdeath(p_causeofdeath) {}
};

struct CreatureMakeRunAwayEvent {
    gameentity::Entity entity;
    gamecomp::CauseOfRunAway causeofrunaway;
    gamecomp::waittime_t waittime;

    CreatureMakeRunAwayEvent(gameentity::Entity p_entity,
                             gamecomp::CauseOfRunAway p_causeofrunaway,
                             gamecomp::waittime_t p_waittime)
        : entity(p_entity)
        , causeofrunaway(p_causeofrunaway)
        , waittime(p_waittime) {}
};

struct CreatureRemoveRunAwayEvent {
    gameentity::Entity entity;

    explicit CreatureRemoveRunAwayEvent(gameentity::Entity p_entity)
        : entity(p_entity) {}
};

struct CreatureDoActivityEvent {
    gameentity::Entity entity;
    gamecomp::CreatureActivity activity;

    CreatureDoActivityEvent(gameentity::Entity p_entity,
                            gamecomp::CreatureActivity p_activity)
        : entity(p_entity), activity(p_activity) {}
};

struct CreatureHasLevelUpEvent {
    gameentity::Entity entity;
    data::lvl_t oldlvl;
    data::lvl_t newlvl;

    explicit CreatureHasLevelUpEvent(gameentity::Entity p_entity, 
                                     data::lvl_t p_oldlvl,
                                     data::lvl_t p_newlvl)
        : entity(p_entity), oldlvl(p_oldlvl), newlvl(p_newlvl) {}
};


} // namespace gameevent

#endif // SYSTEM_EVENT_CREATURESYSTEM_H_
