#include "CreatureBattlerSystem.hpp"

namespace gamesystem {


void CreatureBattlerSystem::updateCreatureRecoverEvents(
    entityx::EventManager& events) {
    for (auto& recover_event : this->recover_events_) {
        entityx::Entity entity = recover_event.entity;
        if (entity) {
            auto creature_battler = entity.component<gamecomp::CreatureBattler>();

            recoverCreature(creature_battler);
        }
    }
    this->recover_events_.clear();
}

void CreatureBattlerSystem::updateCreatureAddStatusEvents(
    entityx::EventManager& events) {
    for (auto& addstatus_event : this->addstatus_events_) {
        entityx::Entity entity = addstatus_event.entity;
        if (entity) {
            auto battlerstatuses = entity.component<gamecomp::BattlerStatuses>();

            this->addCreatureBattlerStatus(events, entity, battlerstatuses,
                                           addstatus_event.addstatus);
        }
    }
    this->addstatus_events_.clear();
}

void CreatureBattlerSystem::updateCreatureRemoveStatusEvents(
    entityx::EventManager& events) {
    for (auto& removestatus_event : this->removestatus_events_) {
        entityx::Entity entity = removestatus_event.entity;
        if (entity) {
            auto battlerstatuses = entity.component<gamecomp::BattlerStatuses>();

            this->removeCreatureBattlerStatus(battlerstatuses,
                                              removestatus_event.removestatus);
        }
    }
    this->removestatus_events_.clear();
}

void CreatureBattlerSystem::updateCreatureAddExpEvents(
    entityx::EventManager& events) {
    for (auto& addexp_event : this->addexp_events_) {
        entityx::Entity entity = addexp_event.entity;
        if (entity) {
            auto creature_battler = entity.component<gamecomp::CreatureBattler>();
            auto creature_data = entity.component<gamecomp::CreatureData>();

            addExp(creature_data, creature_battler, addexp_event.exp);
        }
    }
    this->addexp_events_.clear();
}


void CreatureBattlerSystem::update(entityx::EntityManager& entities,
                                   entityx::EventManager& events,
                                   entityx::TimeDelta dt) {
    this->updateCreatureRecoverEvents(events);
    this->updateCreatureAddStatusEvents(events);
    this->updateCreatureRemoveStatusEvents(events);

    gamecomp::CreatureData::Handle creature_data;
    gamecomp::CreatureBattler::Handle creature_battler;
    gamecomp::BattlerStatuses::Handle battler_statuses;
    for (auto entity : entities.entities_with_components(
             creature_data, creature_battler, battler_statuses)) {
        this->updateCreatureBattlerAttribute(creature_battler, battler_statuses,
                                             creature_data);

        this->updateCreatureHitRate(creature_battler, battler_statuses,
                                    creature_data);

        this->updateCreatureCriticalHitRate(creature_battler, battler_statuses,
                                            creature_data);

        this->updateCreatureEvaRate(creature_battler, battler_statuses,
                                    creature_data);

        this->updateCreatureStatusRestriction(creature_battler,
                                              battler_statuses, creature_data);
    }

    this->updateCreatureAddExpEvents(events);
}

} // namespace gamesystem
