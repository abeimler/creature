#include "doctest.h"

#include "Entity/Game/CreatureBattlerCreator.h"

#include "Entity/Game/EntityGameTestHelper.h"


TEST_CASE("Generate Attributes with Simples values") {
    gameentity::CreatureBattlerCreator creaturebattler_creator;

    int minlvl = 1;
    int maxlvl = 100;
    int basic = 100;
    int inf = 30;
    int boni_inf = 0;
    float boni_factor = 1.0f;

    REQUIRE(minlvl >= 0);
    REQUIRE(maxlvl >= 0);

    std::vector<int> attrs = creaturebattler_creator.genAttrs<int>(
        minlvl, maxlvl, basic, inf, boni_inf, boni_factor);

    SUBCASE("Attibutes has right size, minlevel") {
        CHECK(attrs.size() >= static_cast<size_t>(minlvl));
    }

    SUBCASE("Attibutes has right size, maxlevel") {
        CHECK(attrs.size() >= static_cast<size_t>(maxlvl));
    }


    SUBCASE("Attibutes has right basic value, minlevel") {
        CHECK(attrs[static_cast<size_t>(minlvl)] >= basic);
    }

    SUBCASE("Attibutes has right basic value, maxlevel") {
        CHECK(attrs[static_cast<size_t>(maxlvl)] >= basic);
    }
}


TEST_CASE("Generate Attributes with Big values") {
    gameentity::CreatureBattlerCreator creaturebattler_creator;

    int minlvl = 1;
    int maxlvl = 255;
    int basic = 1000;
    int inf = 50;
    int boni_inf = 10;
    float boni_factor = 5.0f;

    REQUIRE(minlvl >= 0);
    REQUIRE(maxlvl >= 0);

    std::vector<int> attrs = creaturebattler_creator.genAttrs<int>(
        minlvl, maxlvl, basic, inf, boni_inf, boni_factor);

    SUBCASE("Attibutes has right size, minlevel") {
        CHECK(attrs.size() >= static_cast<size_t>(minlvl));
    }

    SUBCASE("Attibutes has right size, maxlevel") {
        CHECK(attrs.size() >= static_cast<size_t>(maxlvl));
    }


    SUBCASE("Attibutes has right basic value, minlevel") {
        CHECK(attrs[static_cast<size_t>(minlvl)] >= basic);
    }

    SUBCASE("Attibutes has right basic value, maxlevel") {
        CHECK(attrs[static_cast<size_t>(maxlvl)] >= basic);
    }

    SUBCASE("Attibutes has no overflow") {
        CHECK_FALSE(attrs[static_cast<size_t>(maxlvl)] < 0);
    }
}


TEST_CASE("create empty CreatureBattler") {
    gameentity::CreatureBattlerCreator creaturebattler_creator;

    auto creaturebattler =
        creaturebattler_creator.createCreatureBattler();

    SUBCASE("CreatureBattler Base MaxHP Attribute wurde mit 0 gesetzt") {
        CHECK(0 == earr::enum_array_at(creaturebattler.attrbase,
                                   +data::Attribute::MaxHP));
    }

    SUBCASE("CreatureBattler Base Exp Attribute wurde mit 0 gesetzt") {
        CHECK(0 == earr::enum_array_at(creaturebattler.attrbase,
                                   +data::Attribute::Exp));
    }


    SUBCASE("CreatureBattler Plus MaxHP Attribute wurde mit 0 gesetzt") {
        CHECK(0 == earr::enum_array_at(creaturebattler.attrplus,
                                   +data::Attribute::MaxHP));
    }

    SUBCASE("CreatureBattler Plus Exp Attribute wurde mit 0 gesetzt") {
        CHECK(0 == earr::enum_array_at(creaturebattler.attrplus,
                                   +data::Attribute::Exp));
    }
}



TEST_CASE("create BattlerBattleState with DataCreature") {
    gameentity::CreatureBattlerCreator creaturebattler_creator;

    auto creature = CreatureTestData::make_DataCreature();

    auto creature_data =
        creaturebattler_creator.createCreatureData(creature);
    auto creaturebattlestate =
        creaturebattler_creator.createBattlerBattleState(creature);

    SUBCASE("CreatureBattler has options of Creature") {
        CHECK(creature.getOption() == creaturebattlestate.option);
    }
}




