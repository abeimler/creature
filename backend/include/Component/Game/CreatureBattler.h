#ifndef COMPONENT_GAME_CREATUREBATTLER_H_
#define COMPONENT_GAME_CREATUREBATTLER_H_

#include "Component/Game/Battler.h"
#include "Component/Game/CreatureBattlerGene.h"

namespace gamecomp {

/// Basic Battler Data
struct CreatureDataComponent {
    std::string creature_name;
};

/// Battler
struct CreatureBattlerComponent {
    /// learned skills
    std::vector<std::string> learned_skills_name;

    int lvl = 0; ///< current Level of Creature
    int exp = 0; ///< current EXP of Creature

    /// Base Attribute of Creature, attrParam[Attribute][Level]
    earr::enum_array<data::Attribute, std::vector<int>> attrparam;


    int hp = 0; ///< HP Value
    int mp = 0; ///< MP Value

    /// Basis Attribute Value
    earr::enum_array<data::Attribute, int> attrbase;

    /// Inflation Attribute Value
    earr::enum_array<data::Attribute, int> attrinf;

    /**
     * Plus Attribute Value,
     * added by Item,BattlerStatus,Weapon,...
     */
    earr::enum_array<data::Attribute, int> attrplus;

    /// current Attribute Value (basis + plus value)
    earr::enum_array<data::Attribute, int> attr;

    // current HitRate for Battle
    int hitrate = 0;

    // current Critical HitRate for Battle
    int critical_hitrate = 0;

    // current EvaRate for Battle
    int evarate = 0;

    data::StatusRestrictionOption status_restriction =
        data::StatusRestrictionOption::None;
};
} // namespace gamecomp

#endif // COMPONENT_GAME_CREATUREBATTLER_H_
