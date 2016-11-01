#include "doctest.h"

#include "Entity/Game/CreatureCreator.h"

#include "EntityGameTestHelper.h"

TEST_CASE("get BMI and Mass right from CreatureCreator with normal values") {
    gameentity::CreatureCreator creaturecreator;

    // bodysize
    // float min_bodysize = 1.2f;
    float max_bodysize = 2.2f;
    float bodysize = 1.8f;

    // body weight
    float min_weight = 35;
    float max_weight = 560;
    float weight = 70;

    // bmi
    float min_bmi = 10;
    float max_bmi = 40;
    float ideal_bmi = 22;

    float high_weight = 90;
    float low_weight = 56;

    SUBCASE("get body mass") {
        float ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        //CAPTURE(ideal_mass);

        SUBCASE("got body mass") { CHECK(ideal_mass > 0.0f); }

        gamecomp::CreatureGeneComponent gene;
        gene.bodymass = ideal_mass;
        gene.ideal_bmi = ideal_bmi;
        gene.max_bmi = max_bmi;
        gene.max_bodysize = max_bodysize;
        gene.min_bmi = min_bmi;

        SUBCASE("get bmi from mass") {
            float bmi_mass = creaturecreator.getBMI(
                gene, min_weight, max_weight, weight, bodysize);

            SUBCASE("got bmi from mass") {
                CHECK(bmi_mass > 0.0f);
                CHECK(bmi_mass == doctest::Approx(ideal_bmi).epsilon(0.01));
            }

            SUBCASE("get bodysize from mass and bmi") {
                float bodysize_mass = creaturecreator.getBodySize(
                    min_bmi, max_bmi, bmi_mass, ideal_mass, min_weight,
                    max_weight, weight);

                SUBCASE("got bmi from mass") {
                    CHECK(bodysize_mass > 0.0f);
                    CHECK(bodysize_mass == doctest::Approx(bodysize).epsilon(0.01));
                }
            }
        }


        SUBCASE("get low bmi by lower weight") {
            float low_bmi = creaturecreator.getBMI(gene, min_weight, max_weight,
                                                   low_weight, bodysize);

            SUBCASE("got lower bmi") { CHECK(low_bmi < ideal_bmi); }
        }

        SUBCASE("get high bmi by higher weight") {
            float high_bmi = creaturecreator.getBMI(
                gene, min_weight, max_weight, high_weight, bodysize);

            SUBCASE("got higer bmi") { CHECK(high_bmi > ideal_bmi); }
        }
    }
}


TEST_CASE("get BMI and Mass right from CreatureCreator with big values") {
    gameentity::CreatureCreator creaturecreator;

    // bodysize
    // float min_bodysize = 4.4f;
    float max_bodysize = 10.0f;
    float bodysize = 8.0f;

    // body weight
    float min_weight = 50;
    float max_weight = 500;
    float weight = 130;

    // bmi
    float min_bmi = 100;
    float max_bmi = 400;
    float ideal_bmi = 220;

    float high_weight = 200;
    float low_weight = 60;

    SUBCASE("get body mass") {
        float ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        //CAPTURE(ideal_mass);

        SUBCASE("got body mass") { CHECK(ideal_mass > 0.0f); }

        gamecomp::CreatureGeneComponent gene;
        gene.bodymass = ideal_mass;
        gene.ideal_bmi = ideal_bmi;
        gene.max_bmi = max_bmi;
        gene.max_bodysize = max_bodysize;
        gene.min_bmi = min_bmi;

        SUBCASE("get bmi from mass") {
            float bmi_mass = creaturecreator.getBMI(
                gene, min_weight, max_weight, weight, bodysize);

            SUBCASE("got bmi from mass") {
                CHECK(bmi_mass > 0.0f);
                CHECK(bmi_mass == doctest::Approx(ideal_bmi).epsilon(0.01));
            }

            SUBCASE("get bodysize from mass and bmi") {
                float bodysize_mass = creaturecreator.getBodySize(
                    min_bmi, max_bmi, bmi_mass, ideal_mass, min_weight,
                    max_weight, weight);

                SUBCASE("got bmi from mass") {
                    CHECK(bodysize_mass > 0.0f);
                    CHECK(bodysize_mass == doctest::Approx(bodysize).epsilon(0.01));
                }
            }
        }


        SUBCASE("get low bmi by lower weight") {
            float low_bmi = creaturecreator.getBMI(gene, min_weight, max_weight,
                                                   low_weight, bodysize);

            SUBCASE("got lower bmi") { CHECK(low_bmi < ideal_bmi); }
        }

        SUBCASE("get high bmi by higher weight") {
            float high_bmi = creaturecreator.getBMI(
                gene, min_weight, max_weight, high_weight, bodysize);

            SUBCASE("got higer bmi") { CHECK(high_bmi > ideal_bmi); }
        }
    }
}

