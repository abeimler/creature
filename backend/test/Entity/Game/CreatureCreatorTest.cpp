#include "doctest.h"

#include "Entity/Game/CreatureEntityCreator.h"

#include "Entity/Game/EntityGameTestHelper.h"

TEST_CASE("get BMI and Mass right from CreatureCreator with normal values") {
    gameentity::CreatureEntityCreator creaturecreator;

    // bodysize
    // double min_bodysize = 1.2f;
    double max_bodysize = 2.2f;
    double bodysize = 1.8f;

    // body weight
    double min_weight = 35;
    double max_weight = 560;
    double weight = 70;

    // bmi
    double min_bmi = 10;
    double max_bmi = 40;
    double ideal_bmi = 22;

    double high_weight = 90;
    double low_weight = 56;

    SUBCASE("get body mass") {
        double ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        // CAPTURE(ideal_mass);

        SUBCASE("got body mass") { CHECK(ideal_mass > 0.0f); }

        gamecomp::CreatureGeneComponent gene;
        gene.bodymass = ideal_mass;
        gene.ideal_bmi = ideal_bmi;
        gene.max_bmi = max_bmi;
        gene.max_bodysize = max_bodysize;
        gene.min_bmi = min_bmi;

        SUBCASE("get bmi from mass") {
            double bmi_mass = creaturecreator.getBMI(
                gene, min_weight, max_weight, weight, bodysize);

            SUBCASE("got bmi from mass") {
                CHECK(bmi_mass > 0.0f);
                CHECK(bmi_mass == doctest::Approx(ideal_bmi).epsilon(0.01));
            }

            SUBCASE("get bodysize from mass and bmi") {
                double bodysize_mass = creaturecreator.getBodySize(
                    min_bmi, max_bmi, bmi_mass, ideal_mass, min_weight,
                    max_weight, weight);

                SUBCASE("got bmi from mass") {
                    CHECK(bodysize_mass > 0.0f);
                    CHECK(bodysize_mass ==
                          doctest::Approx(bodysize).epsilon(0.01));
                }
            }
        }


        SUBCASE("get low bmi by lower weight") {
            double low_bmi = creaturecreator.getBMI(
                gene, min_weight, max_weight, low_weight, bodysize);

            SUBCASE("got lower bmi") { CHECK(low_bmi < ideal_bmi); }
        }

        SUBCASE("get high bmi by higher weight") {
            double high_bmi = creaturecreator.getBMI(
                gene, min_weight, max_weight, high_weight, bodysize);

            SUBCASE("got higer bmi") { CHECK(high_bmi > ideal_bmi); }
        }
    }
}






TEST_CASE("get BMI and Mass right from CreatureCreator with big values") {
    gameentity::CreatureEntityCreator creaturecreator;

    // bodysize
    // double min_bodysize = 4.4f;
    double max_bodysize = 10.0f;
    double bodysize = 8.0f;

    // body weight
    double min_weight = 50;
    double max_weight = 500;
    double weight = 130;

    // bmi
    double min_bmi = 100;
    double max_bmi = 400;
    double ideal_bmi = 220;

    double high_weight = 200;
    double low_weight = 60;

    SUBCASE("get body mass") {
        double ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        // CAPTURE(ideal_mass);

        SUBCASE("got body mass") { 
            CHECK(ideal_mass > 0.0f); 
        }

        gamecomp::CreatureGeneComponent gene;
        gene.bodymass = ideal_mass;
        gene.ideal_bmi = ideal_bmi;
        gene.max_bmi = max_bmi;
        gene.max_bodysize = max_bodysize;
        gene.min_bmi = min_bmi;

        SUBCASE("get bmi from mass") {
            double bmi_mass = creaturecreator.getBMI(
                gene, min_weight, max_weight, weight, bodysize);

            SUBCASE("got bmi from mass") {
                CHECK(bmi_mass > 0.0f);
                CHECK(bmi_mass == doctest::Approx(ideal_bmi).epsilon(0.01));
            }

            SUBCASE("get bodysize from mass and bmi") {
                double bodysize_mass = creaturecreator.getBodySize(
                    min_bmi, max_bmi, bmi_mass, ideal_mass, min_weight,
                    max_weight, weight);

                SUBCASE("got bmi from mass") {
                    CHECK(bodysize_mass > 0.0f);
                    CHECK(bodysize_mass ==
                          doctest::Approx(bodysize).epsilon(0.01));
                }
            }
        }


        SUBCASE("get low bmi by lower weight") {
            double low_bmi = creaturecreator.getBMI(
                gene, min_weight, max_weight, low_weight, bodysize);

            SUBCASE("got lower bmi") { CHECK(low_bmi < ideal_bmi); }
        }

        SUBCASE("get high bmi by higher weight") {
            double high_bmi = creaturecreator.getBMI(
                gene, min_weight, max_weight, high_weight, bodysize);

            SUBCASE("got higer bmi") { CHECK(high_bmi > ideal_bmi); }
        }
    }
}

