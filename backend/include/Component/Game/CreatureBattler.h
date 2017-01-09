#ifndef COMPONENT_GAME_CREATUREBATTLER_H_
#define COMPONENT_GAME_CREATUREBATTLER_H_

#include "Component/Game/Basic.h"
#include "Component/Game/Battler.h"
#include "Component/Game/CreatureBattlerGene.h"

namespace gamecomp {

/// Basic Battler Data
struct CreatureDataComponent {
    data::Creature creature;
};

/// Battler
struct CreatureBattlerComponent {
    /// learned skills
    std::vector<std::string> learned_skills_name;

    data::lvl_t lvl = 0; ///< current Level of Creature
    data::attr_t exp = 0; ///< current EXP of Creature

    /// Base Attribute of Creature, attrParam[Attribute][Level]
    earr::enum_array<data::Attribute, std::vector<data::attr_t>> attrparam;


    data::attr_t hp = 0; ///< HP Value
    data::attr_t mp = 0; ///< MP Value

    /// Basis Attribute Value
    earr::enum_array<data::Attribute, data::attr_t> attrbase;

    /// Inflation Attribute Value
    earr::enum_array<data::Attribute, data::attr_t> attrinf;

    /**
     * Plus Attribute Value,
     * added by Item,BattlerStatus,Weapon,...
     */
    earr::enum_array<data::Attribute, data::attr_t> attrplus;

    /// current Attribute Value (basis + plus value)
    earr::enum_array<data::Attribute, data::attr_t> attr;

    // current HitRate for Battle
    data::percent_rate_t hitrate = 0;

    // current Critical HitRate for Battle
    data::percent_rate_t critical_hitrate = 0;

    // current EvaRate for Battle
    data::percent_rate_t evarate = 0;

    data::StatusRestrictionOption status_restriction =
        data::StatusRestrictionOption::None;
};
} // namespace gamecomp

#endif // COMPONENT_GAME_CREATUREBATTLER_H_
