#ifndef SYSTEM_EVENT_CREATUREBATTLERSYSTEMEVENTS_H_
#define SYSTEM_EVENT_CREATUREBATTLERSYSTEMEVENTS_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Game/CreatureEntityCreator.h"

namespace gameevent {

struct CreatureAddBattlerStatusEvent {
    gameentity::Entity entity;
    data::BattlerStatus addstatus;

    CreatureAddBattlerStatusEvent(gameentity::Entity p_entity,
                                  const data::BattlerStatus& p_addstatus)
        : entity(p_entity), addstatus(p_addstatus) {}
};

struct CreatureRemoveBattlerStatusEvent {
    gameentity::Entity entity;
    data::BattlerStatus removestatus;

    CreatureRemoveBattlerStatusEvent(gameentity::Entity p_entity,
                                     const data::BattlerStatus& p_removestatus)
        : entity(p_entity), removestatus(p_removestatus) {}
};

struct CreatureRecoverEvent {
    gameentity::Entity entity;

    explicit CreatureRecoverEvent(gameentity::Entity p_entity)
        : entity(p_entity) {}
};


struct CreatureAddExpEvent {
    gameentity::Entity entity;
    data::attr_t exp;

    explicit CreatureAddExpEvent(gameentity::Entity p_entity, data::attr_t p_exp)
        : entity(p_entity), exp(p_exp) {}
};

} // namespace gameevent

#endif // SYSTEM_EVENT_CREATUREBATTLERSYSTEMEVENTS_H_
