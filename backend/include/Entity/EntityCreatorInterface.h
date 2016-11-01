#ifndef ENTITY_ENTITYCREATORINTERFACE_HPP_
#define ENTITY_ENTITYCREATORINTERFACE_HPP_

#include <entityx/entityx.hh>

#include "basic.h"

template<class Entity>
class EntityCreatorInterface {
    public:
    EntityCreatorInterface() = default;
    virtual ~EntityCreatorInterface() = default;
    EntityCreatorInterface(const EntityCreatorInterface&) = default;
    EntityCreatorInterface& operator=(const EntityCreatorInterface&) = default;
    EntityCreatorInterface(EntityCreatorInterface&&) = default;
    EntityCreatorInterface& operator=(EntityCreatorInterface&&) = default;

    virtual void create(Entity& entity) = 0;
};

#endif // ENTITY_ENTITYCREATORINTERFACE_HPP_
