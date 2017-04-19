#include <thread>

#include "doctest.h"

#include "Application/GameApplication.h"



SCENARIO("Creature GameApplication and create creature entity"
         "status Hungry") {
    GIVEN("Creature GameApplication") {
        game::GameApplication app;

        auto& entities = app.getEntityManager();
        auto& creaturecreator = app.getCreatureEntityCreator();


        WHEN("create creature entity") {
            auto entity = entities.create();
            creaturecreator.create(entities, entity);

            REQUIRE_FALSE(entities.empty());

            THEN("entity has some component") {
                CHECK(entities.has<gamecomp::CreatureDataComponent>(entity));
            }
        }
    }
}

