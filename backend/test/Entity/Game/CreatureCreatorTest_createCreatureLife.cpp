#include "doctest.h"

#include "Entity/Game/CreatureEntityCreator.h"

#include "Entity/Game/EntityGameTestHelper.h"


TEST_CASE("create CreatureLife Component") {
    gameentity::CreatureEntityCreator creaturecreator;
    gameentity::CreatureBattlerCreator creaturebattler_creator;

    auto creature = CreatureTestData::make_DataCreature();
    auto creature_data = creaturebattler_creator.createCreatureData(creature);
    auto realtime = CreatureTestData::make_time_point_01_01_2000();
    auto battler = creaturebattler_creator.createCreatureBattler();
    auto gene = creaturecreator.createCreatureGene(creature_data);

    auto life = creaturecreator.createCreatureLife(creature_data, realtime,
                                                   battler, gene);

    SUBCASE("Creature name is set") {
        CHECK(CreatureTestData::CREATURENAME == life.name);
    }

    SUBCASE("CreatureLevel is set") {
        CHECK(creature.getCreatureLevel() == life.creaturelevel);
    }

    SUBCASE("CreatureCircadianRhythm is set") {
        CHECK(creature.getCreatureCircadianRhythm() ==
                life.creaturecircadianrhythm);
    }

    SUBCASE("oldLevel is set") { CHECK(battler.lvl == life.oldlevel); }

    SUBCASE("is not busy") { CHECK_FALSE(life.isbusy); }

    SUBCASE("maxLifeTime is set") {
        CHECK(life.maxlifetime >= gene.totalmaxlifetime);
    }

    SUBCASE("ageingTime is set") {
        CHECK(life.ageingtime > std::chrono::milliseconds::zero());
    }

    SUBCASE("causeOfDeath is Alive (not Dead)") {
        REQUIRE_FALSE(life.isdead);
        CHECK(+gamecomp::CauseOfDeath::Alive == life.causeofdeath);
    }

    SUBCASE("Creature is born (not Egg)") {
        REQUIRE(CreatureTestData::CREATURELEVEL != +data::CreatureLevel::Egg);
        CHECK(life.born);
    }

    SUBCASE("Creature has none special status") {
        CHECK_FALSE(earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Hungry));
    }
}
