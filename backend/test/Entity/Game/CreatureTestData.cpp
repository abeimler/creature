#include "Entity/Game/CreatureTestData.h"


constexpr int CreatureTestData::MAXHP;
constexpr int CreatureTestData::MAXMP;
constexpr int CreatureTestData::ATK;
constexpr int CreatureTestData::DEF;
constexpr int CreatureTestData::AGI;
constexpr int CreatureTestData::INT;
constexpr int CreatureTestData::EXP;

constexpr int CreatureTestData::ATTR_INFLATION;


constexpr int CreatureTestData::STARTLEVEL;
constexpr int CreatureTestData::MINLEVEL;
constexpr int CreatureTestData::MAXLEVEL;
constexpr int CreatureTestData::LVL;

constexpr int CreatureTestData::HITRATE;
constexpr int CreatureTestData::HITRATE_HALF;
constexpr int CreatureTestData::CRITICAL_HITRATE;
constexpr int CreatureTestData::EVARATE;


constexpr double CreatureTestData::MIN_WEIGHT;
constexpr double CreatureTestData::MAX_WEIGHT;

constexpr double CreatureTestData::MIN_BODYSIZE;
constexpr double CreatureTestData::MAX_BODYSIZE;

constexpr data::CreatureLevel CreatureTestData::CREATURELEVEL;
constexpr data::CreatureLevel CreatureTestData::OTHERCREATURELEVEL;

constexpr data::CreatureGender CreatureTestData::GENDER;

constexpr double CreatureTestData::MIN_BMI;
constexpr double CreatureTestData::IDEAL_BMI;
constexpr double CreatureTestData::MAX_BMI;
constexpr double CreatureTestData::MAX_BODYSIZE_GENE;
constexpr double CreatureTestData::BODYMASS;


constexpr double CreatureTestData::BMI;
constexpr double CreatureTestData::BODYSIZE;
constexpr double CreatureTestData::WEIGHT;
constexpr double CreatureTestData::LOWER_WEIGHT;
constexpr double CreatureTestData::HIGHER_WEIGHT;
constexpr int CreatureTestData::CALORIES;
constexpr int CreatureTestData::HIGHCALORIES;

constexpr int CreatureTestData::CANGOSLEEP_AT_TIRED;

constexpr size_t CreatureTestData::MAX_DIGESTIONHEAP;

constexpr int CreatureTestData::NEEDSLEEPINPERCENT;
constexpr int CreatureTestData::NEEDRESTINHOSPITALINPERCENT;

constexpr std::chrono::seconds CreatureTestData::TOTALMAXLIFETIME;
constexpr std::chrono::seconds CreatureTestData::LIFETIME;
constexpr std::chrono::seconds CreatureTestData::AGEINGTIME;
constexpr int CreatureTestData::AGE;

constexpr std::chrono::milliseconds CreatureTestData::GOOD_TRAINTIME;
constexpr std::chrono::milliseconds CreatureTestData::MIDDLE_TRAINTIME;
constexpr std::chrono::milliseconds CreatureTestData::MIN_TRAINTIME;

constexpr const char* CreatureTestData::CREATURENAME;

constexpr data::CreatureTrainTime CreatureTestData::CREATURETRAINTIME;

constexpr double CreatureTestData::MAX_HUNGRYOVERLAY_INTRAINING;
constexpr double CreatureTestData::MAX_THIRSTYOVERLAY_INTRAINING;
constexpr double CreatureTestData::MAX_TIREDOVERLAY_INTRAINING;

constexpr size_t CreatureTestData::MAX_SHORTMEMORY_SIZE;

std::chrono::system_clock::time_point
CreatureTestData::make_time_point_01_01_2000() {
    // create tm with 1/1/2000:
    std::tm timeinfo = std::tm();
    timeinfo.tm_year = 100; // year: 2000
    timeinfo.tm_mon = 0;    // month: january
    timeinfo.tm_mday = 1;   // day: 1st
    std::time_t tt = std::mktime(&timeinfo);

    return std::chrono::system_clock::from_time_t(tt);
}

data::Creature CreatureTestData::make_DataCreature() {
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

    creature.setAttrInflation(data::Attribute::MaxHP, ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::MaxMP, ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::Atk, ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::Def, ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::Agi, ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::Int, ATTR_INFLATION);
    creature.setAttrInflation(data::Attribute::Exp, ATTR_INFLATION);

    return creature;
}
