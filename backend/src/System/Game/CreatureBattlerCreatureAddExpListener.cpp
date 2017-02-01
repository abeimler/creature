#include "System/Game/CreatureBattlerCreatureAddExpListener.h"

namespace gamesystem {


void CreatureBattlerCreatureAddExpListener::addExp(
    gamecomp::CreatureDataComponent& creature_data,
    gamecomp::CreatureBattlerComponent& creature_battler,
    data::attr_t add_exp) {
    const auto& creature = creature_data.creature;

    creature_battler.exp += add_exp;

    auto maxlvl = creature.getMaxLvL();
    auto nextexp =
        earr::enum_array_at(creature_battler.attr, +data::Attribute::Exp);
    while (creature_battler.lvl <= maxlvl && creature_battler.exp >= nextexp) {
        creature_battler.lvl++;

        const auto& exp_attrparams = earr::enum_array_at(
            creature_battler.attrparam, +data::Attribute::Exp);
        size_t exp_attrparams_size = exp_attrparams.size();

        if (creature_battler.lvl >= 0) {
            size_t lvl_index = static_cast<size_t>(creature_battler.lvl);
            if (lvl_index < exp_attrparams_size) {
                earr::enum_array_at(creature_battler.attrbase,
                                    +data::Attribute::Exp) =
                    exp_attrparams.at(lvl_index);
            }
        }

        creaturebattler_creator_.updateNewLvL(creature_battler,
                                              creature_data.creature);

        nextexp =
            earr::enum_array_at(creature_battler.attr, +data::Attribute::Exp);
    }
}

void CreatureBattlerCreatureAddExpListener::update(
    const gameevent::CreatureAddExpEvent& event, EntityManager& entities,
    EventBus& /*events*/, TimeDelta /*dt*/) {
    Component<gamecomp::CreatureDataComponent> creature_data;
    Component<gamecomp::CreatureBattlerComponent> creature_battler;

    for (auto entity :
         entities.entities_with_components(creature_data, creature_battler)) {
        auto add_exp = event.exp;
        addExp(*creature_data.get(), *creature_battler.get(), add_exp);
    }
}

} // namespace gamesystem