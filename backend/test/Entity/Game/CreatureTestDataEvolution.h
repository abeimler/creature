#ifndef ENTITY_GAME_CREATURETESTDATAEVOLUTION_H_
#define ENTITY_GAME_CREATURETESTDATAEVOLUTION_H_

#include "Entity/Game/CreatureEntityCreator.h"

class CreatureTestEvolutionEgg {
    public:

    // Attributes
    const int MAXHP = 1;
    const int MAXMP = 1;
    const int ATK = 1;
    const int DEF = 1;
    const int AGI = 1;
    const int INT = 1;
    const int EXP = 1;

    const int ATTR_INFLATION = 1;


    const int STARTLEVEL = 1;
    const int MINLEVEL = 1;
    const int MAXLEVEL = 5;
    const int LVL = 1;

    const data::CreatureLevel CREATURELEVEL = data::CreatureLevel::Egg;

    const data::CreatureGender GENDER = data::CreatureGender::Male;


    const float WEIGHT = 5;
    const float MIN_WEIGHT = 2;
    const float MAX_WEIGHT = 40;

    const float BODYSIZE = 0.3f;
    const float MIN_BODYSIZE = 0.21f;
    const float MAX_BODYSIZE = 0.51f;

    const float MIN_BMI = 18;
    const float IDEAL_BMI = 26;
    const float MAX_BMI = 50;
    const float MAX_BODYSIZE_GENE = 0.43f;


    const float BMI = 25;
    const float BODYMASS = 57; // see CreatureCreator::getBodyMass for formula

    const int CALORIES = 2000;

    const int CANGOSLEEP_AT_TIRED = 88;

    const size_t MAX_DIGESTIONHEAP = 3;

    const int NEEDSLEEPINPERCENT = 70;
    const int NEEDRESTINHOSPITALINPERCENT = 100;

    const std::chrono::seconds TOTALMAXLIFETIME = std::chrono::hours(100);
    const std::chrono::seconds LIFETIME = std::chrono::hours(0);
    const std::chrono::seconds AGEINGTIME = std::chrono::hours(1);
    const int AGE = 0;

    const std::chrono::milliseconds GOOD_TRAINTIME = std::chrono::milliseconds(10);
    const std::chrono::milliseconds MIDDLE_TRAINTIME = std::chrono::milliseconds(5);
    const std::chrono::milliseconds MIN_TRAINTIME = std::chrono::milliseconds(3);

    const char* CREATURENAME = "Egg";

    const data::CreatureTrainTime CREATURETRAINTIME = data::CreatureTrainTime::Noon;

    const float MAX_HUNGRYOVERLAY_INTRAINING = 30.0f;
    const float MAX_THIRSTYOVERLAY_INTRAINING = 30.0f;
    const float MAX_TIREDOVERLAY_INTRAINING = 30.0f;

    const size_t MAX_SHORTMEMORY_SIZE = 5;
};

class CreatureTestEvolutionBaby {
    public:

    // Attributes
    const int MAXHP = 20;
    const int MAXMP = 10;
    const int ATK = 6;
    const int DEF = 3;
    const int AGI = 4;
    const int INT = 6;
    const int EXP = 12;

    const int ATTR_INFLATION = 8;


    const int STARTLEVEL = 1;
    const int MINLEVEL = 1;
    const int MAXLEVEL = 5;
    const int LVL = 1;

    const data::CreatureLevel CREATURELEVEL = data::CreatureLevel::Baby;

    const data::CreatureGender GENDER = data::CreatureGender::Male;

    const float WEIGHT = 5;
    const float MIN_WEIGHT = 2;
    const float MAX_WEIGHT = 40;

    const float BODYSIZE = 0.2f;
    const float MIN_BODYSIZE = 0.14f;
    const float MAX_BODYSIZE = 0.34f;

    const float MIN_BMI = 18;
    const float IDEAL_BMI = 26;
    const float MAX_BMI = 50;
    const float MAX_BODYSIZE_GENE = 0.28f;


    const float BMI = 25;
    const float BODYMASS = 57; // see CreatureCreator::getBodyMass for formula

    const int CALORIES = 2000;

    const int CANGOSLEEP_AT_TIRED = 88;

    const size_t MAX_DIGESTIONHEAP = 3;

    const int NEEDSLEEPINPERCENT = 70;
    const int NEEDRESTINHOSPITALINPERCENT = 100;

