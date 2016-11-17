#include "System/Game/CreatureAddStatusSystem.h"

namespace gamesystem {


CreatureAddStatusSystem::CreatureAddStatusSystem(
    gameentity::DataManager& datamanager)
    : datamanager_(datamanager) {}


void CreatureAddStatusSystem::addCreatureStatus(
    EventBus& events, Entity entity,
    gamecomp::BattlerStatusesComponent& battlerstatuses,
    gamecomp::CreatureBodilyStateComponent& bodilystate,
    data::CreatureStatus addcreaturestatus) {

    auto addstatus = this->datamanager_.findCreatureBattlerStatusByStatus(addcreaturestatus);

    if (addstatus) {
        auto find_status_if = [addstatus](const std::string& status_name) {
            return (addstatus)
                       ? status_name == addstatus->getName()
                       : false;
        };

        auto find_status_it =
            std::find_if(std::begin(battlerstatuses.statuses_name),
                         std::end(battlerstatuses.statuses_name), find_status_if);

        if (find_status_it == std::end(battlerstatuses.statuses_name)) {
            if (addcreaturestatus == +data::CreatureStatus::Ill) {
                bodilystate.illcount++;
                emit_event<gameevent::CreatureDoActivityEvent>(events, entity, gamecomp::CreatureActivity::Ill);
            } else if (addcreaturestatus == +data::CreatureStatus::Hurt) {
                bodilystate.hurtcount++;
                emit_event<gameevent::CreatureDoActivityEvent>(events, entity, gamecomp::CreatureActivity::Hurt);
            }

            emit_event<gameevent::CreatureAddBattlerStatusEvent>(events, entity, *addstatus);
        }
    }
}

void CreatureAddStatusSystem::update(
    const gameevent::CreatureAddStatusEvent& event,
    EntityManager& entities, EventBus& events, TimeDelta /*dt*/) {
    Component<gamecomp::BattlerStatusesComponent> battlerstatuses;
    Component<gamecomp::CreatureBodilyStateComponent> bodilystate;

    for (auto entity : entities.entities_with_components(battlerstatuses, bodilystate)) {
        addCreatureStatus(events, entity, *battlerstatuses.get(), *bodilystate.get(),
                          event.addstatus);
    }
}

} // namespace gamesystem