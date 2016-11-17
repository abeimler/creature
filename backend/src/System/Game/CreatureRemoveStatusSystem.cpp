#include "System/Game/CreatureRemoveStatusSystem.h"

namespace gamesystem {


CreatureRemoveStatusSystem::CreatureRemoveStatusSystem(
    gameentity::DataManager& datamanager)
    : datamanager_(datamanager) {}


void CreatureRemoveStatusSystem::removeCreatureStatus(
    EventBus& events, Entity entity,
    gamecomp::BattlerStatusesComponent& battlerstatuses,
    gamecomp::CreatureBodilyStateComponent& bodilystate,
    data::CreatureStatus removecreaturestatus) {

    auto removestatus = this->datamanager_.findCreatureBattlerStatusByStatus(removecreaturestatus);

    if (removestatus) {
        emit_event<gameevent::CreatureAddBattlerStatusEvent>(events, entity, *removestatus);
    }
}

void CreatureRemoveStatusSystem::update(
    const gameevent::CreatureRemoveStatusEvent& event,
    EntityManager& entities, EventBus& events, TimeDelta /*dt*/) {
    Component<gamecomp::BattlerStatusesComponent> battlerstatuses;
    Component<gamecomp::CreatureBodilyStateComponent> bodilystate;

    for (auto entity : entities.entities_with_components(battlerstatuses, bodilystate)) {
        removeCreatureStatus(events, entity, *battlerstatuses.get(), *bodilystate.get(),
                             event.removestatus);
    }
}
} // namespace gamesystem