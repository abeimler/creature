#ifndef SYSTEM_EVENT_CREATUREEVOLUTIONSYSTEMEVENTS_H_
#define SYSTEM_EVENT_CREATUREEVOLUTIONSYSTEMEVENTS_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Game/CreatureEntityCreator.h"

namespace gameevent {

struct CreatureReadyToEvolveEvent {
    gameentity::Entity entity;

    explicit CreatureReadyToEvolveEvent(gameentity::Entity p_entity)
        : entity(p_entity) {}
};

struct CreatureBornEvent {
    gameentity::Entity entity;

    explicit CreatureBornEvent(gameentity::Entity p_entity) : entity(p_entity) {}
};

struct CreatureIsBornEvent {
    gameentity::Entity entity;

    explicit CreatureIsBornEvent(gameentity::Entity p_entity) : entity(p_entity) {}
};

struct CreatureTryToEvolveEvent {
    gameentity::Entity entity;

    explicit CreatureTryToEvolveEvent(gameentity::Entity p_entity)
        : entity(p_entity) {}
};

struct CreatureEvolveEvent {
    gameentity::Entity entity;
    bool goodevolve;
    data::Creature newcreature;

    CreatureEvolveEvent(
        gameentity::Entity p_entity, bool p_goodevolve,
        const data::Creature& p_newcreature)
        : entity(p_entity)
        , goodevolve(p_goodevolve)
        , newcreature(p_newcreature) {}
};

struct CreatureIsEvolveFinishEvent {
    gameentity::Entity entity;
    gamecomp::EvolutionStatus status;

    CreatureIsEvolveFinishEvent(gameentity::Entity p_entity,
                                gamecomp::EvolutionStatus p_status)
        : entity(p_entity), status(p_status) {}
};


} // namespace gameevent

#endif // SYSTEM_EVENT_CREATUREEVOLUTIONSYSTEMEVENTS_H_