TEST_CASE("get BMI and Mass right from CreatureCreator with small values") {
    gameentity::CreatureEntityCreator creaturecreator;

    // bodysize
    // double min_bodysize = 0.1f;
    double max_bodysize = 1.0f;
    double bodysize = 0.5f;

    // body weight
    double min_weight = 1;
    double max_weight = 8;
    double weight = 2;

    // bmi
    double min_bmi = 10;
    double max_bmi = 40;
    double ideal_bmi = 22;

    double high_weight = 5;
    double low_weight = 1.25;

    SUBCASE("get body mass") {
        double ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        // CAPTURE(ideal_mass);

        SUBCASE("got body mass") { CHECK(ideal_mass > 0.0f); }

        gamecomp::CreatureGeneComponent gene;
        gene.bodymass = ideal_mass;
        gene.ideal_bmi = ideal_bmi;
        gene.max_bmi = max_bmi;
        gene.max_bodysize = max_bodysize;
        gene.min_bmi = min_bmi;

        SUBCASE("get bmi from mass") {
            double bmi_mass = creaturecreator.getBMI(
                gene, min_weight, max_weight, weight, bodysize);

            SUBCASE("got bmi from mass") {
                CHECK(bmi_mass > 0.0f);
                CHECK(bmi_mass == doctest::Approx(ideal_bmi).epsilon(0.01));
            }

            SUBCASE("get bodysize from mass and bmi") {
                double bodysize_mass = creaturecreator.getBodySize(
                    min_bmi, max_bmi, bmi_mass, ideal_mass, min_weight,
                    max_weight, weight);

                SUBCASE("got bmi from mass") {
                    CHECK(bodysize_mass > 0.0f);
                    CHECK(bodysize_mass ==
                          doctest::Approx(bodysize).epsilon(0.01));
                }
            }
        }


        SUBCASE("get low bmi by lower weight") {
            double low_bmi = creaturecreator.getBMI(
                gene, min_weight, max_weight, low_weight, bodysize);

            SUBCASE("got lower bmi") { CHECK(low_bmi < ideal_bmi); }
        }

        SUBCASE("get high bmi by higher weight") {
            double high_bmi = creaturecreator.getBMI(
                gene, min_weight, max_weight, high_weight, bodysize);

            SUBCASE("got higer bmi") { CHECK(high_bmi > ideal_bmi); }
        }
    }
}