    const std::chrono::seconds TOTALMAXLIFETIME = std::chrono::hours(100);
    const std::chrono::seconds LIFETIME = std::chrono::hours(1);
    const std::chrono::seconds AGEINGTIME = std::chrono::hours(1);
    const int AGE = 1;

    const std::chrono::milliseconds GOOD_TRAINTIME = std::chrono::milliseconds(10);
    const std::chrono::milliseconds MIDDLE_TRAINTIME = std::chrono::milliseconds(5);
    const std::chrono::milliseconds MIN_TRAINTIME = std::chrono::milliseconds(3);

    const char* CREATURENAME = "Botamon";

    const data::CreatureTrainTime CREATURETRAINTIME = data::CreatureTrainTime::Noon;

    const float MAX_HUNGRYOVERLAY_INTRAINING = 30.0f;
    const float MAX_THIRSTYOVERLAY_INTRAINING = 30.0f;
    const float MAX_TIREDOVERLAY_INTRAINING = 30.0f;

    const size_t MAX_SHORTMEMORY_SIZE = 5;
};


class creatureTestEvolutionBaby2 {
    public:

    // Attributes
    const int MAXHP = 25;
    const int MAXMP = 12;
    const int ATK = 8;
    const int DEF = 6;
    const int AGI = 6;
    const int INT = 8;
    const int EXP = 23;

    const int ATTR_INFLATION = 10;


    const int STARTLEVEL = 1;
    const int MINLEVEL = 1;
    const int MAXLEVEL = 5;
    const int LVL = 1;

    const data::CreatureLevel CREATURELEVEL = data::CreatureLevel::Baby2;

    const data::CreatureGender GENDER = data::CreatureGender::Male;

    const float WEIGHT = 10;
    const float MIN_WEIGHT = 4;
    const float MAX_WEIGHT = 80;

    const float BODYSIZE = 0.6f;
    const float MIN_BODYSIZE = 0.42f;
    const float MAX_BODYSIZE = 1.02f;

    const float MIN_BMI = 18;
    const float IDEAL_BMI = 26;
    const float MAX_BMI = 50;
    const float MAX_BODYSIZE_GENE = 0.86f;


    const float BMI = 26;
    const float BODYMASS = 28; // see CreatureCreator::getBodyMass for formula

    const int CALORIES = 2000;

    const int CANGOSLEEP_AT_TIRED = 88;

    const size_t MAX_DIGESTIONHEAP = 3;

    const int NEEDSLEEPINPERCENT = 70;
    const int NEEDRESTINHOSPITALINPERCENT = 100;

    const std::chrono::seconds TOTALMAXLIFETIME = std::chrono::hours(100);
    const std::chrono::seconds LIFETIME = std::chrono::hours(1);
    const std::chrono::seconds AGEINGTIME = std::chrono::hours(1);
    const int AGE = 1;

    const std::chrono::milliseconds GOOD_TRAINTIME = std::chrono::milliseconds(10);
    const std::chrono::milliseconds MIDDLE_TRAINTIME = std::chrono::milliseconds(5);
    const std::chrono::milliseconds MIN_TRAINTIME = std::chrono::milliseconds(3);

    const char* CREATURENAME = "Koromon";

    const data::CreatureTrainTime CREATURETRAINTIME = data::CreatureTrainTime::Noon;

    const float MAX_HUNGRYOVERLAY_INTRAINING = 30.0f;
    const float MAX_THIRSTYOVERLAY_INTRAINING = 30.0f;
    const float MAX_TIREDOVERLAY_INTRAINING = 30.0f;

    const size_t MAX_SHORTMEMORY_SIZE = 5;

};

class CreatureTestEvolution {
    public:
    
