#ifndef ENTITY_GAME_CREATURETESTDATAEVOLUTION_H_
#define ENTITY_GAME_CREATURETESTDATAEVOLUTION_H_

#include "Entity/Game/CreatureEntityCreator.h"

class CreatureTestEvolutionEgg {
    public:

    // Attributes
    static constexpr int MAXHP = 1;
    static constexpr int MAXMP = 1;
    static constexpr int ATK = 1;
    static constexpr int DEF = 1;
    static constexpr int AGI = 1;
    static constexpr int INT = 1;
    static constexpr int EXP = 1;

    static constexpr int ATTR_INFLATION = 1;


    static constexpr int STARTLEVEL = 1;
    static constexpr int MINLEVEL = 1;
    static constexpr int MAXLEVEL = 5;
    static constexpr int LVL = 1;

    static constexpr data::CreatureLevel CREATURELEVEL = data::CreatureLevel::Egg;

    static constexpr data::CreatureGender GENDER = data::CreatureGender::Male;


    static constexpr float WEIGHT = 5;
    static constexpr float MIN_WEIGHT = 2;
    static constexpr float MAX_WEIGHT = 40;

    static constexpr float BODYSIZE = 0.3f;
    static constexpr float MIN_BODYSIZE = 0.21f;
    static constexpr float MAX_BODYSIZE = 0.51f;

    static constexpr float MIN_BMI = 18;
    static constexpr float IDEAL_BMI = 26;
    static constexpr float MAX_BMI = 50;
    static constexpr float MAX_BODYSIZE_GENE = 0.43f;


    static constexpr float BMI = 25;
    static constexpr float BODYMASS = 57; // see CreatureCreator::getBodyMass for formula

    static constexpr int CALORIES = 2000;

    static constexpr int CANGOSLEEP_AT_TIRED = 88;

    static constexpr size_t MAX_DIGESTIONHEAP = 3;

    static constexpr int NEEDSLEEPINPERCENT = 70;
    static constexpr int NEEDRESTINHOSPITALINPERCENT = 100;

    static constexpr std::chrono::seconds TOTALMAXLIFETIME = std::chrono::hours(100);
    static constexpr std::chrono::seconds LIFETIME = std::chrono::hours(0);
    static constexpr std::chrono::seconds AGEINGTIME = std::chrono::hours(1);
    static constexpr int AGE = 0;

    static constexpr std::chrono::milliseconds GOOD_TRAINTIME = std::chrono::milliseconds(10);
    static constexpr std::chrono::milliseconds MIDDLE_TRAINTIME = std::chrono::milliseconds(5);
    static constexpr std::chrono::milliseconds MIN_TRAINTIME = std::chrono::milliseconds(3);

    static constexpr const char* CREATURENAME = "Egg";

    static constexpr data::CreatureTrainTime CREATURETRAINTIME = data::CreatureTrainTime::Noon;

    static constexpr float MAX_HUNGRYOVERLAY_INTRAINING = 30.0f;
    static constexpr float MAX_THIRSTYOVERLAY_INTRAINING = 30.0f;
    static constexpr float MAX_TIREDOVERLAY_INTRAINING = 30.0f;

    static constexpr size_t MAX_SHORTMEMORY_SIZE = 5;
};

class CreatureTestEvolutionBaby {
    public:

    // Attributes
    static constexpr int MAXHP = 20;
    static constexpr int MAXMP = 10;
    static constexpr int ATK = 6;
    static constexpr int DEF = 3;
    static constexpr int AGI = 4;
    static constexpr int INT = 6;
    static constexpr int EXP = 12;

    static constexpr int ATTR_INFLATION = 8;


    static constexpr int STARTLEVEL = 1;
    static constexpr int MINLEVEL = 1;
    static constexpr int MAXLEVEL = 5;
    static constexpr int LVL = 1;

    static constexpr data::CreatureLevel CREATURELEVEL = data::CreatureLevel::Baby;

    static constexpr data::CreatureGender GENDER = data::CreatureGender::Male;

    static constexpr float WEIGHT = 5;
    static constexpr float MIN_WEIGHT = 2;
    static constexpr float MAX_WEIGHT = 40;

    static constexpr float BODYSIZE = 0.2f;
    static constexpr float MIN_BODYSIZE = 0.14f;
    static constexpr float MAX_BODYSIZE = 0.34f;

    static constexpr float MIN_BMI = 18;
    static constexpr float IDEAL_BMI = 26;
    static constexpr float MAX_BMI = 50;
    static constexpr float MAX_BODYSIZE_GENE = 0.28f;


    static constexpr float BMI = 25;
    static constexpr float BODYMASS = 57; // see CreatureCreator::getBodyMass for formula

    static constexpr int CALORIES = 2000;

    static constexpr int CANGOSLEEP_AT_TIRED = 88;

    static constexpr size_t MAX_DIGESTIONHEAP = 3;

