#ifndef TEST_SYSTEM_GAME_MAKECREATUREHELPER_H_
#define TEST_SYSTEM_GAME_MAKECREATUREHELPER_H_

#include "Entity/Game/CreatureEntityCreator.h"
#include "Entity/Game/CreatureTestData.h"

class MakeCreatureHelper {
    public:

    static gamecomp::CreatureDataComponent make_CreatureData() {
        CreatureTestData creatureTestData;
        gamecomp::CreatureDataComponent ret;

        ret.creature = creatureTestData.make_DataCreature();

        return ret;
    }

    static gamecomp::CreatureProgressTimersComponent
    make_CreatureProgressTimers() {
        CreatureTestData creatureTestData;
        gamecomputil::ProgressTimerUtil progresstimer_util;
        computil::DateTimerUtil datetimer_util;

        gamecomp::CreatureProgressTimersComponent ret;

        ret.creaturelevel = creatureTestData.CREATURELEVEL;

        auto time = creatureTestData.make_time_point_01_01_2000();
        float factor = 1.0f;

        for (auto timertype : earr::Enum<gamecomp::CreatureProgressTimer>()) {
            progresstimer_util.init(earr::enum_array_at(ret.timer, timertype), time,
                                    factor);
        }
        for (auto timertype_callback :
            earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
            progresstimer_util.init(
                earr::enum_array_at(ret.callback, timertype_callback), time,
                factor);
        }
        for (auto timertype_increment :
            earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
            progresstimer_util.init(
                earr::enum_array_at(ret.increment, timertype_increment), time,
                factor);
        }


        datetimer_util.init(ret.lifetimer, time, factor);
        datetimer_util.start(ret.lifetimer);

        return ret;
    }

    static gamecomp::BattlerStatusesComponent make_BattlerStatuses() {
        gamecomp::BattlerStatusesComponent ret;

        return ret;
    }

    static gamecomp::BattlerBattleStateComponent
    make_BattlerBattleState() {
        gamecomp::BattlerBattleStateComponent ret;

        return ret;
    }

    static gamecomp::BattlerResistsComponent make_BattlerResists() {
        gamecomp::BattlerResistsComponent ret;

        return ret;
    }

