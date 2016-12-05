#include "System/Game/CreatureRemoveStatusListener.h"

namespace gamesystem {


CreatureRemoveStatusListener::CreatureRemoveStatusListener(
    gameentity::DataManager& datamanager)
    : datamanager_(datamanager) {}


void CreatureRemoveStatusListener::removeCreatureStatus(
    EventBus& events, Entity entity,
    gamecomp::BattlerStatusesComponent& battlerstatuses,
    gamecomp::CreatureBodilyStateComponent& bodilystate,
    data::CreatureStatus removecreaturestatus) {

    auto removestatus = this->datamanager_.findCreatureBattlerStatusByStatus(
        removecreaturestatus);

    if (removestatus) {
        emit_event<gameevent::CreatureRemoveBattlerStatusEvent>(events, entity,
                                                             *removestatus);
    }
}

void CreatureRemoveStatusListener::update(
    const gameevent::CreatureRemoveStatusEvent& event, EntityManager& entities,
    EventBus& events, TimeDelta /*dt*/) {
    Component<gamecomp::BattlerStatusesComponent> battlerstatuses;
    Component<gamecomp::CreatureBodilyStateComponent> bodilystate;

    for (auto entity :
         entities.entities_with_components(battlerstatuses, bodilystate)) {
        removeCreatureStatus(events, entity, *battlerstatuses.get(),
                             *bodilystate.get(), event.removestatus);
    }
}
} // namespace gamesystem