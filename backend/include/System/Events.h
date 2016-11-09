#ifndef SYSTEM_GAME_EVENTS_H_
#define SYSTEM_GAME_EVENTS_H_

#include "basic.h"

#include "Data/Basic.h"

#include "System/Event/CreatureProgressTimerSystemEvents.h"

namespace gameevent {

// Convenience types for our entity system.
using GameEvents = entityx::Components<
    ProgressTimerCallbackEvent,
    ProgressTimerIncrementEvent,
    ProgressTimerStarvationPhaseEvent,
    ProgressTimerShortTermMemoryEvent,
    ProgressTimerMediumTermMemoryEvent
    >;

using EventManager = entityx::EntityX<GameEvents, entityx::ColumnStorage<GameEvents>>;

template <typename E>
using Event = EventManager::Component<E>;

using EventEntity = EventManager::Entity;

} // namespace gameevent

namespace std {
template <> struct hash<const gameevent::EventEntity> {
  std::size_t operator () (const gameevent::EventEntity &entity) const {
    return static_cast<std::size_t>(entity.id().index() ^ entity.id().version());
  }
};
}



#endif // SYSTEM_GAME_EVENTS_H_
