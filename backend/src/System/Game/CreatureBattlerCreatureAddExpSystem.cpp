#include "System/Game/CreatureBattlerCreatureAddExpSystem.h"

namespace gamesystem {


void CreatureBattlerCreatureAddExpSystem::update(
    const gameevent::CreatureAddExpEvent& event, EntityManager& entities,
    EventBus& /*events*/, TimeDelta /*dt*/) {
    Component<gamecomp::CreatureDataComponent> creature_data;
    Component<gamecomp::CreatureBattlerComponent> creature_battler;

    for (auto entity :
         entities.entities_with_components(creature_data, creature_battler)) {
        const data::Creature& creature = creature_data->creature;
        int add_exp = event.exp;

        creature_battler->exp += add_exp;

        int maxlvl = creature.getMaxLvL();
        int nextexp =
            earr::enum_array_at(creature_battler->attr, +data::Attribute::Exp);
        while (creature_battler->lvl <= maxlvl &&
               creature_battler->exp >= nextexp) {
            creature_battler->lvl++;

            const auto& exp_attrparams = earr::enum_array_at(
                creature_battler->attrparam, +data::Attribute::Exp);
            size_t exp_attrparams_size = exp_attrparams.size();

            if (creature_battler->lvl >= 0) {
                size_t lvl_index = static_cast<size_t>(creature_battler->lvl);
                if (lvl_index < exp_attrparams_size) {
                    earr::enum_array_at(creature_battler->attrbase,
                                        +data::Attribute::Exp) =
                        exp_attrparams.at(lvl_index);
                }
            }

            creaturebattler_creator_.updateNewLvL(*creature_battler.get(),
                                                  creature_data->creature);

            nextexp = earr::enum_array_at(creature_battler->attr,
                                          +data::Attribute::Exp);
        }
    }
}
} // namespace gamesystem