#include "CreatureBattlerSystem.hpp"

namespace gamesystem {


void CreatureBattlerSystem::receive(const CreatureRecoverEvent& recover_event) {
    this->recover_events_.push_back(recover_event);
}

void CreatureBattlerSystem::receive(
    const CreatureAddBattlerStatusEvent& addstatus_event) {
    this->addstatus_events_.push_back(addstatus_event);
}

void CreatureBattlerSystem::receive(
    const CreatureRemoveBattlerStatusEvent& removestatus_event) {
    this->removestatus_events_.push_back(removestatus_event);
}

void CreatureBattlerSystem::receive(const CreatureAddExpEvent& addexp_event) {
    this->addexp_events_.push_back(addexp_event);
}



void CreatureBattlerSystem::sortBattlerStatuses(
    std::vector<std::shared_ptr<model::data::BattlerStatus>>& statuses) {
    auto orderby = [](std::shared_ptr<model::data::BattlerStatus> s1,
                      std::shared_ptr<model::data::BattlerStatus> s2) {
        return (s1 && s2) ? (*s1) > (*s2) : false;
    };

    std::sort(std::begin(statuses), std::end(statuses), orderby);
}


void CreatureBattlerSystem::addCreatureBattlerStatus(
    entityx::EventManager& events, entityx::Entity entity,
    gamecomp::BattlerStatuses::Handle battlerstatuses,
    const std::shared_ptr<model::data::BattlerStatus>& addstatus) {
    if (addstatus) {
        auto find_status_if = [addstatus](
            const std::shared_ptr<model::data::BattlerStatus>& status) {
            return (status && addstatus)
                       ? status->getBattlerStatusID() ==
                                 addstatus->getBattlerStatusID() &&
                             status->getName() == addstatus->getName()
                       : false;
        };

        auto find_status_it =
            std::find_if(std::begin(battlerstatuses->statuses),
                         std::end(battlerstatuses->statuses), find_status_if);
        if (find_status_it == std::end(battlerstatuses->statuses)) {
            battlerstatuses->statuses.push_back(addstatus);
            battlerstatuses->startstatusturn.emplace_back(
                addstatus->getBattlerStatusID());

            for (auto removestatus : addstatus->getRemoveStatuses()) {
                if (removestatus) {
                    events.emit<CreatureRemoveBattlerStatusEvent>(entity, removestatus);
                }
            }

            sortBattlerStatuses(battlerstatuses->statuses);
        }
    }
}

void CreatureBattlerSystem::removeCreatureBattlerStatus(
    gamecomp::BattlerStatuses::Handle battlerstatuses,
    const std::shared_ptr<model::data::BattlerStatus>& removestatus) {
    if (removestatus) {
        auto removestatus_status_if = [removestatus](
            const std::shared_ptr<model::data::BattlerStatus>& status) {
            return (status && removestatus)
                       ? status->getBattlerStatusID() ==
                                 removestatus->getBattlerStatusID() &&
                             status->getName() == removestatus->getName()
                       : false;
        };

        battlerstatuses->statuses.erase(
            std::remove_if(std::begin(battlerstatuses->statuses),
                           std::end(battlerstatuses->statuses),
                           removestatus_status_if),
            std::end(battlerstatuses->statuses));


        sortBattlerStatuses(battlerstatuses->statuses);
    }
}


void CreatureBattlerSystem::recoverCreature(
    gamecomp::CreatureBattler::Handle creature_battler) {
    creature_battler->hp =
        enum_array_at(creature_battler->attr, model::data::Attribute::MaxHP);
    creature_battler->mp =
        enum_array_at(creature_battler->attr, model::data::Attribute::MaxMP);
}


void CreatureBattlerSystem::addExp(
    gamecomp::CreatureData::Handle creature_data,
    gamecomp::CreatureBattler::Handle creature_battler, int exp) {
    const std::shared_ptr<model::data::Creature>& creature_data_ptr =
        creature_data->data;

    if (creature_data_ptr) {
        int maxlvl = creature_data_ptr->getMaxLvL();

        int nextexp =
            enum_array_at(creature_battler->attr, model::data::Attribute::Exp);

        creature_battler->exp += exp;

        while (creature_battler->lvl <= maxlvl &&
               creature_battler->exp >= nextexp) {
            creature_battler->lvl++;

            const std::vector<int>& exp_attrparam = enum_array_at(
                creature_battler->attrparam, model::data::Attribute::Exp);
            size_t exp_attrparam_size = exp_attrparam.size();
            if (creature_battler->lvl >= 0 &&
                static_cast<size_t>(creature_battler->lvl) < exp_attrparam_size) {
                enum_array_at(creature_battler->attrbase,
                              model::data::Attribute::Exp) =
                    exp_attrparam.at(static_cast<size_t>(creature_battler->lvl));
            }
        }

        creaturebattler_creator_.updateNewLvL(*creature_battler.get(),
                                              *creature_data.get());
    }
}


void CreatureBattlerSystem::updateCreatureBattlerAttribute(
    gamecomp::CreatureBattler::Handle creature_battler,
    gamecomp::BattlerStatuses::Handle battler_statuses,
    gamecomp::CreatureData::Handle creature_data) {
    const std::vector<std::shared_ptr<model::data::BattlerStatus>>&
        battlerstatuses = battler_statuses->statuses;

    const std::shared_ptr<model::data::Creature>& creature_data_ptr =
        creature_data->data;
    if (creature_data_ptr) {
        creature_battler->lvl = boost::algorithm::clamp(
            creature_battler->lvl, creature_data_ptr->getMinLvL(),
            creature_data_ptr->getMaxLvL());
    }

    for (auto attr : Enum<model::data::Attribute>()) {
        auto& baseattrs = enum_array_at(creature_battler->attrparam, attr);
        if (creature_battler->lvl >= 0 &&
            static_cast<size_t>(creature_battler->lvl) < baseattrs.size()) {
            enum_array_at(creature_battler->attrbase, attr) =
                baseattrs[static_cast<size_t>(creature_battler->lvl)];
        }

        auto& battler_attr = enum_array_at(creature_battler->attr, attr);
        battler_attr = enum_array_at(creature_battler->attrbase, attr) +
                       enum_array_at(creature_battler->attrplus, attr);

        for (const auto& status : battlerstatuses) {
            if (status) {
                battler_attr *= status->getAttr(attr);
            }
        }
    }

    creature_battler->hp = boost::algorithm::clamp(
        creature_battler->hp, 0,
        enum_array_at(creature_battler->attr, model::data::Attribute::MaxHP));
    creature_battler->mp = boost::algorithm::clamp(
        creature_battler->mp, 0,
        enum_array_at(creature_battler->attr, model::data::Attribute::MaxMP));
}


void CreatureBattlerSystem::updateCreatureHitRate(
    gamecomp::CreatureBattler::Handle creature_battler,
    gamecomp::BattlerStatuses::Handle battler_statuses,
    gamecomp::CreatureData::Handle creature_data) {
    const std::vector<std::shared_ptr<model::data::BattlerStatus>>&
        battlerstatuses = battler_statuses->statuses;

    const std::shared_ptr<model::data::Creature>& creature_data_ptr =
        creature_data->data;

    int basehitrate = (creature_data_ptr) ? creature_data_ptr->getHitRate() : DEFAULT_HITRATE;
    
    int status_sum_hitrate = std::accumulate(std::begin(battlerstatuses), std::end(battlerstatuses), 0, [&](const int& init, const std::shared_ptr<model::data::BattlerStatus>& status){
        return init + ((status)? status->getHitRate() : DEFAULT_HITRATE);
    });
    int status_avg_hitrate = (battlerstatuses.size() != 0)? status_sum_hitrate / battlerstatuses.size() : DEFAULT_HITRATE;

    creature_battler->hitrate = (basehitrate + status_avg_hitrate) / 2;
}


void CreatureBattlerSystem::updateCreatureCriticalHitRate(
    gamecomp::CreatureBattler::Handle creature_battler,
    gamecomp::BattlerStatuses::Handle battler_statuses,
    gamecomp::CreatureData::Handle creature_data) {
    const std::shared_ptr<model::data::Creature> creature_data_ptr =
        creature_data->data;

    int critical_hitrate =
        (creature_data_ptr) ? creature_data_ptr->getCriticalHitRate() : DEFAULT_CRITICAL_HITRATE;

    creature_battler->critical_hitrate = critical_hitrate;
}


void CreatureBattlerSystem::updateCreatureEvaRate(
    gamecomp::CreatureBattler::Handle creature_battler,
    gamecomp::BattlerStatuses::Handle battler_statuses,
    gamecomp::CreatureData::Handle creature_data) {
    const std::shared_ptr<model::data::Creature>& creature_data_ptr =
        creature_data->data;

    int evarate = (creature_data_ptr) ? creature_data_ptr->getEvaRate() : DEFAULT_EVARATE;

    creature_battler->evarate = evarate;
}



void CreatureBattlerSystem::updateCreatureStatusRestriction(
    gamecomp::CreatureBattler::Handle creature_battler,
    gamecomp::BattlerStatuses::Handle battler_statuses,
    gamecomp::CreatureData::Handle creature_data) {
    const std::vector<std::shared_ptr<model::data::BattlerStatus>>&
        battlerstatuses = battler_statuses->statuses;

    const std::shared_ptr<model::data::Creature>& creature_data_ptr =
        creature_data->data;

    auto comp_func = [](const std::shared_ptr<model::data::BattlerStatus>& status1,
                        const std::shared_ptr<model::data::BattlerStatus>& status2) {
        return static_cast<int>(status1->getRestriction()) <
               static_cast<int>(status2->getRestriction());
    };

    auto it = std::max_element(std::begin(battlerstatuses),
                               std::end(battlerstatuses), comp_func);

    creature_battler->status_restriction =
        (it != std::end(battlerstatuses))
            ? (*it)->getRestriction()
            : model::data::StatusRestrictionOption::None;
}

} // namespace gamesystem
