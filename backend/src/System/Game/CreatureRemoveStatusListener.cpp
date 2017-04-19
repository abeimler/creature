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
        
    for(auto entity : entities.view<gamecomp::BattlerStatusesComponent, 
            gamecomp::CreatureBodilyStateComponent>()) {
        
        auto& battlerstatuses = entities.get<gamecomp::BattlerStatusesComponent>(entity);
        auto& bodilystate = entities.get<gamecomp::CreatureBodilyStateComponent>(entity);

        removeCreatureStatus(events, entity, battlerstatuses,
                             bodilystate, event.removestatus);
    }
}
} // namespace gamesystem