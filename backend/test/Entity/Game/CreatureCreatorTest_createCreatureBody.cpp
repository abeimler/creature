#include "doctest.h"

#include "Entity/Game/CreatureCreator.h"

#include "Entity/Game/EntityGameTestHelper.h"


TEST_CASE("create CreatureBody Component with DataCreature") {
    gameentity::CreatureCreator creaturecreator;
    gameentity::CreatureBattlerCreator creaturebattler_creator;

    auto creature = CreatureTestData::make_DataCreature();
    auto creature_data = creaturebattler_creator.createCreatureData(creature);
    auto gene = creaturecreator.createCreatureGene(creature_data);

    auto body = creaturecreator.createCreatureBody(creature_data, gene);

    SUBCASE("Weight is set") { CHECK(body.weight > 0.0f); }

    SUBCASE("Bodysize is set") { CHECK(body.bodysize > 0.0f); }

    SUBCASE("BMI is set") { CHECK(body.bmi > 0.0f); }
}