TEST_CASE("get BMI and Mass right from CreatureCreator with small values") {
    gameentity::CreatureCreator creaturecreator;

    // bodysize
    // float min_bodysize = 0.1f;
    float max_bodysize = 1.0f;
    float bodysize = 0.5f;

    // body weight
    float min_weight = 1;
    float max_weight = 8;
    float weight = 2;

    // bmi
    float min_bmi = 10;
    float max_bmi = 40;
    float ideal_bmi = 22;

    float high_weight = 5;
    float low_weight = 1.25;

    SUBCASE("get body mass") {
        float ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        //CAPTURE(ideal_mass);

        SUBCASE("got body mass") { CHECK(ideal_mass > 0.0f); }

        gamecomp::CreatureGeneComponent gene;
        gene.bodymass = ideal_mass;
        gene.ideal_bmi = ideal_bmi;
        gene.max_bmi = max_bmi;
        gene.max_bodysize = max_bodysize;
        gene.min_bmi = min_bmi;

        SUBCASE("get bmi from mass") {
            float bmi_mass = creaturecreator.getBMI(
                gene, min_weight, max_weight, weight, bodysize);

            SUBCASE("got bmi from mass") {
                CHECK(bmi_mass > 0.0f);
                CHECK(bmi_mass == doctest::Approx(ideal_bmi).epsilon(0.01));
            }

            SUBCASE("get bodysize from mass and bmi") {
                float bodysize_mass = creaturecreator.getBodySize(
                    min_bmi, max_bmi, bmi_mass, ideal_mass, min_weight,
                    max_weight, weight);

                SUBCASE("got bmi from mass") {
                    CHECK(bodysize_mass > 0.0f);
                    CHECK(bodysize_mass == doctest::Approx(bodysize).epsilon(0.01));
                }
            }
        }


        SUBCASE("get low bmi by lower weight") {
            float low_bmi = creaturecreator.getBMI(gene, min_weight, max_weight,
                                                   low_weight, bodysize);

            SUBCASE("got lower bmi") { CHECK(low_bmi < ideal_bmi); }
        }

        SUBCASE("get high bmi by higher weight") {
            float high_bmi = creaturecreator.getBMI(
                gene, min_weight, max_weight, high_weight, bodysize);

            SUBCASE("got higer bmi") { CHECK(high_bmi > ideal_bmi); }
        }
    }
}



TEST_CASE("create empty Creature Entity") {
    gameentity::EntityManager manager;
    gameentity::CreatureCreator creaturecreator;

    auto entity = manager.create();
    creaturecreator.create(entity);

    SUBCASE("get CreatureLife Component and check valid") {
        auto creaturelife = entity.component<gamecomp::CreatureLifeComponent>();

        CHECK(creaturelife.valid());
    }

    SUBCASE("get CreatureProgressTimers Component and check valid") {
        auto creatureprogresstimers =
            entity.component<gamecomp::CreatureProgressTimersComponent>();

        CHECK(creatureprogresstimers.valid());
    }
}



TEST_CASE("create Creature Entity with Creatue Data") {
    gameentity::EntityManager manager;
    gameentity::CreatureCreator creaturecreator;

    auto creature = CreatureTestData::make_DataCreature();
    auto time = CreatureTestData::make_time_point_01_01_2000();

    auto entity = manager.create();

    creaturecreator.create(entity, creature, time, 1.0f);

    auto creaturebattler = entity.component<gamecomp::CreatureBattlerComponent>();


    SUBCASE("CreatureBattler minimal level") {
        CHECK(creaturebattler->lvl >= creature.getMinLvL());
    }
    SUBCASE("CreatureBattler has right Level") {
        CHECK(1 == creaturebattler->lvl);
    }
    SUBCASE("CreatureBattler maximal level") {
        CHECK(creaturebattler->lvl <= creature.getMaxLvL());
    }



    SUBCASE("CreatureBattler has right base Attribute, front") {
        data::Attribute index = data::Attribute::MaxHP;
        CHECK(earr::enum_array_at(creaturebattler->attrbase, index) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right base Attribute, back") {
        data::Attribute index = data::Attribute::Exp;
        CHECK(earr::enum_array_at(creaturebattler->attrbase, index) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right inflation Attribute, front") {
        data::Attribute index = data::Attribute::MaxHP;
        CHECK(earr::enum_array_at(creaturebattler->attrinf, index) >=
                creature.getAttrInflation(index));
    }

    SUBCASE("CreatureBattler has right inflation Attribute, back") {
        data::Attribute index = data::Attribute::Exp;
        CHECK(earr::enum_array_at(creaturebattler->attrinf, index) >=
                creature.getAttrInflation(index));
    }



    SUBCASE("CreatureBattler has right Attribute, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMinLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler->attrparam, index)
                    .at(static_cast<size_t>(creature.getMinLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right Attribute, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMaxLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler->attrparam, index)
                    .at(static_cast<size_t>(creature.getMaxLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("Attibutes has right size, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        CHECK(earr::enum_array_at(creaturebattler->attrparam, index).size() >=
                static_cast<size_t>(creature.getMinLvL()));
    }

    SUBCASE("Attibutes has right size, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        CHECK(earr::enum_array_at(creaturebattler->attrparam, index).size() >=
                static_cast<size_t>(creature.getMaxLvL()));
    }
}
