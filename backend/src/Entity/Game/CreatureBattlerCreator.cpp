#include "Entity/Game/CreatureBattlerCreator.h"

namespace gameentity {

bool CreatureBattlerCreator::isSkillLearned(
    const std::vector<std::shared_ptr<data::Skill>>& skills,
    std::string skill_name) {
    auto find_func = [skill_name](const std::shared_ptr<data::Skill>& skill) {
        return skill && skill->getName() == skill_name;
    };

    return std::find_if(std::begin(skills), std::end(skills), find_func) !=
           std::end(skills);
}

bool CreatureBattlerCreator::isSkillLearned(
    const std::vector<std::string>& skills, std::string skill_name) {
    auto find_func = [skill_name](const std::string& skill) {
        return skill == skill_name;
    };

    return std::find_if(std::begin(skills), std::end(skills), find_func) !=
           std::end(skills);
}

CreatureBattlerCreator::CreatureBattlerCreator() = default;

int CreatureBattlerCreator::getAttr(
    const gamecomp::CreatureBattlerComponent& battler, data::Attribute attr) {
    int attr_base_value = earr::enum_array_at(battler.attrbase, attr);
    int attr_plus_value = earr::enum_array_at(battler.attrplus, attr);
    return attr_base_value + attr_plus_value;
}

void CreatureBattlerCreator::setHP(
    int value, gamecomp::CreatureBattlerComponent& battler) {
    battler.hp = clamp(value, 0, getAttr(battler, data::Attribute::MaxMP));
}

void CreatureBattlerCreator::setMP(
    int value, gamecomp::CreatureBattlerComponent& battler) {
    battler.mp = clamp(value, 0, getAttr(battler, data::Attribute::MaxMP));
}


void CreatureBattlerCreator::setAttr(
    data::Attribute attr, int value,
    gamecomp::CreatureBattlerComponent& battler) {
    earr::enum_array_at(battler.attrplus, attr) =
        value - earr::enum_array_at(battler.attrbase, attr);
    earr::enum_array_at(battler.attr, attr) = value;

    if (attr == +data::Attribute::MaxHP) {
        setHP(battler.hp, battler);
    } else if (attr == +data::Attribute::MaxMP) {
        setMP(battler.mp, battler);
    }
}


void CreatureBattlerCreator::updateNewLvL(
    gamecomp::CreatureBattlerComponent& battler,
    const data::Creature& creature) {
    battler.lvl = std::max<int>(battler.lvl, creature.getMinLvL());
    battler.lvl = std::min<int>(battler.lvl, creature.getMaxLvL());

    for (const auto& lskill : creature.getSkills()) {
        if (battler.lvl >= lskill.getLvL()) {
            auto skill_name = lskill.getSkillName();
            if (!isSkillLearned(battler.learned_skills_name, skill_name)) {
                battler.learned_skills_name.push_back(skill_name);
            }
        }
    }

    if (battler.lvl >= 0) {
        for (auto index : earr::Enum<data::Attribute>()) {
            auto& params = earr::enum_array_at(battler.attrparam, index);
            if (battler.lvl >= 0 &&
                static_cast<size_t>(battler.lvl) < params.size()) {
                earr::enum_array_at(battler.attrbase, index) =
                    params[static_cast<size_t>(battler.lvl)];

                earr::enum_array_at(battler.attr, index) =
                    earr::enum_array_at(battler.attrbase, index) +
                    earr::enum_array_at(battler.attrplus, index);
            }
        }
    }

    setHP(battler.hp, battler);
    setMP(battler.mp, battler);
}

void CreatureBattlerCreator::setEXP(gamecomp::CreatureBattlerComponent& battler,
                                    const data::Creature& creature, int exp) {
    size_t battler_exp_size =
        earr::enum_array_at(battler.attrparam, +data::Attribute::Exp).size();
    if (battler.lvl >= 0 &&
        static_cast<size_t>(battler.lvl) < battler_exp_size) {
        battler.exp = exp;
        battler.lvl = creature.getMinLvL();
        auto& attrBaseExp =
            earr::enum_array_at(battler.attrbase, +data::Attribute::Exp);
        auto& attrParamExp =
            earr::enum_array_at(battler.attrparam, +data::Attribute::Exp);

        attrBaseExp = (battler.lvl >= 0)
                          ? attrParamExp[static_cast<size_t>(battler.lvl)]
                          : 0;
        while (battler.lvl <= creature.getMaxLvL() &&
               battler.exp >= getAttr(battler, +data::Attribute::Exp)) {
            battler.lvl++;
            if (battler.lvl >= 0 &&
                static_cast<size_t>(battler.lvl) < attrParamExp.size()) {
                attrBaseExp = attrParamExp[static_cast<size_t>(battler.lvl)];
            }
        }

        earr::enum_array_at(battler.attr, +data::Attribute::Exp) =
            earr::enum_array_at(battler.attrbase, +data::Attribute::Exp) +
            earr::enum_array_at(battler.attrplus, +data::Attribute::Exp);

        updateNewLvL(battler, creature);
    }
}

void CreatureBattlerCreator::setLvL(gamecomp::CreatureBattlerComponent& battler,
                                    const data::Creature& creature, int lvl) {
    auto& attrParamExp =
        earr::enum_array_at(battler.attrparam, +data::Attribute::Exp);
    if (lvl > 0 && (static_cast<size_t>(lvl) - 1) < attrParamExp.size()) {
        setEXP(battler, creature, attrParamExp[static_cast<size_t>(lvl) - 1]);
    } else {
        battler.exp = 0;
    }
}


gamecomp::CreatureDataComponent
CreatureBattlerCreator::createCreatureData(const data::Creature& creature) {
    gamecomp::CreatureDataComponent creature_data;

    creature_data.creature = creature;

    return creature_data;
}

gamecomp::CreatureBattlerComponent
CreatureBattlerCreator::createCreatureBattler() {
    gamecomp::CreatureBattlerComponent ret;

    ret.attrbase.fill(0);
    ret.attrinf.fill(0);
    ret.attrplus.fill(0);
    ret.attr.fill(0);

    return ret;
}


gamecomp::CreatureBattlerGeneComponent
CreatureBattlerCreator::createCreatureBattlerGene() {
    gamecomp::CreatureBattlerGeneComponent ret;

    ret.boniattrfactor.fill(1.0);
    ret.boniattrinflation.fill(1.0);

    return ret;
}

gamecomp::BattlerBattleStateComponent
CreatureBattlerCreator::createBattlerBattleState() {
    gamecomp::BattlerBattleStateComponent ret;

    ret.option.fill(false);

    return ret;
}

gamecomp::BattlerBattleStateComponent
CreatureBattlerCreator::createBattlerBattleState(
    const data::Creature& creature) {
    gamecomp::BattlerBattleStateComponent ret;

    ret.option = creature.getOption();

    return ret;
}

gamecomp::BattlerResistsComponent
CreatureBattlerCreator::createBattlerResists(const data::Creature& creature) {
    gamecomp::BattlerResistsComponent ret;


    ret.atk_elements_name = creature.getElements();

    const auto& data_element_resist = creature.getElementResist();
    ret.elementresist.clear();
    ret.elementresist.reserve(data_element_resist.size());
    for (const auto& elem_res : data_element_resist) {
        ret.elementresist.push_back(
            gamecomp::ElementResist(elem_res.first, elem_res.second));
    }

    const auto& data_status_resist = creature.getStatusResist();
    ret.statusresist.clear();
    ret.statusresist.reserve(data_status_resist.size());
    for (const auto& elem_res : data_status_resist) {
        ret.statusresist.push_back(
            gamecomp::BattlerStatusResist(elem_res.first, elem_res.second));
    }

    return ret;
}

void CreatureBattlerCreator::loadCreatureBattler(
    gamecomp::CreatureBattlerComponent& battler, const data::Creature& creature,
    const gamecomp::CreatureBattlerGeneComponent& gene, int lvl) {

    for (auto index : earr::Enum<data::Attribute>()) {
        earr::enum_array_at(battler.attrparam, index) =
            genAttrs<int>(creature, gene, index);
    }

    for (auto index : earr::Enum<data::Attribute>()) {
        earr::enum_array_at(battler.attrinf, index) =
            creature.getAttrInflation(index);
    }

    if (lvl >= 0) {
        size_t lvl_index = static_cast<size_t>(lvl);
        for (auto index : earr::Enum<data::Attribute>()) {
            auto& attrParam = earr::enum_array_at(battler.attrparam, index);
            earr::enum_array_at(battler.attrbase, index) =
                (lvl_index < attrParam.size()) ? attrParam[lvl_index] : 0;
        }
    } else {
        battler.attrbase.fill(0);
    }

    if (battler.lvl != lvl) {
        setLvL(battler, creature, lvl);
    }

    for (const auto& lskill : creature.getSkills()) {
        if (battler.lvl == lskill.getLvL()) {
            auto skill_name = lskill.getSkillName();
            if (!isSkillLearned(battler.learned_skills_name, skill_name)) {
                battler.learned_skills_name.push_back(skill_name);
            }
        }
    }
}
} // namespace gameentity
