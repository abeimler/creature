#include <fstream>
#include <thread>

#include <cereal/archives/json.hpp>
#include <json.hpp>


#include "doctest.h"


#include "Entity/Game/CreatureEntityCreator.h"

#include "Entity/Game/EntityGameTestHelper.h"

#include "Entity/Game/CreatureTestDataEvolution.h"



TEST_CASE("data::Creature serial json") {
    CreatureTestData creatureTestData;
    gameentity::CreatureEntityCreator creaturecreator;

    auto creature = creatureTestData.make_DataCreature();

    auto& data = creature;

    SUBCASE("serial json") {
        std::stringstream ss;
        {
            cereal::JSONOutputArchive outar(ss);

            CHECK_NOTHROW(outar(cereal::make_nvp("data", data)));
        }

        std::string output = ss.str();
        REQUIRE(!output.empty());

        SUBCASE("deserial json") {
            {
                cereal::JSONInputArchive inar(ss);

                CHECK_NOTHROW(inar(cereal::make_nvp("data", data)));
            }
        }
    }
}



TEST_CASE("data::Creature serial json as file") {
    CreatureTestData creatureTestData;
    gameentity::CreatureEntityCreator creaturecreator;

    auto creature = creatureTestData.make_DataCreature();

    auto& data = creature;

    SUBCASE("serial json") {
        std::ofstream os("creature.json");
        {
            cereal::JSONOutputArchive outar(os);

            CHECK_NOTHROW(outar(cereal::make_nvp("data", data)));
        }
    }
}

TEST_CASE("data::Creatures serial json as file") {
    gameentity::CreatureEntityCreator creaturecreator;

    auto creatures = CreatureTestEvolution::make_DataCreature_Evolutions();

    auto& data = creatures;

    SUBCASE("serial json") {
        std::ofstream os("creatures.json");
        {
            cereal::JSONOutputArchive outar(os);

            CHECK_NOTHROW(outar(cereal::make_nvp("data", data)));
        }
    }
}