    static gamecomp::CreatureBattlerComponent make_CreatureBattler() {
        CreatureTestData creatureTestData;
        gamecomp::CreatureBattlerComponent ret;

        earr::enum_array_at(ret.attrbase, +data::Attribute::MaxHP) =
            creatureTestData.MAXHP;
        earr::enum_array_at(ret.attrbase, +data::Attribute::MaxMP) =
            creatureTestData.MAXMP;
        earr::enum_array_at(ret.attrbase, +data::Attribute::Atk) =
            creatureTestData.ATK;
        earr::enum_array_at(ret.attrbase, +data::Attribute::Def) =
            creatureTestData.DEF;
        earr::enum_array_at(ret.attrbase, +data::Attribute::Agi) =
            creatureTestData.AGI;
        earr::enum_array_at(ret.attrbase, +data::Attribute::Int) =
            creatureTestData.INT;
        earr::enum_array_at(ret.attrbase, +data::Attribute::Exp) =
            creatureTestData.EXP;

        earr::enum_array_at(ret.attrinf, +data::Attribute::MaxHP) =
            creatureTestData.ATTR_INFLATION;
        earr::enum_array_at(ret.attrinf, +data::Attribute::MaxMP) =
            creatureTestData.ATTR_INFLATION;
        earr::enum_array_at(ret.attrinf, +data::Attribute::Atk) =
            creatureTestData.ATTR_INFLATION;
        earr::enum_array_at(ret.attrinf, +data::Attribute::Def) =
            creatureTestData.ATTR_INFLATION;
        earr::enum_array_at(ret.attrinf, +data::Attribute::Agi) =
            creatureTestData.ATTR_INFLATION;
        earr::enum_array_at(ret.attrinf, +data::Attribute::Int) =
            creatureTestData.ATTR_INFLATION;
        earr::enum_array_at(ret.attrinf, +data::Attribute::Exp) =
            creatureTestData.ATTR_INFLATION;

        earr::enum_array_at(ret.attrplus, +data::Attribute::MaxHP) = 0;
        earr::enum_array_at(ret.attrplus, +data::Attribute::MaxMP) = 0;
        earr::enum_array_at(ret.attrplus, +data::Attribute::Atk) = 0;
        earr::enum_array_at(ret.attrplus, +data::Attribute::Def) = 0;
        earr::enum_array_at(ret.attrplus, +data::Attribute::Agi) = 0;
        earr::enum_array_at(ret.attrplus, +data::Attribute::Int) = 0;
        earr::enum_array_at(ret.attrplus, +data::Attribute::Exp) = 0;

        earr::enum_array_at(ret.attr, +data::Attribute::MaxHP) =
            creatureTestData.MAXHP;
        earr::enum_array_at(ret.attr, +data::Attribute::MaxMP) =
            creatureTestData.MAXMP;
        earr::enum_array_at(ret.attr, +data::Attribute::Atk) =
            creatureTestData.ATK;
        earr::enum_array_at(ret.attr, +data::Attribute::Def) =
            creatureTestData.DEF;
        earr::enum_array_at(ret.attr, +data::Attribute::Agi) =
            creatureTestData.AGI;
        earr::enum_array_at(ret.attr, +data::Attribute::Int) =
            creatureTestData.INT;
        earr::enum_array_at(ret.attr, +data::Attribute::Exp) =
            creatureTestData.EXP;


        // set level 1
        ret.exp = 0;
        ret.lvl = creatureTestData.LVL;

        ret.hp = creatureTestData.MAXHP;
        ret.mp = creatureTestData.MAXMP;


        // set attributes for 5 Levels, Index 0-5 => 5 Levels
        earr::enum_array_at(ret.attrparam, +data::Attribute::MaxHP) = {
            0,
            creatureTestData.MAXHP,
            creatureTestData.MAXHP + creatureTestData.ATTR_INFLATION,
            creatureTestData.MAXHP + creatureTestData.ATTR_INFLATION * 2,
            creatureTestData.MAXHP + creatureTestData.ATTR_INFLATION * 3,
            creatureTestData.MAXMP + creatureTestData.ATTR_INFLATION * 4};

        earr::enum_array_at(ret.attrparam, +data::Attribute::MaxMP) = {
            0,
            creatureTestData.MAXMP,
            creatureTestData.MAXMP + creatureTestData.ATTR_INFLATION,
            creatureTestData.MAXMP + creatureTestData.ATTR_INFLATION * 2,
            creatureTestData.MAXMP + creatureTestData.ATTR_INFLATION * 3,
            creatureTestData.MAXMP + creatureTestData.ATTR_INFLATION * 4};

        earr::enum_array_at(ret.attrparam, +data::Attribute::Atk) = {
            0,
            creatureTestData.ATK,
            creatureTestData.ATK + creatureTestData.ATTR_INFLATION,
            creatureTestData.ATK + creatureTestData.ATTR_INFLATION * 2,
            creatureTestData.ATK + creatureTestData.ATTR_INFLATION * 3,
            creatureTestData.ATK + creatureTestData.ATTR_INFLATION * 4};

        earr::enum_array_at(ret.attrparam, +data::Attribute::Def) = {
            0,
            creatureTestData.DEF,
            creatureTestData.DEF + creatureTestData.ATTR_INFLATION,
            creatureTestData.DEF + creatureTestData.ATTR_INFLATION * 2,
            creatureTestData.DEF + creatureTestData.ATTR_INFLATION * 3,
            creatureTestData.DEF + creatureTestData.ATTR_INFLATION * 4};

        earr::enum_array_at(ret.attrparam, +data::Attribute::Agi) = {
            0,
            creatureTestData.AGI,
            creatureTestData.AGI + creatureTestData.ATTR_INFLATION,
            creatureTestData.AGI + creatureTestData.ATTR_INFLATION * 2,
            creatureTestData.AGI + creatureTestData.ATTR_INFLATION * 3,
            creatureTestData.AGI + creatureTestData.ATTR_INFLATION * 4};

        earr::enum_array_at(ret.attrparam, +data::Attribute::Exp) = {
            0,
            creatureTestData.EXP,
            creatureTestData.EXP + creatureTestData.ATTR_INFLATION,
            creatureTestData.EXP + creatureTestData.ATTR_INFLATION * 2,
            creatureTestData.EXP + creatureTestData.ATTR_INFLATION * 3,
            creatureTestData.EXP + creatureTestData.ATTR_INFLATION * 4};

        return ret;
    }

