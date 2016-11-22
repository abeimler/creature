#ifndef ENTITY_GAME_CreatureTestDataDATA_H_
#define ENTITY_GAME_CreatureTestDataDATA_H_

#include "Entity/Game/CreatureEntityCreator.h"


class CreatureTestData {
    public:

    // Attributes
    const int MAXHP = 123;
    const int MAXMP = 96;
    const int ATK = 32;
    const int DEF = 26;
    const int AGI = 18;
    const int INT = 11;
    const int EXP = 88;

    const int ATTR_INFLATION = 12;


    const int STARTLEVEL = 1;
    const int MINLEVEL = 1;
    const int MAXLEVEL = 5;
    const int LVL = 1;
    
    
    const int HITRATE = 90;
    const int HITRATE_HALF = 45;
    const int CRITICAL_HITRATE = 30;
    const int CRITICAL_HITRATE_HALF = 15;
    const int EVARATE = 30;

    const data::CreatureLevel CREATURELEVEL = data::CreatureLevel::Child;
    const data::CreatureLevel OTHERCREATURELEVEL = data::CreatureLevel::Perfect;

    const data::CreatureGender GENDER = data::CreatureGender::Male;


    const double WEIGHT = 10;
    const double MIN_WEIGHT = 4;
    const double MAX_WEIGHT = 80;

    const double BODYSIZE = 1.2;
    const double MIN_BODYSIZE = 1.0;
    const double MAX_BODYSIZE = 1.8;

    const double MIN_BMI = 10;
    const double IDEAL_BMI = 22;
    const double MAX_BMI = 40;
    const double MAX_BODYSIZE_GENE = 1.6;


    const double BMI = 20;
    const double BODYMASS = 32; // see CreatureCreator::getBodyMass for formula

    const double LOWER_WEIGHT = 5;
    const double HIGHER_WEIGHT = 50;
    const int CALORIES = 2000;
    const int HIGHCALORIES = 5000;

    const int CANGOSLEEP_AT_TIRED = 88;

    const size_t MAX_DIGESTIONHEAP = 3;

    const int NEEDSLEEPINPERCENT = 70;
    const int NEEDRESTINHOSPITALINPERCENT = 100;

    const std::chrono::seconds TOTALMAXLIFETIME = std::chrono::hours(100);
    const std::chrono::seconds LIFETIME = std::chrono::hours(10);
    const std::chrono::seconds AGEINGTIME = std::chrono::hours(1);
    const int AGE = 10;

    const std::chrono::milliseconds GOOD_TRAINTIME = std::chrono::milliseconds(10);
    const std::chrono::milliseconds MIDDLE_TRAINTIME = std::chrono::milliseconds(5);
    const std::chrono::milliseconds MIN_TRAINTIME = std::chrono::milliseconds(3);

    const char* CREATURENAME = "Testmon";

    const data::CreatureTrainTime CREATURETRAINTIME = data::CreatureTrainTime::Noon;

    const double MAX_HUNGRYOVERLAY_INTRAINING = 30;
    const double MAX_THIRSTYOVERLAY_INTRAINING = 30;
    const double MAX_TIREDOVERLAY_INTRAINING = 30;

    const size_t MAX_SHORTMEMORY_SIZE = 7;

    
    std::chrono::system_clock::time_point
    make_time_point_01_01_2000() {
        // create tm with 1/1/2000:
        std::tm timeinfo = std::tm();
        timeinfo.tm_year = 100; // year: 2000
        timeinfo.tm_mon = 0;    // month: january
        timeinfo.tm_mday = 1;   // day: 1st
        std::time_t tt = std::mktime(&timeinfo);

        return std::chrono::system_clock::from_time_t(tt);
    }

    data::Creature make_DataCreature() {
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

};


#endif // ENTITY_GAME_CreatureTestDataDATA_H_
