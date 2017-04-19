#ifndef ENTITY_ENTITYCREATOR_H_
#define ENTITY_ENTITYCREATOR_H_

#include "basic.h"

namespace gameentity {

template <class EntityManager, class Entity>
class EntityCreator {
    public:
    EntityCreator() = default;
    virtual ~EntityCreator() = default;
    EntityCreator(const EntityCreator&) = default;
    EntityCreator& operator=(const EntityCreator&) = default;
    EntityCreator(EntityCreator&&) = default;
    EntityCreator& operator=(EntityCreator&&) = default;

    virtual void create(EntityManager& entities, Entity& entity) = 0;
};

} // namespace gameentity

#endif // ENTITY_ENTITYCREATOR_H_