    static data::Creature make_DataCreature_Egg() {
        CreatureTestEvolutionEgg creatureTestEvolutionEgg;

        data::Creature creature;

        creature.setName(creatureTestEvolutionEgg.CREATURENAME);
        creature.setCreatureLevel(creatureTestEvolutionEgg.CREATURELEVEL);


        creature.setMinWeight(creatureTestEvolutionEgg.MIN_WEIGHT);
        creature.setMaxWeight(creatureTestEvolutionEgg.MAX_WEIGHT);
        creature.setBodySizeMin(creatureTestEvolutionEgg.MIN_BODYSIZE);
        creature.setBodySizeMax(creatureTestEvolutionEgg.MAX_BODYSIZE);


        creature.setStartLvL(creatureTestEvolutionEgg.STARTLEVEL);
        creature.setMinLvL(creatureTestEvolutionEgg.MINLEVEL);
        creature.setMaxLvL(creatureTestEvolutionEgg.MAXLEVEL);

        creature.setHitRate(90);
        creature.setCriticalHitRate(30);
        creature.setEvaRate(30);


        creature.setAttrBasis(data::Attribute::MaxHP,
                            creatureTestEvolutionEgg.MAXHP);
        creature.setAttrBasis(data::Attribute::MaxMP,
                            creatureTestEvolutionEgg.MAXMP);
        creature.setAttrBasis(data::Attribute::Atk, creatureTestEvolutionEgg.ATK);
        creature.setAttrBasis(data::Attribute::Def, creatureTestEvolutionEgg.DEF);
        creature.setAttrBasis(data::Attribute::Agi, creatureTestEvolutionEgg.AGI);
        creature.setAttrBasis(data::Attribute::Int, creatureTestEvolutionEgg.INT);
        creature.setAttrBasis(data::Attribute::Exp, creatureTestEvolutionEgg.EXP);

        creature.setAttrInflation(data::Attribute::MaxHP,
                                creatureTestEvolutionEgg.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::MaxMP,
                                creatureTestEvolutionEgg.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Atk,
                                creatureTestEvolutionEgg.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Def,
                                creatureTestEvolutionEgg.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Agi,
                                creatureTestEvolutionEgg.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Int,
                                creatureTestEvolutionEgg.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Exp,
                                creatureTestEvolutionEgg.ATTR_INFLATION);


        data::EvolutionCondition condition;
        condition.setTrainTimeEveryDay();

        creature.setEvolCondition(condition);

        return creature;
    }

    static data::Creature make_DataCreature_Baby() {
        CreatureTestEvolutionBaby creatureTestEvolutionBaby;

        data::Creature creature;

        creature.setName(creatureTestEvolutionBaby.CREATURENAME);
        creature.setCreatureLevel(creatureTestEvolutionBaby.CREATURELEVEL);


        creature.setMinWeight(creatureTestEvolutionBaby.MIN_WEIGHT);
        creature.setMaxWeight(creatureTestEvolutionBaby.MAX_WEIGHT);
        creature.setBodySizeMin(creatureTestEvolutionBaby.MIN_BODYSIZE);
        creature.setBodySizeMax(creatureTestEvolutionBaby.MAX_BODYSIZE);


        creature.setStartLvL(creatureTestEvolutionBaby.STARTLEVEL);
        creature.setMinLvL(creatureTestEvolutionBaby.MINLEVEL);
        creature.setMaxLvL(creatureTestEvolutionBaby.MAXLEVEL);

        creature.setHitRate(90);
        creature.setCriticalHitRate(30);
        creature.setEvaRate(30);


        creature.setAttrBasis(data::Attribute::MaxHP,
                            creatureTestEvolutionBaby.MAXHP);
        creature.setAttrBasis(data::Attribute::MaxMP,
                            creatureTestEvolutionBaby.MAXMP);
        creature.setAttrBasis(data::Attribute::Atk, creatureTestEvolutionBaby.ATK);
        creature.setAttrBasis(data::Attribute::Def, creatureTestEvolutionBaby.DEF);
        creature.setAttrBasis(data::Attribute::Agi, creatureTestEvolutionBaby.AGI);
        creature.setAttrBasis(data::Attribute::Int, creatureTestEvolutionBaby.INT);
        creature.setAttrBasis(data::Attribute::Exp, creatureTestEvolutionBaby.EXP);

        creature.setAttrInflation(data::Attribute::MaxHP,
                                creatureTestEvolutionBaby.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::MaxMP,
                                creatureTestEvolutionBaby.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Atk,
                                creatureTestEvolutionBaby.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Def,
                                creatureTestEvolutionBaby.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Agi,
                                creatureTestEvolutionBaby.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Int,
                                creatureTestEvolutionBaby.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Exp,
                                creatureTestEvolutionBaby.ATTR_INFLATION);

        data::EvolutionCondition condition;
        condition.setTrainTimeEveryDay();
        condition.setWeight(5);

        creature.setEvolCondition(condition);

        return creature;
    }