    static gamecomp::CreatureBattlerGeneComponent
    make_CreatureBattlerGene() {
        gamecomp::CreatureBattlerGeneComponent ret;

        ret.boniattrfactor.fill(0);
        ret.boniattrinflation.fill(0);

        return ret;
    }

    static gamecomp::CreatureGeneComponent make_CreatureGene() {
        CreatureTestData creatureTestData;
        gamecomp::CreatureGeneComponent ret;

        ret.generationnr = 1;
        auto creaturelevel = creatureTestData.CREATURELEVEL;

        ret.gender = creatureTestData.GENDER;
        ret.min_bmi = creatureTestData.MIN_BMI;
        ret.ideal_bmi = creatureTestData.IDEAL_BMI;
        ret.max_bmi = creatureTestData.MAX_BMI;
        ret.max_bodysize = creatureTestData.MAX_BODYSIZE_GENE;
        ret.bodymass = creatureTestData.BODYMASS;

        ret.cangosleep_at_tired = creatureTestData.CANGOSLEEP_AT_TIRED;
        ret.max_poopstack = creatureTestData.MAX_POOPSTACK;

        auto& perevolution = earr::enum_array_at(ret.perevolution, creaturelevel);

        perevolution.needsleepinpercent = creatureTestData.NEEDSLEEPINPERCENT;
        perevolution.needrestinhospitalinpercent =
            creatureTestData.NEEDRESTINHOSPITALINPERCENT;

        ret.totalmaxlifetime = creatureTestData.TOTALMAXLIFETIME;

        auto& training = perevolution.training;

        training.good_trainitime = creatureTestData.GOOD_TRAINTIME;
        training.middle_trainitime = creatureTestData.MIDDLE_TRAINTIME;
        training.min_trainitime = creatureTestData.MIN_TRAINTIME;

        training.max_hungryoverlay_intraining =
            creatureTestData.MAX_HUNGRYOVERLAY_INTRAINING;
        training.max_thirstyoverlay_intraining =
            creatureTestData.MAX_THIRSTYOVERLAY_INTRAINING;
        training.max_tiredoverlay_intraining =
            creatureTestData.MAX_TIREDOVERLAY_INTRAINING;

        return ret;
    }


    static gamecomp::CreatureMemoryComponent make_CreatureMemory() {
        CreatureTestData creatureTestData;
        gamecomp::CreatureMemoryComponent ret;

        ret.max_short_memorysize = creatureTestData.MAX_SHORTMEMORY_SIZE;

        return ret;
    }

    static gamecomp::CreaturePersonalityComponent
    make_CreaturePersonality() {
        gamecomp::CreaturePersonalityComponent ret;

        return ret;
    }

    static gamecomp::CreatureHungerComponent make_CreatureHunger() {
        gamecomp::CreatureHungerComponent ret;

        ret.poopstack = 0;
        ret.starvationphase = gamecomp::StarvationPhase::None;

        return ret;
    }

