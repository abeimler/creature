#include "System/Game/CreatureBattlerRemoveBattlerStatusSystem.h"

namespace gamesystem {


CreatureBattlerRemoveBattlerStatusSystem::
    CreatureBattlerRemoveBattlerStatusSystem(
        gameentity::DataManager& datamanager)
    : datamanager_(datamanager) {}

void CreatureBattlerRemoveBattlerStatusSystem::sortBattlerStatuses(
    std::vector<std::string>& statuses_name) {
    auto sort_func = [&](const std::string& a, const std::string& b) {
        auto status_a = this->datamanager_.findCreatureBattlerStatus(a);
        auto status_b = this->datamanager_.findCreatureBattlerStatus(b);

        if (status_a && status_b) {
            return *status_a > *status_b;
        }

        return false;
    };

    std::sort(std::begin(statuses_name), std::end(statuses_name), sort_func);
}

void CreatureBattlerRemoveBattlerStatusSystem::removeBattlerStatus(
    const gameevent::CreatureRemoveBattlerStatusEvent& event,
    Component<gamecomp::BattlerStatusesComponent>& battlerstatuses) {
    const data::BattlerStatus& removestatus = event.removestatus;
    std::string removestatus_name = removestatus.getName();

    auto status_name_it =
        std::find(std::begin(battlerstatuses->statuses_name),
                  std::end(battlerstatuses->statuses_name), removestatus_name);

    if (status_name_it != std::end(battlerstatuses->statuses_name)) {
        battlerstatuses->statuses_name.erase(status_name_it);
    }
}

void CreatureBattlerRemoveBattlerStatusSystem::removeStartBattlerStatusTurn(
    const gameevent::CreatureRemoveBattlerStatusEvent& event,
    Component<gamecomp::BattlerStatusesComponent>& battlerstatuses) {
    const data::BattlerStatus& removestatus = event.removestatus;
    std::string removestatus_name = removestatus.getName();

    auto remove_startstatusturn_func = [removestatus_name](
        const gamecomp::BattlerStatusTurn& startstatusturn) {
        return startstatusturn.battlerstatus_name == removestatus_name;
    };


    battlerstatuses->startstatusturns.erase(
        std::remove_if(std::begin(battlerstatuses->startstatusturns),
                       std::end(battlerstatuses->startstatusturns),
                       remove_startstatusturn_func),
        std::end(battlerstatuses->startstatusturns));
}

void CreatureBattlerRemoveBattlerStatusSystem::update(
    const gameevent::CreatureRemoveBattlerStatusEvent& event,
    EntityManager& entities, EventBus& events, TimeDelta dt) {
    Component<gamecomp::BattlerStatusesComponent> battlerstatuses;

    for (auto entity : entities.entities_with_components(battlerstatuses)) {

        removeBattlerStatus(event, battlerstatuses);
        removeStartBattlerStatusTurn(event, battlerstatuses);

        sortBattlerStatuses(battlerstatuses->statuses_name);
    }
}
}