    static constexpr int NEEDSLEEPINPERCENT = 70;
    static constexpr int NEEDRESTINHOSPITALINPERCENT = 100;

    static constexpr std::chrono::seconds TOTALMAXLIFETIME = std::chrono::hours(100);
    static constexpr std::chrono::seconds LIFETIME = std::chrono::hours(1);
    static constexpr std::chrono::seconds AGEINGTIME = std::chrono::hours(1);
    static constexpr int AGE = 1;

    static constexpr std::chrono::milliseconds GOOD_TRAINTIME = std::chrono::milliseconds(10);
    static constexpr std::chrono::milliseconds MIDDLE_TRAINTIME = std::chrono::milliseconds(5);
    static constexpr std::chrono::milliseconds MIN_TRAINTIME = std::chrono::milliseconds(3);

    static constexpr const char* CREATURENAME = "Botamon";

    static constexpr data::CreatureTrainTime CREATURETRAINTIME = data::CreatureTrainTime::Noon;

    static constexpr float MAX_HUNGRYOVERLAY_INTRAINING = 30.0f;
    static constexpr float MAX_THIRSTYOVERLAY_INTRAINING = 30.0f;
    static constexpr float MAX_TIREDOVERLAY_INTRAINING = 30.0f;

    static constexpr size_t MAX_SHORTMEMORY_SIZE = 5;
};


class CreatureTestEvolutionBaby2 {
    public:

    // Attributes
    static constexpr int MAXHP = 25;
    static constexpr int MAXMP = 12;
    static constexpr int ATK = 8;
    static constexpr int DEF = 6;
    static constexpr int AGI = 6;
    static constexpr int INT = 8;
    static constexpr int EXP = 23;

    static constexpr int ATTR_INFLATION = 10;


    static constexpr int STARTLEVEL = 1;
    static constexpr int MINLEVEL = 1;
    static constexpr int MAXLEVEL = 5;
    static constexpr int LVL = 1;

    static constexpr data::CreatureLevel CREATURELEVEL = data::CreatureLevel::Baby2;

    static constexpr data::CreatureGender GENDER = data::CreatureGender::Male;

    static constexpr float WEIGHT = 10;
    static constexpr float MIN_WEIGHT = 4;
    static constexpr float MAX_WEIGHT = 80;

    static constexpr float BODYSIZE = 0.6f;
    static constexpr float MIN_BODYSIZE = 0.42f;
    static constexpr float MAX_BODYSIZE = 1.02f;

    static constexpr float MIN_BMI = 18;
    static constexpr float IDEAL_BMI = 26;
    static constexpr float MAX_BMI = 50;
    static constexpr float MAX_BODYSIZE_GENE = 0.86f;


    static constexpr float BMI = 26;
    static constexpr float BODYMASS = 28; // see CreatureCreator::getBodyMass for formula

    static constexpr int CALORIES = 2000;

    static constexpr int CANGOSLEEP_AT_TIRED = 88;

    static constexpr size_t MAX_DIGESTIONHEAP = 3;

    static constexpr int NEEDSLEEPINPERCENT = 70;
    static constexpr int NEEDRESTINHOSPITALINPERCENT = 100;

    static constexpr std::chrono::seconds TOTALMAXLIFETIME = std::chrono::hours(100);
    static constexpr std::chrono::seconds LIFETIME = std::chrono::hours(1);
    static constexpr std::chrono::seconds AGEINGTIME = std::chrono::hours(1);
    static constexpr int AGE = 1;

    static constexpr std::chrono::milliseconds GOOD_TRAINTIME = std::chrono::milliseconds(10);
    static constexpr std::chrono::milliseconds MIDDLE_TRAINTIME = std::chrono::milliseconds(5);
    static constexpr std::chrono::milliseconds MIN_TRAINTIME = std::chrono::milliseconds(3);

    static constexpr const char* CREATURENAME = "Koromon";

    static constexpr data::CreatureTrainTime CREATURETRAINTIME = data::CreatureTrainTime::Noon;

    static constexpr float MAX_HUNGRYOVERLAY_INTRAINING = 30.0f;
    static constexpr float MAX_THIRSTYOVERLAY_INTRAINING = 30.0f;
    static constexpr float MAX_TIREDOVERLAY_INTRAINING = 30.0f;

    static constexpr size_t MAX_SHORTMEMORY_SIZE = 5;

};

class CreatureTestEvolution {
    public:
    static std::chrono::system_clock::time_point make_time_point_01_01_2000();

    static data::Creature make_DataCreature_Egg();
    static data::Creature make_DataCreature_Baby();
    static data::Creature make_DataCreature_Baby2();
    
    static std::vector<data::Creature> make_DataCreature_Evolutions();

    static std::vector<std::shared_ptr<data::Creature>>
    make_DataCreature_Evolutions_shared_ptrs();
};

#endif // ENTITY_GAME_CREATURETESTDATAEVOLUTION_HPP_
