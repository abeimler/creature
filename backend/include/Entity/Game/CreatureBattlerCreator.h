#ifndef ENTITY_GAME_CREATUREBATTLERCREATOR_H_
#define ENTITY_GAME_CREATUREBATTLERCREATOR_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Component/Game/Battler.h"
#include "Component/Game/Creature.h"
#include "Component/Game/CreatureBattler.h"
#include "Component/Game/CreatureGene.h"
#include "Component/Game/CreatureMemory.h"

namespace gameentity {

class CreatureBattlerCreator {
    private:
    static constexpr data::attr_t MIN_INFLATION = 33;
    static constexpr data::attr_t MAX_INFLATION = 131;

    public:
    static bool
    isSkillLearned(const std::vector<std::shared_ptr<data::Skill>>& skills,
                   std::string skill_name);
    static bool isSkillLearned(const std::vector<std::string>& skills,
                               std::string skill_name);

    static data::attr_t getAttr(const gamecomp::CreatureBattlerComponent& battler,
                       data::Attribute attr);

    static void setHP(data::attr_t value, gamecomp::CreatureBattlerComponent& battler);
    static void setMP(data::attr_t value, gamecomp::CreatureBattlerComponent& battler);

    static void setAttr(data::Attribute attr, data::attr_t value,
                        gamecomp::CreatureBattlerComponent& battler);


    static void updateNewLvL(gamecomp::CreatureBattlerComponent& battler,
                             const data::Creature& creature);

    static void setEXP(gamecomp::CreatureBattlerComponent& battler,
                       const data::Creature& creature, data::attr_t exp);

    static void setLvL(gamecomp::CreatureBattlerComponent& battler,
                       const data::Creature& creature, data::lvl_t lvl);

    static constexpr data::attr_t getMinInflation() { return MIN_INFLATION; }
    static constexpr data::attr_t getMaxInflation() { return MAX_INFLATION; }

    /**
    * @param minlvl Minimal Level
    * @param maxlvl Maximal Level
    * @param basic basic value
    * @param inf inflation
    * @param boni_inf bonus inflation
    * @param boni_factor bonus factor
    * @brief formula: <br>
    *       i = minlvl..maxlvl <br>
    *       p = 1.3 + inflation / 120 <br>
    *       n = basic * (i+4)^p / 5^p; <br>
    *       attr[i] = n
    */
    template <class T>
    static std::vector<T> genAttrs(data::lvl_t minlvl, data::lvl_t maxlvl, 
                                   data::attr_t basic, data::attr_t inf,
                                   data::attr_t boni_inf, data::attr_factor_t boni_factor) {
        size_t minlvli = static_cast<size_t>(std::max<int>(0, minlvl));
        size_t maxlvli = static_cast<size_t>(std::max<int>(0, maxlvl));
        size_t attrs_size =
            static_cast<size_t>(std::max<int>(1, minlvl + maxlvl + 1));

        std::vector<T> attrs;
        attrs.resize(attrs_size);
        std::fill(std::begin(attrs), std::end(attrs), 0);

        auto mininf = getMinInflation();
        auto maxinf = getMaxInflation();

        auto powi = 1 + (mininf / maxinf) + (inf + boni_inf) / mininf;
        double n = 0.0;
        for (size_t i = minlvli; i <= maxlvli; i++) {
            if (basic != 0 && inf != 0) {
                n = (basic * boni_factor) * std::pow(i + 4, powi) /
                    std::pow(5, powi);
            } else {
                n = 0.0;
            }
            attrs[i] = static_cast<T>(n);
        }

        return attrs;
    }

    template <class T>
    static std::vector<T> genAttrs(const data::Creature& creature,
                                   data::Attribute attr) {
        auto minlvl = creature.getMinLvL();
        auto maxlvl = creature.getMaxLvL();
        auto inf = creature.getAttrInflation(attr);
        auto basic = creature.getAttrBasis(attr);
        data::attr_t boni_inf = 0;
        data::attr_factor_t boni_factor = 1.0;

        return genAttrs<T>(minlvl, maxlvl, basic, inf, boni_inf, boni_factor);
    }


    template <class T>
    static std::vector<T>
    genAttrs(const data::Creature& creature,
             const gamecomp::CreatureBattlerGeneComponent& gene,
             data::Attribute attr) {
        auto minlvl = creature.getMinLvL();
        auto maxlvl = creature.getMaxLvL();
        auto inf = creature.getAttrInflation(attr);
        auto basic = creature.getAttrBasis(attr);
        auto boni_inf = earr::enum_array_at(gene.boniattrinflation, attr);
        auto boni_factor = earr::enum_array_at(gene.boniattrfactor, attr);

        return genAttrs<T>(minlvl, maxlvl, basic, inf, boni_inf, boni_factor);
    }

    CreatureBattlerCreator();

    gamecomp::CreatureDataComponent
    createCreatureData(const data::Creature& creature);

    gamecomp::CreatureBattlerComponent createCreatureBattler();

    gamecomp::CreatureBattlerGeneComponent createCreatureBattlerGene();

    gamecomp::BattlerBattleStateComponent createBattlerBattleState();

    gamecomp::BattlerBattleStateComponent
    createBattlerBattleState(const data::Creature& creature);

    gamecomp::BattlerResistsComponent
    createBattlerResists(const data::Creature& creature);



    void loadCreatureBattler(
        gamecomp::CreatureBattlerComponent& battler,
        const data::Creature& creature,
        const gamecomp::CreatureBattlerGeneComponent& gene, data::lvl_t lvl);

    inline void loadCreatureBattler(
        gamecomp::CreatureBattlerComponent& battler,
        const data::Creature& creature,
        const gamecomp::CreatureBattlerGeneComponent& battlergene) {
        auto start_lvl = creature.getStartLvL();
        loadCreatureBattler(battler, creature, battlergene, start_lvl);
    }

    inline void transformCreatureBattler(
        gamecomp::CreatureBattlerComponent& battler,
        const data::Creature& creature,
        const gamecomp::CreatureBattlerGeneComponent& battlergene) {
        loadCreatureBattler(battler, creature, battlergene, battler.lvl);
    }
};
} // namespace gameentity

#endif // ENTITY_GAME_CREATUREBATTLERCREATOR_H_
