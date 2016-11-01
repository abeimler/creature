#include "Entity/Game/CreatureTestData.h"


constexpr int CreatureTest::MAXHP;
constexpr int CreatureTest::MAXMP;
constexpr int CreatureTest::ATK;
constexpr int CreatureTest::DEF;
constexpr int CreatureTest::AGI;
constexpr int CreatureTest::INT;
constexpr int CreatureTest::EXP;

constexpr int CreatureTest::ATTR_INFLATION;


constexpr int CreatureTest::STARTLEVEL;
constexpr int CreatureTest::MINLEVEL;
constexpr int CreatureTest::MAXLEVEL;
constexpr int CreatureTest::LVL;

constexpr int CreatureTest::HITRATE;
constexpr int CreatureTest::HITRATE_HALF;
constexpr int CreatureTest::CRITICAL_HITRATE;
constexpr int CreatureTest::EVARATE;


constexpr double CreatureTest::MIN_WEIGHT;
constexpr double CreatureTest::MAX_WEIGHT;

constexpr double CreatureTest::MIN_BODYSIZE;
constexpr double CreatureTest::MAX_BODYSIZE;

constexpr data::CreatureLevel CreatureTest::CREATURELEVEL;
constexpr data::CreatureLevel CreatureTest::OTHERCREATURELEVEL;

constexpr data::CreatureGender CreatureTest::GENDER;

constexpr double CreatureTest::MIN_BMI;
constexpr double CreatureTest::IDEAL_BMI;
constexpr double CreatureTest::MAX_BMI;
constexpr double CreatureTest::MAX_BODYSIZE_GENE;
constexpr double CreatureTest::BODYMASS;


constexpr double CreatureTest::BMI;
constexpr double CreatureTest::BODYSIZE;
constexpr double CreatureTest::WEIGHT;
constexpr double CreatureTest::LOWER_WEIGHT;
constexpr double CreatureTest::HIGHER_WEIGHT;
constexpr int CreatureTest::CALORIES;
constexpr int CreatureTest::HIGHCALORIES;

constexpr int CreatureTest::CANGOSLEEP_AT_TIRED;

constexpr size_t CreatureTest::MAX_DIGESTIONHEAP;

constexpr int CreatureTest::NEEDSLEEPINPERCENT;
constexpr int CreatureTest::NEEDRESTINHOSPITALINPERCENT;

constexpr std::chrono::seconds CreatureTest::TOTALMAXLIFETIME;
constexpr std::chrono::seconds CreatureTest::LIFETIME;
constexpr std::chrono::seconds CreatureTest::AGEINGTIME;
constexpr int CreatureTest::AGE;

constexpr std::chrono::milliseconds CreatureTest::GOOD_TRAINTIME;
constexpr std::chrono::milliseconds CreatureTest::MIDDLE_TRAINTIME;
constexpr std::chrono::milliseconds CreatureTest::MIN_TRAINTIME;

constexpr const char* CreatureTest::CREATURENAME;

constexpr data::CreatureTrainTime CreatureTest::CREATURETRAINTIME;

constexpr double CreatureTest::MAX_HUNGRYOVERLAY_INTRAINING;
constexpr double CreatureTest::MAX_THIRSTYOVERLAY_INTRAINING;
constexpr double CreatureTest::MAX_TIREDOVERLAY_INTRAINING;

constexpr size_t CreatureTest::MAX_SHORTMEMORY_SIZE;

std::chrono::system_clock::time_point CreatureTest::make_time_point_01_01_2000() {
    // create tm with 1/1/2000:
    std::tm timeinfo = std::tm();
    timeinfo.tm_year = 100; // year: 2000
    timeinfo.tm_mon = 0;    // month: january
    timeinfo.tm_mday = 1;   // day: 1st
    std::time_t tt = std::mktime(&timeinfo);

    return std::chrono::system_clock::from_time_t(tt);
}

data::Creature CreatureTest::make_DataCreature() {
    data::Creature creature;

    creature.setName(CREATURENAME);
    creature.setCreatureLevel(CREATURELEVEL);


    creature.setMinWeight(MIN_WEIGHT);
    creature.setMaxWeight(MAX_WEIGHT);
    creature.setBodySizeMin(MIN_BODYSIZE);
    creature.setBodySizeMax(MAX_BODYSIZE);


    creature.setStartLvL(STARTLEVEL);
    creature.setMinLvL(MINLEVEL);
    creature.setMaxLvL(MAXLEVEL);

    creature.setHitRate(HITRATE);
    creature.setCriticalHitRate(CRITICAL_HITRATE);
    creature.setEvaRate(EVARATE);


    creature.setAttrBasis(data::Attribute::MaxHP, MAXHP);
    creature.setAttrBasis(data::Attribute::MaxMP, MAXMP);
    creature.setAttrBasis(data::Attribute::Atk, ATK);
    creature.setAttrBasis(data::Attribute::Def, DEF);
    creature.setAttrBasis(data::Attribute::Agi, AGI);
    creature.setAttrBasis(data::Attribute::Int, INT);
    creature.setAttrBasis(data::Attribute::Exp, EXP);

    creature.setAttrInflation(data::Attribute::MaxHP,
                               ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::MaxMP,
                               ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::Atk,
                               ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::Def,
                               ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::Agi,
                               ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::Int,
                               ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::Exp,
                               ATTR_INFLATION);

    return creature;
}