    static gamecomp::CreatureEvolveComponent make_CreatureEvolve() {
        gamecomp::CreatureEvolveComponent ret;

        return ret;
    }

    static gamecomp::CreatureSleepComponent make_CreatureSleep() {
        gamecomp::CreatureSleepComponent ret;

        return ret;
    }

    static gamecomp::CreatureTrainingComponent
    make_CreatureTraining() {
        CreatureTestData creatureTestData;
        gamecomp::CreatureTrainingComponent ret;

        earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::MaxHP) =
            creatureTestData.MAXHP;
        earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::MaxMP) =
            creatureTestData.MAXMP;
        earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Atk) =
            creatureTestData.ATK;
        earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Def) =
            creatureTestData.DEF;
        earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Agi) =
            creatureTestData.AGI;
        earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Int) =
            creatureTestData.INT;
        earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Exp) =
            creatureTestData.EXP;

        earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::MaxHP) =
            creatureTestData.MAXHP;
        earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::MaxMP) =
            creatureTestData.MAXMP;
        earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Atk) =
            creatureTestData.ATK;
        earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Def) =
            creatureTestData.DEF;
        earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Agi) =
            creatureTestData.AGI;
        earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Int) =
            creatureTestData.INT;
        earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Exp) =
            creatureTestData.EXP;

        ret.trainingcounter.fill(0);

        return ret;
    }

    static gamecomp::CreatureBodilyStateComponent
    make_CreatureBodilyState() {
        gamecomp::CreatureBodilyStateComponent ret;

        ret.hurtcount = 0;
        ret.illcount = 0;

        return ret;
    }

    static gamecomp::CreatureBodyComponent make_CreatureBody() {
        CreatureTestData creatureTestData;
        gamecomp::CreatureBodyComponent ret;

        ret.bmi = creatureTestData.BMI;
        ret.bodysize = creatureTestData.BODYSIZE;
        ret.calories = creatureTestData.CALORIES;
        ret.weight = creatureTestData.WEIGHT;

        return ret;
    }

    static gamecomp::CreaturePsycheComponent make_CreaturePsyche() {
        gamecomp::CreaturePsycheComponent ret;

        ret.disc = 100;
        ret.luck = 100;

        return ret;
    }

    static gamecomp::CreatureLifeComponent make_CreatureLife() {
        CreatureTestData creatureTestData;
        gamecomp::CreatureLifeComponent ret;

        ret.name = "Testmon";

        ret.born = true;
        ret.birthday = creatureTestData.make_time_point_01_01_2000();

        ret.causeofdeath = gamecomp::CauseOfDeath::Alive;
        ret.causeofrunaway = gamecomp::CauseOfRunAway::NotRunAway;
        ret.isdead = false;

        ret.creaturelevel = creatureTestData.CREATURELEVEL;

        ret.maxlifetime = creatureTestData.TOTALMAXLIFETIME;
        ret.lifetime = creatureTestData.LIFETIME;
        ret.ageingtime = creatureTestData.AGEINGTIME;
        ret.age = creatureTestData.AGE;

        ret.oldlevel = creatureTestData.LVL;

        ret.hasstatus.fill(false);
        ret.isbusy = false;

        return ret;
    }



    static gameentity::Entity create_Entity_Creature(
        gameentity::EntityManager& entities) {

        auto entity = entities.create();

        entities.assign<gamecomp::CreatureDataComponent>(entity, make_CreatureData());
        entities.assign<gamecomp::CreatureProgressTimersComponent>(entity, 
            make_CreatureProgressTimers());

        entities.assign<gamecomp::BattlerStatusesComponent>(entity, make_BattlerStatuses());
        entities.assign<gamecomp::BattlerBattleStateComponent>(entity, 
            make_BattlerBattleState());
        entities.assign<gamecomp::BattlerResistsComponent>(entity, make_BattlerResists());
        entities.assign<gamecomp::CreatureBattlerComponent>(entity, make_CreatureBattler());

        entities.assign<gamecomp::CreatureBattlerGeneComponent>(entity, 
            make_CreatureBattlerGene());
        entities.assign<gamecomp::CreatureGeneComponent>(entity, make_CreatureGene());

        entities.assign<gamecomp::CreatureMemoryComponent>(entity, make_CreatureMemory());
        entities.assign<gamecomp::CreaturePersonalityComponent>(entity, 
            make_CreaturePersonality());

        entities.assign<gamecomp::CreatureHungerComponent>(entity, make_CreatureHunger());
        entities.assign<gamecomp::CreatureEvolveComponent>(entity, make_CreatureEvolve());
        entities.assign<gamecomp::CreatureSleepComponent>(entity, make_CreatureSleep());
        entities.assign<gamecomp::CreatureTrainingComponent>(entity, make_CreatureTraining());
        entities.assign<gamecomp::CreatureBodilyStateComponent>(entity, 
            make_CreatureBodilyState());
        entities.assign<gamecomp::CreatureBodyComponent>(entity, make_CreatureBody());
        entities.assign<gamecomp::CreaturePsycheComponent>(entity, make_CreaturePsyche());
        entities.assign<gamecomp::CreatureLifeComponent>(entity, make_CreatureLife());

        return entity;
    }


    static gameentity::Entity create_Entity_CreatureAllWaitTime(
        gameentity::EntityManager& entities, gamecomp::waittime_t waittime) {
        CreatureTestData creatureTestData;

        auto entity = create_Entity_Creature(entities);
        auto creaturelevel = creatureTestData.CREATURELEVEL;


        auto& timers = entities.get<gamecomp::CreatureProgressTimersComponent>(entity);

        for (auto timertype : earr::Enum<gamecomp::CreatureProgressTimer>()) {
            earr::enum_array_at(
                earr::enum_array_at(timers.timer, timertype).waittime,
                creaturelevel) = waittime;
        }
        for (auto timertype_callback :
            earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
            earr::enum_array_at(
                earr::enum_array_at(timers.callback, timertype_callback)
                    .base.waittime,
                creaturelevel) = waittime;
        }
        for (auto timertype_increment :
            earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
            earr::enum_array_at(
                earr::enum_array_at(timers.increment, timertype_increment)
                    .base.waittime,
                creaturelevel) = waittime;
        }

        return entity;
    }


    static gameentity::Entity
    create_Entity_CreatureAllWaitTime_Starvation(
        gameentity::EntityManager& entities, gamecomp::waittime_t waittime) {
        CreatureTestData creatureTestData;

        auto entity = create_Entity_Creature(entities);
        auto creaturelevel = creatureTestData.CREATURELEVEL;


        auto timers = entities.get<gamecomp::CreatureProgressTimersComponent>(entity);

        for (auto timertype : earr::Enum<gamecomp::CreatureProgressTimer>()) {
            earr::enum_array_at(
                earr::enum_array_at(timers.timer, timertype).waittime,
                creaturelevel) = waittime;
        }
        for (auto timertype_callback :
            earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
            earr::enum_array_at(
                earr::enum_array_at(timers.callback, timertype_callback)
                    .base.waittime,
                creaturelevel) = waittime;
        }
        for (auto timertype_increment :
            earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
            earr::enum_array_at(
                earr::enum_array_at(timers.increment, timertype_increment)
                    .base.waittime,
                creaturelevel) = waittime;
        }
        for (auto starvationphase : earr::Enum<gamecomp::StarvationPhase>()) {
            earr::enum_array_at(
                earr::enum_array_at(timers.starvation, starvationphase)
                    .base.waittime,
                creaturelevel) = waittime;
        }

        return entity;
    }
};


#endif // TEST_SYSTEM_GAME_MAKECREATUREHELPER_H_