    static data::Creature make_DataCreature_Baby2() {
        creatureTestEvolutionBaby2 creatureTestEvolutionBaby2;
        
        data::Creature creature;

        creature.setName(creatureTestEvolutionBaby2.CREATURENAME);
        creature.setCreatureLevel(creatureTestEvolutionBaby2.CREATURELEVEL);


        creature.setMinWeight(creatureTestEvolutionBaby2.MIN_WEIGHT);
        creature.setMaxWeight(creatureTestEvolutionBaby2.MAX_WEIGHT);
        creature.setBodySizeMin(creatureTestEvolutionBaby2.MIN_BODYSIZE);
        creature.setBodySizeMax(creatureTestEvolutionBaby2.MAX_BODYSIZE);


        creature.setStartLvL(creatureTestEvolutionBaby2.STARTLEVEL);
        creature.setMinLvL(creatureTestEvolutionBaby2.MINLEVEL);
        creature.setMaxLvL(creatureTestEvolutionBaby2.MAXLEVEL);

        creature.setHitRate(90);
        creature.setCriticalHitRate(30);
        creature.setEvaRate(30);


        creature.setAttrBasis(data::Attribute::MaxHP,
                            creatureTestEvolutionBaby2.MAXHP);
        creature.setAttrBasis(data::Attribute::MaxMP,
                            creatureTestEvolutionBaby2.MAXMP);
        creature.setAttrBasis(data::Attribute::Atk,
                            creatureTestEvolutionBaby2.ATK);
        creature.setAttrBasis(data::Attribute::Def,
                            creatureTestEvolutionBaby2.DEF);
        creature.setAttrBasis(data::Attribute::Agi,
                            creatureTestEvolutionBaby2.AGI);
        creature.setAttrBasis(data::Attribute::Int,
                            creatureTestEvolutionBaby2.INT);
        creature.setAttrBasis(data::Attribute::Exp,
                            creatureTestEvolutionBaby2.EXP);

        creature.setAttrInflation(data::Attribute::MaxHP,
                                creatureTestEvolutionBaby2.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::MaxMP,
                                creatureTestEvolutionBaby2.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Atk,
                                creatureTestEvolutionBaby2.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Def,
                                creatureTestEvolutionBaby2.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Agi,
                                creatureTestEvolutionBaby2.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Int,
                                creatureTestEvolutionBaby2.ATTR_INFLATION);
        creature.setAttrInflation(data::Attribute::Exp,
                                creatureTestEvolutionBaby2.ATTR_INFLATION);

        data::EvolutionCondition condition;
        condition.setTrainTimeEveryDay();
        condition.setWeight(10);

        creature.setEvolCondition(condition);

        return creature;
    }


    static std::chrono::system_clock::time_point
    make_time_point_01_01_2000() {
        // create tm with 1/1/2000:
        std::tm timeinfo = std::tm();
        timeinfo.tm_year = 100; // year: 2000
        timeinfo.tm_mon = 0;    // month: january
        timeinfo.tm_mday = 1;   // day: 1st
        std::time_t tt = std::mktime(&timeinfo);

        return std::chrono::system_clock::from_time_t(tt);
    }


    static std::vector<data::Creature>
    make_DataCreature_Evolutions() {
        data::Creature egg = make_DataCreature_Egg();
        data::Creature baby = make_DataCreature_Baby();
        data::Creature baby2 = make_DataCreature_Baby2();

        egg.addNextCreature(baby);

        baby.addPrevCreature(egg);
        baby.addNextCreature(baby2);

        baby2.addPrevCreature(baby);

        return {egg, baby, baby2};
    }

    static std::vector<std::shared_ptr<data::Creature>>
    make_DataCreature_Evolutions_shared_ptrs() {
        auto egg = std::make_shared<data::Creature>(make_DataCreature_Egg());
        auto baby = std::make_shared<data::Creature>(make_DataCreature_Baby());
        auto baby2 = std::make_shared<data::Creature>(make_DataCreature_Baby2());

        egg->addNextCreature(*baby);

        baby->addPrevCreature(*egg);
        baby->addNextCreature(*baby2);

        baby2->addPrevCreature(*baby);

        return {egg, baby, baby2};
    }
};

#endif // ENTITY_GAME_CREATURETESTDATAEVOLUTION_HPP_
