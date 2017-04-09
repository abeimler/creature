#include "System/Game/CreatureBattlerSystem.h"

namespace gamesystem {

CreatureBattlerSystem::CreatureBattlerSystem(
    gameentity::DataManager& datamanager)
    : datamanager_(datamanager) {}

void CreatureBattlerSystem::updateCreatureBattlerAttribute(
    gamecomp::CreatureBattlerComponent& creature_battler,
    gamecomp::BattlerStatusesComponent& battler_statuses,
    gamecomp::CreatureDataComponent& creature_data) {

    const auto& creature = creature_data.creature;

    creature_battler.lvl =
        clamp(creature_battler.lvl, creature.getMinLvL(), creature.getMaxLvL());

    for (auto attr : earr::Enum<data::Attribute>()) {
        auto& baseattrs = earr::enum_array_at(creature_battler.attrparam, attr);

        if (creature_battler.lvl >= 0) {
            auto lvl_index = static_cast<size_t>(creature_battler.lvl);
            if (lvl_index < baseattrs.size()) {
                earr::enum_array_at(creature_battler.attrbase, attr) =
                    baseattrs[lvl_index];
            }
        }

        auto& battler_attr = earr::enum_array_at(creature_battler.attr, attr);
        battler_attr = earr::enum_array_at(creature_battler.attrbase, attr) +
                       earr::enum_array_at(creature_battler.attrplus, attr);
    }

    for (auto status_name : battler_statuses.statuses_name) {
        auto status = this->datamanager_.findCreatureBattlerStatus(status_name);
        if (status) {
            for (auto attr : earr::Enum<data::Attribute>()) {
                auto& battler_attr = earr::enum_array_at(creature_battler.attr, attr);
                auto new_battler_attr = static_cast<double>(battler_attr) * status->getAttrFactor(attr);
                battler_attr = static_cast<data::attr_t>(new_battler_attr);
            }
        }
    }

    const data::attr_t min_hp_mp_attr = 0;

    creature_battler.hp = clamp(
        creature_battler.hp, min_hp_mp_attr,
        earr::enum_array_at(creature_battler.attr, +data::Attribute::MaxHP));

    creature_battler.mp = clamp(
        creature_battler.mp, min_hp_mp_attr,
        earr::enum_array_at(creature_battler.attr, +data::Attribute::MaxMP));
}


void CreatureBattlerSystem::updateCreatureHitRate(
    gamecomp::CreatureBattlerComponent& creature_battler,
    gamecomp::BattlerStatusesComponent& battler_statuses,
    gamecomp::CreatureDataComponent& creature_data) {


    const auto& creature = creature_data.creature;

    auto basehitrate = creature.getHitRate();

    auto& battlerstatuses = battler_statuses.statuses_name;

    auto sum_battlerstatuses_hitrate_func = [&](
        const auto& init, const std::string& status_name) {
        auto status = this->datamanager_.findCreatureBattlerStatus(status_name);

        // double -> int, don't care
        auto new_rate = static_cast<double>(init) * static_cast<double>((status) ? status->getHitRate() : 1.0);
        return static_cast<decltype(basehitrate)>(new_rate);
    };

    auto status_sum_hitrate =
        std::accumulate(std::begin(battlerstatuses), std::end(battlerstatuses),
                        0, sum_battlerstatuses_hitrate_func);

    auto status_avg_hitrate = (!battlerstatuses.empty())
                                  ? status_sum_hitrate / static_cast<decltype(basehitrate)>(battlerstatuses.size())
                                  : basehitrate;

    creature_battler.hitrate = (basehitrate + status_avg_hitrate) / 2;
}


void CreatureBattlerSystem::updateCreatureCriticalHitRate(
    gamecomp::CreatureBattlerComponent& creature_battler,
    gamecomp::BattlerStatusesComponent& battler_statuses,
    gamecomp::CreatureDataComponent& creature_data) {

    const auto& creature = creature_data.creature;

    auto basecritical_hitrate = creature.getCriticalHitRate();

    auto& battlerstatuses = battler_statuses.statuses_name;

    auto sum_battlerstatuses_critical_hitrate_func = [&](
        const auto& init, const std::string& status_name) {
        auto status = this->datamanager_.findCreatureBattlerStatus(status_name);

        // double -> int, don't care
        auto new_rate = static_cast<double>(init) * static_cast<double>((status) ? status->getCriticalHitRate() : 1.0);
        return static_cast<decltype(basecritical_hitrate)>(new_rate);
    };

    auto status_sum_critical_hitrate =
        std::accumulate(std::begin(battlerstatuses), std::end(battlerstatuses),
                        0, sum_battlerstatuses_critical_hitrate_func);

    auto status_avg_hitrate =
        (!battlerstatuses.empty())
            ? status_sum_critical_hitrate / static_cast<decltype(basecritical_hitrate)>(battlerstatuses.size())
            : basecritical_hitrate;

    creature_battler.critical_hitrate =
        (basecritical_hitrate + status_avg_hitrate) / 2;
}


void CreatureBattlerSystem::updateCreatureEvaRate(
    gamecomp::CreatureBattlerComponent& creature_battler,
    gamecomp::BattlerStatusesComponent& battler_statuses,
    gamecomp::CreatureDataComponent& creature_data) {

    const auto& creature = creature_data.creature;

    auto baseevarate = creature.getEvaRate();

    auto& battlerstatuses = battler_statuses.statuses_name;

    auto sum_battlerstatuses_evarate_func = [&](
        const auto& init, const std::string& status_name) {
        auto status = this->datamanager_.findCreatureBattlerStatus(status_name);

        // double -> int, don't care
        auto new_rate = static_cast<double>(init) * ((status) ? status->getEvaRate() : 1.0);
        return static_cast<decltype(baseevarate)>(new_rate);
    };

    auto status_sum_evarate =
        std::accumulate(std::begin(battlerstatuses), std::end(battlerstatuses),
                        0, sum_battlerstatuses_evarate_func);

    auto status_avg_evarate = (!battlerstatuses.empty())
                                  ? status_sum_evarate / static_cast<decltype(baseevarate)>(battlerstatuses.size())
                                  : baseevarate;

    creature_battler.evarate = (baseevarate + status_avg_evarate) / 2;
}



void CreatureBattlerSystem::updateCreatureStatusRestriction(
    gamecomp::CreatureBattlerComponent& creature_battler,
    gamecomp::BattlerStatusesComponent& battler_statuses,
    gamecomp::CreatureDataComponent& /*creature_data*/) {

    // const auto& creature = creature_data.creature;

    auto& battlerstatuses = battler_statuses.statuses_name;

    auto restriction_comp_func = [&](const std::string& a,
                                     const std::string& b) {
        auto status_a = this->datamanager_.findCreatureBattlerStatus(a);
        auto status_b = this->datamanager_.findCreatureBattlerStatus(b);

        data::StatusRestrictionOption status_a_restriction =
            (status_a) ? status_a->getRestriction()
                       : +data::StatusRestrictionOption::None;
        data::StatusRestrictionOption status_b_restriction =
            (status_b) ? status_b->getRestriction()
                       : +data::StatusRestrictionOption::None;

        return status_a_restriction < status_b_restriction;
    };

    auto status_it =
        std::max_element(std::begin(battlerstatuses), std::end(battlerstatuses),
                         restriction_comp_func);

    creature_battler.status_restriction = data::StatusRestrictionOption::None;
    if (status_it != std::end(battlerstatuses)) {
        auto status = this->datamanager_.findCreatureBattlerStatus(*status_it);
        if (status) {
            creature_battler.status_restriction = status->getRestriction();
        }
    }
}



void CreatureBattlerSystem::update(EntityManager& entities,
                                   EventBus& /*events*/, TimeDelta /*dt*/) {

    for(auto entity : entities.view<gamecomp::CreatureDataComponent, gamecomp::CreatureBattlerComponent, gamecomp::BattlerStatusesComponent>()) {
        auto& creature_data = entities.get<gamecomp::CreatureDataComponent>(entity);
        auto& creature_battler = entities.get<gamecomp::CreatureBattlerComponent>(entity);
        auto& battler_statuses = entities.get<gamecomp::BattlerStatusesComponent>(entity);


        updateCreatureBattlerAttribute(creature_battler,
                                        battler_statuses,
                                        creature_data);

        updateCreatureHitRate(creature_battler,
                                battler_statuses,
                                creature_data);

        updateCreatureCriticalHitRate(creature_battler,
                                        battler_statuses,
                                        creature_data);

        updateCreatureEvaRate(creature_battler,
                                battler_statuses,
                                creature_data);

        this->updateCreatureStatusRestriction(creature_battler,
                                              battler_statuses,
                                              creature_data);
    }
}


} // namespace gamesystem
