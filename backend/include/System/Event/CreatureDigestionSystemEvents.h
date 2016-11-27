#ifndef SYSTEM_EVENT_CREATUREDIGESTIONSYSTEMEVENTS_H_
#define SYSTEM_EVENT_CREATUREDIGESTIONSYSTEMEVENTS_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Game/CreatureEntityCreator.h"

namespace gameevent {


struct CreatureUseToiletEvent {
    entityx::Entity entity;

    explicit CreatureUseToiletEvent(entityx::Entity p_entity)
        : entity(p_entity) {}
};

struct CreatureMakePoopEvent {
    entityx::Entity entity;
    int newpoop;

    explicit CreatureMakePoopEvent(entityx::Entity p_entity, int p_newpoop)
        : entity(p_entity)
        , newpoop(p_newpoop){}
};


} // namespace gameevent

#endif // SYSTEM_EVENT_CREATUREDIGESTIONSYSTEMEVENTS_H_
