#ifndef ENTITY_ENTITYCREATOR_H_
#define ENTITY_ENTITYCREATOR_H_

#include <entityx/entityx.hh>

#include "basic.h"

namespace gameentity {

template <class Entity>
class EntityCreator {
    public:
    EntityCreator() = default;
    virtual ~EntityCreator() = default;
    EntityCreator(const EntityCreator&) = default;
    EntityCreator& operator=(const EntityCreator&) = default;
    EntityCreator(EntityCreator&&) = default;
    EntityCreator& operator=(EntityCreator&&) = default;

    virtual void create(Entity& entity) = 0;
};

} // namespace gameentity

#endif // ENTITY_ENTITYCREATOR_H_
