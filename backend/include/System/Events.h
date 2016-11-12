#ifndef SYSTEM_GAME_EVENTS_H_
#define SYSTEM_GAME_EVENTS_H_

#include <entityx/entityx.hh>

#include <bus.hpp>
#include <event.hpp>
#include <signal.hpp>

#include "basic.h"

#include "Data/Basic.h"

#include "System/Event/CreatureBattlerSystemEvents.h"
#include "System/Event/CreatureProgressTimerSystemEvents.h"

namespace gameevent {

using EventBus = eventpp::Bus<
  CreatureAddBattlerStatusEvent,
  CreatureRemoveBattlerStatusEvent,
  CreatureRecoverEvent,
  CreatureAddExpEvent,

  ProgressTimerCallbackEvent,
  ProgressTimerIncrementEvent,
  ProgressTimerStarvationPhaseEvent,
  ProgressTimerShortTermMemoryEvent,
  ProgressTimerMediumTermMemoryEvent
>;

} // namespace gameevent




#endif // SYSTEM_GAME_EVENTS_H_
