#ifndef SYSTEM_EVENT_CREATUREDIGESTIONSYSTEMEVENTS_H_
#define SYSTEM_EVENT_CREATUREDIGESTIONSYSTEMEVENTS_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Game/CreatureEntityCreator.h"

namespace gameevent {


struct CreatureUseToiletEvent {
    gameentity::Entity entity;

    explicit CreatureUseToiletEvent(gameentity::Entity p_entity)
        : entity(p_entity) {}
};

struct CreatureMakePoopEvent {
    gameentity::Entity entity;
    int newpoopstack;

    explicit CreatureMakePoopEvent(gameentity::Entity p_entity, int p_newpoopstack)
        : entity(p_entity)
        , newpoopstack(p_newpoopstack){}
};


} // namespace gameevent

#endif // SYSTEM_EVENT_CREATUREDIGESTIONSYSTEMEVENTS_H_
