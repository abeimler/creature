#ifndef ENTITY_GAME_CreatureTestDataDATA_H_
#define ENTITY_GAME_CreatureTestDataDATA_H_

#include "Entity/Game/CreatureEntityCreator.h"


class CreatureTestData {
    public:

    // Attributes
    static constexpr int MAXHP = 123;
    static constexpr int MAXMP = 96;
    static constexpr int ATK = 32;
    static constexpr int DEF = 26;
    static constexpr int AGI = 18;
    static constexpr int INT = 11;
    static constexpr int EXP = 88;

    static constexpr int ATTR_INFLATION = 12;


    static constexpr int STARTLEVEL = 1;
    static constexpr int MINLEVEL = 1;
    static constexpr int MAXLEVEL = 5;
    static constexpr int LVL = 1;
    
    
    static constexpr int HITRATE = 90;
    static constexpr int HITRATE_HALF = 45;
    static constexpr int CRITICAL_HITRATE = 30;
    static constexpr int CRITICAL_HITRATE_HALF = 15;
    static constexpr int EVARATE = 30;

    static constexpr data::CreatureLevel CREATURELEVEL = data::CreatureLevel::Child;
    static constexpr data::CreatureLevel OTHERCREATURELEVEL = data::CreatureLevel::Perfect;

    static constexpr data::CreatureGender GENDER = data::CreatureGender::Male;


    static constexpr double WEIGHT = 10;
    static constexpr double MIN_WEIGHT = 4;
    static constexpr double MAX_WEIGHT = 80;

    static constexpr double BODYSIZE = 1.2;
    static constexpr double MIN_BODYSIZE = 1.0;
    static constexpr double MAX_BODYSIZE = 1.8;

    static constexpr double MIN_BMI = 10;
    static constexpr double IDEAL_BMI = 22;
    static constexpr double MAX_BMI = 40;
    static constexpr double MAX_BODYSIZE_GENE = 1.6;


    static constexpr double BMI = 20;
    static constexpr double BODYMASS = 32; // see CreatureCreator::getBodyMass for formula

    static constexpr double LOWER_WEIGHT = 5;
    static constexpr double HIGHER_WEIGHT = 50;
    static constexpr int CALORIES = 2000;
    static constexpr int HIGHCALORIES = 5000;

    static constexpr int CANGOSLEEP_AT_TIRED = 88;

    static constexpr size_t MAX_DIGESTIONHEAP = 3;

    static constexpr int NEEDSLEEPINPERCENT = 70;
    static constexpr int NEEDRESTINHOSPITALINPERCENT = 100;

    static constexpr std::chrono::seconds TOTALMAXLIFETIME = std::chrono::hours(100);
    static constexpr std::chrono::seconds LIFETIME = std::chrono::hours(10);
    static constexpr std::chrono::seconds AGEINGTIME = std::chrono::hours(1);
    static constexpr int AGE = 10;

    static constexpr std::chrono::milliseconds GOOD_TRAINTIME = std::chrono::milliseconds(10);
    static constexpr std::chrono::milliseconds MIDDLE_TRAINTIME = std::chrono::milliseconds(5);
    static constexpr std::chrono::milliseconds MIN_TRAINTIME = std::chrono::milliseconds(3);

    static constexpr const char* CREATURENAME = "Testmon";

    static constexpr data::CreatureTrainTime CREATURETRAINTIME = data::CreatureTrainTime::Noon;

    static constexpr double MAX_HUNGRYOVERLAY_INTRAINING = 30;
    static constexpr double MAX_THIRSTYOVERLAY_INTRAINING = 30;
    static constexpr double MAX_TIREDOVERLAY_INTRAINING = 30;

    static constexpr size_t MAX_SHORTMEMORY_SIZE = 7;

    static std::chrono::system_clock::time_point make_time_point_01_01_2000();
    static data::Creature make_DataCreature();
};


#endif // ENTITY_GAME_CreatureTestDataDATA_H_