TEST_CASE("create empty Creature Entity") {
    gameentity::EntityManager manager;
    gameentity::CreatureEntityCreator creaturecreator;

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
    CreatureTestData creatureTestData;
    gameentity::EntityManager manager;
    gameentity::CreatureEntityCreator creaturecreator;

    auto creature = creatureTestData.make_DataCreature();
    auto time = creatureTestData.make_time_point_01_01_2000();

    auto entity = manager.create();

    creaturecreator.create(entity, creature, time, 1.0f);

    auto creaturebattler =
        entity.component<gamecomp::CreatureBattlerComponent>();


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





TEST_CASE("get Mass right from CreatureCreator with quite very big values") {
    gameentity::CreatureEntityCreator creaturecreator;

    // bodysize
    // double min_bodysize = 8.4f;
    //double max_bodysize = 20.4;
    double bodysize = 18.0;

    // body weight
    double min_weight = 16;
    //double max_weight = 320;
    double weight = 50;

    // bmi
    double min_bmi = 10;
    double max_bmi = 40;
    double ideal_bmi = 22;

    SUBCASE("get body mass") {
        double ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        // CAPTURE(ideal_mass);

        SUBCASE("got body mass") { 
            CHECK(ideal_mass == doctest::Approx(0.24).epsilon(0.01)); 
        }
    }
}


TEST_CASE("get Mass right from CreatureCreator with big values") {
    gameentity::CreatureEntityCreator creaturecreator;

    // bodysize
    // double min_bodysize = 4.1f;
    //double max_bodysize = 10.2;
    double bodysize = 8.0;

    // body weight
    double min_weight = 8;
    //double max_weight = 160;
    double weight = 30;

    // bmi
    double min_bmi = 10;
    double max_bmi = 40;
    double ideal_bmi = 22;

    SUBCASE("get body mass") {
        double ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        // CAPTURE(ideal_mass);

        SUBCASE("got body mass") { 
            CHECK(ideal_mass == doctest::Approx(6.25).epsilon(0.01)); 
        }
    }
}


TEST_CASE("get Mass right from CreatureCreator with normal values") {
    gameentity::CreatureEntityCreator creaturecreator;

    // bodysize
    // double min_bodysize = 0.8f;
    //double max_bodysize = 2.0;
    double bodysize = 1.75;

    // body weight
    double min_weight = 6;
    //double max_weight = 120;
    double weight = 20;

    // bmi
    double min_bmi = 10;
    double max_bmi = 40;
    double ideal_bmi = 22;

    SUBCASE("get body mass") {
        double ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        // CAPTURE(ideal_mass);

        SUBCASE("got body mass") { 
            CHECK(ideal_mass == doctest::Approx(20.79).epsilon(0.01)); 
        }
    }
}


TEST_CASE("get Mass right from CreatureCreator with small values") {
    gameentity::CreatureEntityCreator creaturecreator;

    // bodysize
    // double min_bodysize = 0.6f;
    //double max_bodysize = 1.5;
    double bodysize = 1.0;

    // body weight
    double min_weight = 4;
    //double max_weight = 80;
    double weight = 10;

    // bmi
    double min_bmi = 10;
    double max_bmi = 40;
    double ideal_bmi = 22;

    SUBCASE("get body mass") {
        double ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        // CAPTURE(ideal_mass);

        SUBCASE("got body mass") { 
            CHECK(ideal_mass == doctest::Approx(36.51).epsilon(0.01)); 
        }
    }
}

TEST_CASE("get Mass right from CreatureCreator with very small values") {
    gameentity::CreatureEntityCreator creaturecreator;

    // bodysize
    // double min_bodysize = 0.14f;
    //double max_bodysize = 0.34;
    double bodysize = 0.30;

    // body weight
    double min_weight = 2;
    //double max_weight = 40;
    double weight = 5;

    // bmi
    double min_bmi = 10;
    double max_bmi = 40;
    double ideal_bmi = 22;

    SUBCASE("get body mass") {
        double ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        // CAPTURE(ideal_mass);

        SUBCASE("got body mass") { 
            CHECK(ideal_mass == doctest::Approx(80.51).epsilon(0.01)); 
        }
    }
}


TEST_CASE("get Mass right from CreatureCreator with max values") {
    gameentity::CreatureEntityCreator creaturecreator;

    // bodysize
    // double min_bodysize = 8.4f;
    //double max_bodysize = 20.4;
    double bodysize = 20.4;

    // body weight
    double min_weight = 16;
    //double max_weight = 320;
    double weight = 320;

    // bmi
    double min_bmi = 10;
    double max_bmi = 40;
    double ideal_bmi = 22;

    SUBCASE("get body mass") {
        double ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        // CAPTURE(ideal_mass);

        SUBCASE("got body mass") { 
            CHECK(ideal_mass >= 0.01); 
        }
    }
}

TEST_CASE("get Mass right from CreatureCreator with very min values") {
    gameentity::CreatureEntityCreator creaturecreator;

    // bodysize
    // double min_bodysize = 0.21f;
    //double max_bodysize = 0.51;
    double bodysize = 0.21;

    // body weight
    double min_weight = 2;
    //double max_weight = 40;
    double weight = 2;

    // bmi
    double min_bmi = 10;
    double max_bmi = 40;
    double ideal_bmi = 22;

    SUBCASE("get body mass") {
        double ideal_mass = creaturecreator.getBodyMass(
            bodysize, weight, min_weight, ideal_bmi, min_bmi, max_bmi);

        // CAPTURE(ideal_mass);

        SUBCASE("got body mass") { 
            CHECK(ideal_mass <= 100); 
        }
    }
}