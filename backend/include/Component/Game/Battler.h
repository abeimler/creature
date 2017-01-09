#ifndef COMPONENT_GAME_BATTLER_H_
#define COMPONENT_GAME_BATTLER_H_

#include "Data/BattlerStatus.h"
#include "Data/Creature.h"
#include "Data/Skill.h"
#include "Data/UseItem.h"

#include "Component/Game/Basic.h"

namespace gamecomp {


/// Damage/Hit Info
struct BattlerDamage {
    data::attr_t hpdamage = 0;            ///< damage of HP
    data::attr_t mpdamage = 0;            ///< damage of MP
    option_t ismiss = false;         ///< is attack Miss
    option_t iseva = false;          ///< is Enemy evade
    option_t isimmune = false;       ///< is Enemy Immune (Elements)
    option_t isimmunestatus = false; ///< is Enemy Immune (BattlerStatus)
    option_t iscriticalhit = false;  ///< is Critical Hit
    option_t isabsorbhp = false;     ///< is absorb HP effect
    option_t isabsorbmp = false;     ///< is absorb MP effect
    option_t iszerodamage = false;   ///< have no Damage
};

struct BattlerStatusTurn {
    std::string battlerstatus_name;
    data::turns_t turn = 0;

    BattlerStatusTurn() = default;
    explicit BattlerStatusTurn(std::string p_battlerstatus_name)
        : battlerstatus_name(p_battlerstatus_name) {}
    BattlerStatusTurn(std::string p_battlerstatus_name, data::turns_t p_turn)
        : battlerstatus_name(p_battlerstatus_name), turn(p_turn) {}
};

struct ElementResist {
    std::string element_name;
    data::Resist resist;

    ElementResist() = default;
    ElementResist(std::string p_element_name, data::Resist p_resist)
        : element_name(p_element_name), resist(p_resist) {}
};

struct BattlerStatusResist {
    std::string battlerstatus_name;
    data::Resist resist;

    BattlerStatusResist() = default;
    BattlerStatusResist(std::string p_battlerstatus_name, data::Resist p_resist)
        : battlerstatus_name(p_battlerstatus_name), resist(p_resist) {}
};

struct BattlerStatusesComponent {
    std::vector<std::string> statuses_name;

    /// start Turn of Statuses
    std::vector<BattlerStatusTurn> startstatusturns;

    data::StatusRestrictionOption statusrestriction =
        data::StatusRestrictionOption::None;
};


struct BattlerBattleStateComponent {
    /// current Battle turn to count turn for recover BattlerStatus after Turn
    data::turns_t turn = 0;

    /// Battler Option
    earr::enum_array<data::BattlerOption, option_t> option;

    option_t immortal = false;    ///< immortal Battler
    option_t active = true;       ///< Battler is active on BattleField
    option_t isdefending = false; ///< Battler is Definding
    option_t isescapeing = false; ///< is escapeing (in Battle)
};

struct BattlerResistsComponent {
    std::vector<std::string> atk_elements_name;

    /**
     * Resist of Element
     * with out Weapons, Armor, Item, ...
     */
    std::vector<ElementResist> elementresist;

    /**
     * Resist of BattlerStatus
     * with out Weapons, Armor, Item, ...
     */
    std::vector<BattlerStatusResist> statusresist;
};
} // namespace gamecomp


#endif // COMPONENT_GAME_BATTLER_H_
