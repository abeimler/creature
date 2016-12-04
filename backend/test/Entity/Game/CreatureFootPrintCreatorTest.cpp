#include <fstream>
#include <string>
#include <iostream>

#include "doctest.h"

#include "Entity/Game/CreatureEntityCreator.h"
#include "Entity/Game/CreatureFootPrintCreator.h"

#include "Entity/Game/EntityGameTestHelper.h"

TEST_CASE("create print with CreatureFootPrintCreator") {
    gameentity::CreatureFootPrintCreator printcreator;
    gameentity::CreatureEntityCreator creaturecreator;

    std::string creature_name = "Koromon";
    data::CreatureLevel creature_level = data::CreatureLevel::Baby2;

    // bodysize
    // double min_bodysize = 0.62f;
    double max_bodysize = 1.52f;
    double bodysize = 1.4f;

    // body weight
    double min_weight = 4;
    double max_weight = 80;
    double weight = 10;

    // bmi
    double min_bmi = 10;
    double max_bmi = 40;
    double ideal_bmi = 22;

    double high_weight = 30;
    double low_weight = 5;

    /*
    double ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);
    */
    double ideal_mass = 35.51;

    std::string expectedPrint = 
        "******\n"
        "******\n"
        "  **  \n"
        "  **  \n"
        "******\n"
        "******\n"
        "******\n"
        "******\n";


    SUBCASE("generate print") {
        std::string print = printcreator.createPrintString(creature_name, creature_level, ideal_mass, bodysize);

        SUBCASE("print is right") {
            CHECK(expectedPrint == print);
        }
    }
}



