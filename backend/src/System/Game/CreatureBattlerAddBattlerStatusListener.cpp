#include "System/Game/CreatureBattlerAddBattlerStatusListener.h"

namespace gamesystem {


CreatureBattlerAddBattlerStatusListener::
    CreatureBattlerAddBattlerStatusListener(
        gameentity::DataManager& datamanager)
    : datamanager_(datamanager) {}

void CreatureBattlerAddBattlerStatusListener::sortBattlerStatuses(
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


void CreatureBattlerAddBattlerStatusListener::addBattlerStatus(EntityManager& entities, EventBus& events, Entity entity,
    gamecomp::BattlerStatusesComponent& battlerstatuses, const data::BattlerStatus& addstatus) {
    std::string addstatus_name = addstatus.getName();

    auto& battlerstatuses_statuses_name = battlerstatuses.statuses_name;
    auto& battlerstatuses_startstatusturns = battlerstatuses.startstatusturns;

    auto status_name_it =
        std::find(std::begin(battlerstatuses_statuses_name),
                    std::end(battlerstatuses_statuses_name), addstatus_name);

    if (status_name_it == std::end(battlerstatuses_statuses_name)) {
        battlerstatuses_statuses_name.push_back(addstatus_name);
        battlerstatuses_startstatusturns.push_back(gamecomp::BattlerStatusTurn(addstatus_name));

        for (auto removestatus_name : addstatus.getRemoveStatuses()) {
            auto removestatus =
                this->datamanager_.findCreatureBattlerStatus(removestatus_name);
            if (removestatus) {
                emit_event<gameevent::CreatureRemoveBattlerStatusEvent>(events, entity, *removestatus);
            }
        }

        sortBattlerStatuses(battlerstatuses_statuses_name);
    }
}

void CreatureBattlerAddBattlerStatusListener::update(
    const gameevent::CreatureAddBattlerStatusEvent& event,
    EntityManager& entities, EventBus& events, TimeDelta /*dt*/) {

    for(auto entity : entities.view<gamecomp::BattlerStatusesComponent>()) {
        auto& battlerstatuses = entities.get<gamecomp::BattlerStatusesComponent>(entity);

        const data::BattlerStatus& addstatus = event.addstatus;
        addBattlerStatus(entities, events, entity, battlerstatuses, addstatus);
    }
}
} // namespace gamesystem