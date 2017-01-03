#include <cereal/archives/json.hpp>
#include <fstream>
#include <json.hpp>

#include "doctest.h"

#include "Data/Battler.h"


class LearnSkillTest {
    public:
    static const std::string SKILL_NAME;
    static const int LVL;

    static void init_minimal_Skill(data::Skill& skill) {
        skill.setName(SKILL_NAME);
    }

    static void init_LearnSkill(data::LearnSkill& learnskill) {
        learnskill.setLvL(LVL);

        data::Skill skill;
        init_minimal_Skill(skill);
        learnskill.setSkill(skill);
    }
};
const std::string LearnSkillTest::SKILL_NAME = "Fire";
const int LearnSkillTest::LVL = 5;



class BattlerTest {
    public:
    static const std::string NAME;

    static const int ATTR_BASE_MAXHP;
    static const int ATTR_BASE_MAXMP;
    static const int ATTR_BASE_ATK;
    static const int ATTR_BASE_DEF;
    static const int ATTR_BASE_INT;
    static const int ATTR_BASE_AGI;
    static const int ATTR_BASE_EXP;

    static const int ATTR_INF_MAXHP;
    static const int ATTR_INF_MAXMP;
    static const int ATTR_INF_ATK;
    static const int ATTR_INF_DEF;
    static const int ATTR_INF_INT;
    static const int ATTR_INF_AGI;
    static const int ATTR_INF_EXP;

    static const int START_LVL;
    static const int MIN_LVL;
    static const int MAX_LVL;

    static const std::string STATUSRESIST_NAME;
    static const std::string ELEMENTRESIST_NAME;
    static const data::Resist STATUSRESIST_RESIST;
    static const data::Resist ELEMENTRESIST_RESIST;

    static const int HITRATE;
    static const int CRITICAL_HITRATE;
    static const int EVARATE;

    static void init_minimal_BattlerStatus(data::BattlerStatus& battlerstatus) {
        battlerstatus.setName(STATUSRESIST_NAME);
    }

    static void init_minimal_Element(data::Element& element) {
        element.setName(ELEMENTRESIST_NAME);
    }

    static void init_Battler(data::Battler& battler) {
        data::LearnSkill learnskill;
        LearnSkillTest::init_LearnSkill(learnskill);
        std::vector<data::LearnSkill> skills = {learnskill};

        battler.setSkills(skills);

        battler.setAttrBasis(data::Attribute::MaxHP, ATTR_BASE_MAXHP);
        battler.setAttrBasis(data::Attribute::MaxMP, ATTR_BASE_MAXMP);
        battler.setAttrBasis(data::Attribute::Atk, ATTR_BASE_ATK);
        battler.setAttrBasis(data::Attribute::Def, ATTR_BASE_DEF);
        battler.setAttrBasis(data::Attribute::Int, ATTR_BASE_INT);
        battler.setAttrBasis(data::Attribute::Agi, ATTR_BASE_AGI);
        battler.setAttrBasis(data::Attribute::Exp, ATTR_BASE_EXP);

        battler.setAttrInflation(data::Attribute::MaxHP, ATTR_INF_MAXHP);
        battler.setAttrInflation(data::Attribute::MaxMP, ATTR_INF_MAXMP);
        battler.setAttrInflation(data::Attribute::Atk, ATTR_INF_ATK);
        battler.setAttrInflation(data::Attribute::Def, ATTR_INF_DEF);
        battler.setAttrInflation(data::Attribute::Int, ATTR_INF_INT);
        battler.setAttrInflation(data::Attribute::Agi, ATTR_INF_AGI);
        battler.setAttrInflation(data::Attribute::Exp, ATTR_INF_EXP);

        battler.setStartLvL(START_LVL);
        battler.setMinLvL(MIN_LVL);
        battler.setMaxLvL(MAX_LVL);

        data::BattlerStatus battlerstatus;
        init_minimal_BattlerStatus(battlerstatus);

        data::Element element;
        init_minimal_Element(element);

        battler.setStatusResist(battlerstatus, STATUSRESIST_RESIST);
        battler.setElementResist(element, STATUSRESIST_RESIST);

        battler.setName(NAME);

        battler.setHitRate(HITRATE);
        battler.setCriticalHitRate(CRITICAL_HITRATE);
        battler.setEvaRate(EVARATE);
    }
};
const std::string BattlerTest::NAME = "DummyBattler";

const int BattlerTest::ATTR_BASE_MAXHP = 24;
const int BattlerTest::ATTR_BASE_MAXMP = 32;
const int BattlerTest::ATTR_BASE_ATK = 12;
const int BattlerTest::ATTR_BASE_DEF = 13;
const int BattlerTest::ATTR_BASE_INT = 18;
const int BattlerTest::ATTR_BASE_AGI = 12;
const int BattlerTest::ATTR_BASE_EXP = 42;

const int BattlerTest::ATTR_INF_MAXHP = 9;
const int BattlerTest::ATTR_INF_MAXMP = 10;
const int BattlerTest::ATTR_INF_ATK = 8;
const int BattlerTest::ATTR_INF_DEF = 9;
const int BattlerTest::ATTR_INF_INT = 11;
const int BattlerTest::ATTR_INF_AGI = 9;
const int BattlerTest::ATTR_INF_EXP = 24;

const int BattlerTest::START_LVL = 1;
const int BattlerTest::MIN_LVL = 1;
const int BattlerTest::MAX_LVL = 100;

const std::string BattlerTest::STATUSRESIST_NAME = "Poisen";
const std::string BattlerTest::ELEMENTRESIST_NAME = "Fire";
const data::Resist BattlerTest::STATUSRESIST_RESIST = data::Resist::Normal;
const data::Resist BattlerTest::ELEMENTRESIST_RESIST = data::Resist::Normal;

const int BattlerTest::HITRATE = 90;
const int BattlerTest::CRITICAL_HITRATE = 30;
const int BattlerTest::EVARATE = 20;



TEST_CASE("data::LearnSkill serial json") {
    data::LearnSkill data;

    LearnSkillTest::init_LearnSkill(data);

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


TEST_CASE("data::Battler serial json") {
    data::Battler data;

    BattlerTest::init_Battler(data);

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



TEST_CASE("data::Battler serial json as file") {
    data::Battler data;

    BattlerTest::init_Battler(data);

    SUBCASE("serial json") {
        std::ofstream os("battler.json");
        {
            cereal::JSONOutputArchive outar(os);

            CHECK_NOTHROW(outar(cereal::make_nvp("data", data)));
        }
    }
}