TEST_CASE("create BattlerResists with DataCreature") {
    gameentity::CreatureBattlerCreator creaturebattler_creator;

    auto creature = CreatureTestData::make_DataCreature();

    auto creature_data =
        creaturebattler_creator.createCreatureData(creature);
    auto battlerresists =
        creaturebattler_creator.createBattlerResists(creature);

    SUBCASE("CreatureBattler has right elements (size)") {
        CHECK(creature.getElements() == battlerresists.atk_elements_name);
    }

    SUBCASE("CreatureBattler has right elements resists (size)") {
        CHECK(creature.getElementResist().size() ==
                battlerresists.elementresist.size());
    }

    SUBCASE("CreatureBattler has right status resists (size)") {
        CHECK(creature.getStatusResist().size() ==
                battlerresists.statusresist.size());
    }
}




TEST_CASE("create and load CreatureBattler with start Level") {
    gameentity::CreatureBattlerCreator creaturebattler_creator;
    auto creature = CreatureTestData::make_DataCreature();
    auto gene = EntityGameTestHelper::make_CreatureBattlerGene_withValues();

    int lvl = creature.getStartLvL();

    auto creature_data =
        creaturebattler_creator.createCreatureData(creature);
    auto creaturebattler =
        creaturebattler_creator.createCreatureBattler();

    creaturebattler_creator.loadCreatureBattler(creaturebattler, creature, gene, lvl);

    SUBCASE("CreatureBattler minimal level") {
        CHECK(creaturebattler.lvl >= creature.getMinLvL());
    }
    SUBCASE("CreatureBattler has right Level (Start Level)") {
        CHECK(creaturebattler.lvl == lvl);
    }
    SUBCASE("CreatureBattler maximal level") {
        CHECK(creaturebattler.lvl <= creature.getMaxLvL());
    }

    SUBCASE("CreatureBattler has no exp (Start Level)") {
        CHECK(creaturebattler.exp == 0);
    }


    SUBCASE("CreatureBattler has right base Attribute, front") {
        data::Attribute index = data::Attribute::MaxHP;
        CHECK(earr::enum_array_at(creaturebattler.attrbase, index) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right Attribute, front") {
        data::Attribute index = data::Attribute::MaxHP;
        CHECK(earr::enum_array_at(creaturebattler.attr, index) >=
                creature.getAttrBasis(index));
    }


    SUBCASE("CreatureBattler has right base Attribute, back") {
        data::Attribute index = data::Attribute::Exp;
        CHECK(earr::enum_array_at(creaturebattler.attrbase, index) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right Attribute, back") {
        data::Attribute index = data::Attribute::Exp;
        CHECK(earr::enum_array_at(creaturebattler.attr, index) >=
                creature.getAttrBasis(index));
    }



    SUBCASE("CreatureBattler has right Attribute, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMinLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index)
                    .at(static_cast<size_t>(creature.getMinLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right Attribute, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMaxLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index)
                    .at(static_cast<size_t>(creature.getMaxLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("Attibutes has right size, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMinLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index).size() >=
                static_cast<size_t>(creature.getMinLvL()));
    }

    SUBCASE("Attibutes has right size, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMaxLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index).size() >=
                static_cast<size_t>(creature.getMaxLvL()));
    }
}



TEST_CASE("create and load CreatureBattler with Level 5") {
    gameentity::CreatureBattlerCreator creaturebattler_creator;
    auto creature = CreatureTestData::make_DataCreature();
    auto gene = EntityGameTestHelper::make_CreatureBattlerGene_withValues();

    int lvl = 5;

    auto creature_data =
        creaturebattler_creator.createCreatureData(creature);
    auto creaturebattler =
        creaturebattler_creator.createCreatureBattler();

    creaturebattler_creator.loadCreatureBattler(creaturebattler, creature, gene, lvl);

    SUBCASE("CreatureBattler minimal level") {
        CHECK(creaturebattler.lvl >= creature.getMinLvL());
    }
    SUBCASE("CreatureBattler has right Level") {
        CHECK(lvl == creaturebattler.lvl);
    }
    SUBCASE("CreatureBattler maximal level") {
        CHECK(creaturebattler.lvl <= creature.getMaxLvL());
    }

    SUBCASE("CreatureBattler has same exp") {
        CHECK(creaturebattler.exp >= 0);
    }


    SUBCASE("CreatureBattler has right base Attribute, front") {
        data::Attribute index = data::Attribute::MaxHP;
        CHECK(earr::enum_array_at(creaturebattler.attrbase, index) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right base Attribute, back") {
        data::Attribute index = data::Attribute::Exp;
        CHECK(earr::enum_array_at(creaturebattler.attrbase, index) >=
                creature.getAttrBasis(index));
    }



    SUBCASE("CreatureBattler has right Attribute, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMinLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index)
                    .at(static_cast<size_t>(creature.getMinLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right Attribute, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMaxLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index)
                    .at(static_cast<size_t>(creature.getMaxLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("Attibutes has right size, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMinLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index).size() >=
                static_cast<size_t>(creature.getMinLvL()));
    }

    SUBCASE("Attibutes has right size, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMaxLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index).size() >=
                static_cast<size_t>(creature.getMaxLvL()));
    }
}


TEST_CASE("load CreatureBattler with Max Level") {
    gameentity::CreatureBattlerCreator creaturebattler_creator;
    auto creature = CreatureTestData::make_DataCreature();
    auto gene = EntityGameTestHelper::make_CreatureBattlerGene_withValues();

    int lvl = creature.getMaxLvL();

    auto creature_data = creaturebattler_creator.createCreatureData(creature);
    auto creaturebattler = creaturebattler_creator.createCreatureBattler();
    creaturebattler_creator.loadCreatureBattler(creaturebattler, creature, gene, lvl);

    SUBCASE("CreatureBattler minimal level") {
        CHECK(creaturebattler.lvl >= creature.getMinLvL());
    }
    SUBCASE("CreatureBattler has right Level") {
        CHECK(lvl == creaturebattler.lvl);
    }
    SUBCASE("CreatureBattler maximal level") {
        CHECK(creaturebattler.lvl <= creature.getMaxLvL());
    }

    SUBCASE("CreatureBattler has same exp") {
        CHECK(creaturebattler.exp >= 0);
    }


    SUBCASE("CreatureBattler has right base Attribute, front") {
        data::Attribute index = data::Attribute::MaxHP;
        CHECK(earr::enum_array_at(creaturebattler.attrbase, index) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right base Attribute, back") {
        data::Attribute index = data::Attribute::Exp;
        CHECK(earr::enum_array_at(creaturebattler.attrbase, index) >=
                creature.getAttrBasis(index));
    }



    SUBCASE("CreatureBattler has right Attribute, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMinLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index)
                    .at(static_cast<size_t>(creature.getMinLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right Attribute, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMaxLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index)
                    .at(static_cast<size_t>(creature.getMaxLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("Attibutes has right size, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMinLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index).size() >=
                static_cast<size_t>(creature.getMinLvL()));
    }

    SUBCASE("Attibutes has right size, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMaxLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index).size() >=
                static_cast<size_t>(creature.getMaxLvL()));
    }
}



TEST_CASE("create load and transform CreatureBattler with Level 5") {
    gameentity::CreatureBattlerCreator creaturebattler_creator;
    auto creature = CreatureTestData::make_DataCreature();
    auto gene = EntityGameTestHelper::make_CreatureBattlerGene_withValues();

    int lvl = 5;

    auto creature_data = creaturebattler_creator.createCreatureData(creature);
    auto creaturebattler = creaturebattler_creator.createCreatureBattler();
    creaturebattler_creator.loadCreatureBattler(creaturebattler, creature, gene, lvl);

    creaturebattler_creator.transformCreatureBattler(creaturebattler, creature, gene);

    SUBCASE("CreatureBattler minimal level") {
        CHECK(creaturebattler.lvl >= creature.getMinLvL());
    }
    SUBCASE("after transform CreatureBattler level is the same") {
        CHECK(lvl == creaturebattler.lvl);
    }
    SUBCASE("CreatureBattler maximal level") {
        CHECK(creaturebattler.lvl <= creature.getMaxLvL());
    }

    SUBCASE("CreatureBattler has same exp") {
        CHECK(creaturebattler.exp >= 0);
    }


    SUBCASE("CreatureBattler has right base Attribute, front") {
        data::Attribute index = data::Attribute::MaxHP;
        CHECK(earr::enum_array_at(creaturebattler.attrbase, index) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right base Attribute, back") {
        data::Attribute index = data::Attribute::Exp;
        CHECK(earr::enum_array_at(creaturebattler.attrbase, index) >=
                creature.getAttrBasis(index));
    }



    SUBCASE("CreatureBattler has right Attribute, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMinLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index)
                    .at(static_cast<size_t>(creature.getMinLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right Attribute, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMaxLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index)
                    .at(static_cast<size_t>(creature.getMaxLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("Attibutes has right size, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMinLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index).size() >=
                static_cast<size_t>(creature.getMinLvL()));
    }

    SUBCASE("Attibutes has right size, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMaxLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index).size() >=
                static_cast<size_t>(creature.getMaxLvL()));
    }
}



TEST_CASE("create load and (re)load again CreatureBattler with Level 5") {
    gameentity::CreatureBattlerCreator creaturebattler_creator;
    auto creature = CreatureTestData::make_DataCreature();
    auto gene = EntityGameTestHelper::make_CreatureBattlerGene_withValues();

    int start_lvl = creature.getStartLvL();
    int lvl = 5;


    auto creature_data = creaturebattler_creator.createCreatureData(creature);
    auto creaturebattler = creaturebattler_creator.createCreatureBattler();
    creaturebattler_creator.loadCreatureBattler(creaturebattler, creature, gene,
                                                start_lvl);

    creaturebattler_creator.loadCreatureBattler(creaturebattler, creature, gene, lvl);

    SUBCASE("CreatureBattler minimal level") {
        CHECK(creaturebattler.lvl >= creature.getMinLvL());
    }
    SUBCASE("CreatureBattler has right Level") {
        CHECK(lvl == creaturebattler.lvl);
    }
    SUBCASE("after reload CreatureBattler level is not the same") {
        REQUIRE(start_lvl != creaturebattler.lvl);
    }
    SUBCASE("CreatureBattler maximal level") {
        CHECK(creaturebattler.lvl <= creature.getMaxLvL());
    }

    SUBCASE("CreatureBattler has same exp") {
        CHECK(creaturebattler.exp >= 0);
    }


    SUBCASE("CreatureBattler has right base Attribute, front") {
        data::Attribute index = data::Attribute::MaxHP;
        CHECK(earr::enum_array_at(creaturebattler.attrbase, index) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right base Attribute, back") {
        data::Attribute index = data::Attribute::Exp;
        CHECK(earr::enum_array_at(creaturebattler.attrbase, index) >=
                creature.getAttrBasis(index));
    }



    SUBCASE("CreatureBattler has right Attribute, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMinLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index)
                    .at(static_cast<size_t>(creature.getMinLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("CreatureBattler has right Attribute, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMaxLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index)
                    .at(static_cast<size_t>(creature.getMaxLvL())) >=
                creature.getAttrBasis(index));
    }

    SUBCASE("Attibutes has right size, minlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMinLvL() >= 0);
        CHECK(earr::enum_array_at(creaturebattler.attrparam, index).size() >=
                static_cast<size_t>(creature.getMinLvL()));
    }

    SUBCASE("Attibutes has right size, maxlevel") {
        data::Attribute index = data::Attribute::MaxHP;
        REQUIRE(creature.getMaxLvL() >= 0);
        REQUIRE(earr::enum_array_at(creaturebattler.attrparam, index).size() >=
                static_cast<size_t>(creature.getMaxLvL()));
    }
}
