#ifndef COMPONENT_GAME_BATTLER_H_
#define COMPONENT_GAME_BATTLER_H_

#include "Data/BattlerStatus.h"
#include "Data/Creature.h"
#include "Data/Skill.h"
#include "Data/UseItem.h"

#include "Component/Basic.h"

namespace gamecomp {

/// Damage/Hit Info
struct BattlerDamage {
    int hpdamage = 0;            ///< damage of HP
    int mpdamage = 0;            ///< damage of MP
    bool ismiss = false;         ///< is attack Miss
    bool iseva = false;          ///< is Enemy evade
    bool isimmune = false;       ///< is Enemy Immune (Elements)
    bool isimmunestatus = false; ///< is Enemy Immune (BattlerStatus)
    bool iscriticalhit = false;  ///< is Critical Hit
    bool isabsorbhp = false;     ///< is absorb HP effect
    bool isabsorbmp = false;     ///< is absorb MP effect
    bool iszerodamage = false;   ///< have no Damage
};

struct BattlerStatusTurn {
    std::string battlerstatus_name;
    int turn = 0;

    BattlerStatusTurn() = default;
    explicit BattlerStatusTurn(std::string p_battlerstatus_name)
        : battlerstatus_name(p_battlerstatus_name) {}
    BattlerStatusTurn(std::string p_battlerstatus_name, int p_turn)
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

struct BattlerStatuses : public entityx::Component<BattlerStatuses> {
    std::vector<std::string> statuses_name;

    /// start Turn of Statuses, {BattlerStatusID, turn}
    std::vector<BattlerStatusTurn> startstatusturn;

    data::StatusRestrictionOption statusrestriction =
        data::StatusRestrictionOption::None;
};

struct BattlerBattleState : public entityx::Component<BattlerBattleState> {
    /// current Battle turn to count turn for recover BattlerStatus after Turn
    size_t turn = 0;

    /// Battler Option
    earr::enum_array<data::BattlerOption, bool> option;

    bool immortal = false;    ///< immortal Battler
    bool active = true;       ///< Battler is active on BattleField
    bool isdefending = false; ///< Battler is Definding
    bool isescapeing = false; ///< is escapeing (in Battle)
};

struct BattlerResists : public entityx::Component<BattlerResists> {
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
