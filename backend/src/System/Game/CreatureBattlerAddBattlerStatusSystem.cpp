#include "System/Game/CreatureBattlerAddBattlerStatusSystem.h"

namespace gamesystem {


CreatureBattlerAddBattlerStatusSystem::CreatureBattlerAddBattlerStatusSystem(gameentity::DataManager& datamanager)
    : datamanager_(datamanager) 
{}

void CreatureBattlerAddBattlerStatusSystem::sortBattlerStatuses(std::vector<std::string>& statuses_name) {
    auto sort_func = [&](const std::string& a, const std::string& b) {
        auto status_a = this->datamanager_.findCreatureBattlerStatus(a);
        auto status_b = this->datamanager_.findCreatureBattlerStatus(b);

        if(status_a && status_b) {
            return *status_a > *status_b;
        }

        return false;
    };

    std::sort(std::begin(statuses_name), std::end(statuses_name), sort_func);
}

void CreatureBattlerAddBattlerStatusSystem::update(const gameevent::CreatureAddBattlerStatusEvent& event, EntityManager& entities, EventBus& events, TimeDelta dt) {
    Component<gamecomp::BattlerStatusesComponent> battlerstatuses;
    
    for (auto entity : entities.entities_with_components(battlerstatuses)) {
        const data::BattlerStatus& addstatus = event.addstatus;
        std::string addstatus_name = addstatus.getName();

        auto status_name_it =
            std::find(std::begin(battlerstatuses->statuses_name),
                         std::end(battlerstatuses->statuses_name), addstatus_name);

        if (status_name_it == std::end(battlerstatuses->statuses_name)) {
            battlerstatuses->statuses_name.push_back(addstatus_name);
            battlerstatuses->startstatusturns.push_back(gamecomp::BattlerStatusTurn (addstatus_name));

            for (auto removestatus_name : addstatus.getRemoveStatuses()) {
                auto removestatus = this->datamanager_.findCreatureBattlerStatus(removestatus_name);
                if(removestatus){
                    emit_event<gameevent::CreatureRemoveBattlerStatusEvent>(events, entity, *removestatus);
                }
            }

            sortBattlerStatuses(battlerstatuses->statuses_name);
        }
    }
}

}