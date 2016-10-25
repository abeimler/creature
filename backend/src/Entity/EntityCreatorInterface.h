#ifndef ENTITY_ENTITYCREATORINTERFACE_HPP_
#define ENTITY_ENTITYCREATORINTERFACE_HPP_

#include <entityx/entityx.h>

#include "basic.h"

class EntityCreatorInterface {
    public:
    virtual ~EntityCreatorInterface() = default;
    EntityCreatorInterface(const EntityCreatorInterface&) = default;
    EntityCreatorInterface& operator=(const EntityCreatorInterface&) = default;
    EntityCreatorInterface(EntityCreatorInterface&&) = default;
    EntityCreatorInterface& operator=(EntityCreatorInterface&&) = default;

    virtual void create(entityx::Entity& entity) = 0;
};

#endif // ENTITY_ENTITYCREATORINTERFACE_HPP_
