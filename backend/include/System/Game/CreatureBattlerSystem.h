#ifndef SYSTEM_GAME_CREATUREBATTLERSYSTEM_H_
#define SYSTEM_GAME_CREATUREBATTLERSYSTEM_H_

#include <entityx/entityx.h>

#include "basic.h"

#include "Model/Data/Basic.h"

#include "Entity/Game/CreatureEntityCreator.h"

#include "System/Game/CreatureProgressTimerSystem.h"

#include "System/Events.h"
#include "System/System.h"

namespace gamesystem {

class CreatureBattlerSystem : public entityx::Receiver<CreatureBattlerSystem> {
    private:
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;
    gameentity::CreatureCreator creaturecreator_;
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    std::vector<CreatureAddBattlerStatusEvent> addstatus_events_;
    std::vector<CreatureRemoveBattlerStatusEvent> removestatus_events_;
    std::vector<CreatureRecoverEvent> recover_events_;
    std::vector<CreatureAddExpEvent> addexp_events_;

    std::unordered_map<size_t, std::shared_ptr<model::data::Element>> elements_;

    void updateCreatureRecoverEvents(entityx::EventManager& events);
    void updateCreatureAddExpEvents(entityx::EventManager& events);

    void updateCreatureAddStatusEvents(entityx::EventManager& events);
    void updateCreatureRemoveStatusEvents(entityx::EventManager& events);

    void sortBattlerStatuses(
        std::vector<std::shared_ptr<model::data::BattlerStatus>>& statuses);

    public:
    
    static constexpr int DEFAULT_HITRATE = 90;
    static constexpr int DEFAULT_CRITICAL_HITRATE = 30; 
    static constexpr int DEFAULT_EVARATE = 20;
        
    void addCreatureBattlerStatus(
        entityx::EventManager& events, entityx::Entity entity,
        gamecomp::BattlerStatuses::Handle battlerstatuses,
        const std::shared_ptr<model::data::BattlerStatus>& addcreaturestatus);
    void removeCreatureBattlerStatus(
        gamecomp::BattlerStatuses::Handle battlerstatuses,
        const std::shared_ptr<model::data::BattlerStatus>&
            removecreaturestatus);

    void recoverCreature(gamecomp::CreatureBattler::Handle creature_battler);
    void addExp(gamecomp::CreatureData::Handle creature_data,
                gamecomp::CreatureBattler::Handle creature_battler, int exp);

    void updateCreatureBattlerAttribute(
        gamecomp::CreatureBattler::Handle creature_battler,
        gamecomp::BattlerStatuses::Handle battler_statuses,
        gamecomp::CreatureData::Handle creature_data);

    void
    updateCreatureHitRate(gamecomp::CreatureBattler::Handle creature_battler,
                          gamecomp::BattlerStatuses::Handle battler_statuses,
                          gamecomp::CreatureData::Handle creature_data);

    void updateCreatureCriticalHitRate(
        gamecomp::CreatureBattler::Handle creature_battler,
        gamecomp::BattlerStatuses::Handle battler_statuses,
        gamecomp::CreatureData::Handle creature_data);

    void
    updateCreatureEvaRate(gamecomp::CreatureBattler::Handle creature_battler,
                          gamecomp::BattlerStatuses::Handle battler_statuses,
                          gamecomp::CreatureData::Handle creature_data);

    void updateCreatureStatusRestriction(
        gamecomp::CreatureBattler::Handle creature_battler,
        gamecomp::BattlerStatuses::Handle battler_statuses,
        gamecomp::CreatureData::Handle creature_data);

    void setElementList(
        const std::vector<std::shared_ptr<model::data::Element>>& elements) {
        this->elements_.clear();
        for (auto elem : elements) {
            if (elem) {
                this->elements_[elem->getElementID()] = elem;
            }
        }
    }
    const std::unordered_map<size_t, std::shared_ptr<model::data::Element>>&
    getElementList() const {
        return this->elements_;
    }

    void configure(entityx::EventManager& event_manager) override {
        event_manager.subscribe<CreatureAddBattlerStatusEvent>(*this);
        event_manager.subscribe<CreatureRemoveBattlerStatusEvent>(*this);
        event_manager.subscribe<CreatureRecoverEvent>(*this);
        event_manager.subscribe<CreatureAddExpEvent>(*this);
    }


    void receive(const CreatureAddBattlerStatusEvent& addstatus_event);
    void receive(const CreatureRemoveBattlerStatusEvent& removestatus_event);
    void receive(const CreatureRecoverEvent& recover_event);
    void receive(const CreatureAddExpEvent& addexp_event);

    void update(entityx::EntityManager& entities, entityx::EventManager& events,
                entityx::TimeDelta dt) override;
};

} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREBATTLERSYSTEM_HPP_
