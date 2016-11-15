#include "MakeCreatureHelper.h"


gamecomp::CreatureDataComponent MakeCreatureHelper::make_CreatureData() {
    gamecomp::CreatureDataComponent ret;

    ret.creature = CreatureTestData::make_DataCreature();

    return ret;
}

gamecomp::CreatureProgressTimersComponent
MakeCreatureHelper::make_CreatureProgressTimers() {
    gamecomputil::ProgressTimerUtil progresstimer_util;
    computil::DateTimerUtil datetimer_util;

    gamecomp::CreatureProgressTimersComponent ret;

    ret.creaturelevel = CreatureTestData::CREATURELEVEL;

    auto time = CreatureTestData::make_time_point_01_01_2000();
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

gamecomp::BattlerStatusesComponent MakeCreatureHelper::make_BattlerStatuses() {
    gamecomp::BattlerStatusesComponent ret;

    return ret;
}

gamecomp::BattlerBattleStateComponent
MakeCreatureHelper::make_BattlerBattleState() {
    gamecomp::BattlerBattleStateComponent ret;

    return ret;
}

gamecomp::BattlerResistsComponent MakeCreatureHelper::make_BattlerResists() {
    gamecomp::BattlerResistsComponent ret;

    return ret;
}

gamecomp::CreatureBattlerComponent MakeCreatureHelper::make_CreatureBattler() {
    gamecomp::CreatureBattlerComponent ret;

    earr::enum_array_at(ret.attrbase, +data::Attribute::MaxHP) =
        CreatureTestData::MAXHP;
    earr::enum_array_at(ret.attrbase, +data::Attribute::MaxMP) =
        CreatureTestData::MAXMP;
    earr::enum_array_at(ret.attrbase, +data::Attribute::Atk) =
        CreatureTestData::ATK;
    earr::enum_array_at(ret.attrbase, +data::Attribute::Def) =
        CreatureTestData::DEF;
    earr::enum_array_at(ret.attrbase, +data::Attribute::Agi) =
        CreatureTestData::AGI;
    earr::enum_array_at(ret.attrbase, +data::Attribute::Int) =
        CreatureTestData::INT;
    earr::enum_array_at(ret.attrbase, +data::Attribute::Exp) =
        CreatureTestData::EXP;

    earr::enum_array_at(ret.attrinf, +data::Attribute::MaxHP) =
        CreatureTestData::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::MaxMP) =
        CreatureTestData::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::Atk) =
        CreatureTestData::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::Def) =
        CreatureTestData::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::Agi) =
        CreatureTestData::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::Int) =
        CreatureTestData::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::Exp) =
        CreatureTestData::ATTR_INFLATION;

    earr::enum_array_at(ret.attrplus, +data::Attribute::MaxHP) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::MaxMP) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::Atk) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::Def) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::Agi) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::Int) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::Exp) = 0;

    earr::enum_array_at(ret.attr, +data::Attribute::MaxHP) =
        CreatureTestData::MAXHP;
    earr::enum_array_at(ret.attr, +data::Attribute::MaxMP) =
        CreatureTestData::MAXMP;
    earr::enum_array_at(ret.attr, +data::Attribute::Atk) =
        CreatureTestData::ATK;
    earr::enum_array_at(ret.attr, +data::Attribute::Def) =
        CreatureTestData::DEF;
    earr::enum_array_at(ret.attr, +data::Attribute::Agi) =
        CreatureTestData::AGI;
    earr::enum_array_at(ret.attr, +data::Attribute::Int) =
        CreatureTestData::INT;
    earr::enum_array_at(ret.attr, +data::Attribute::Exp) =
        CreatureTestData::EXP;


    // set level 1
    ret.exp = 0;
    ret.lvl = CreatureTestData::LVL;

    ret.hp = CreatureTestData::MAXHP;
    ret.mp = CreatureTestData::MAXMP;


    // set attributes for 5 Levels, Index 0-5 => 5 Levels
    earr::enum_array_at(ret.attrparam, +data::Attribute::MaxHP) = {
        0,
        CreatureTestData::MAXHP,
        CreatureTestData::MAXHP + CreatureTestData::ATTR_INFLATION,
        CreatureTestData::MAXHP + CreatureTestData::ATTR_INFLATION * 2,
        CreatureTestData::MAXHP + CreatureTestData::ATTR_INFLATION * 3,
        CreatureTestData::MAXMP + CreatureTestData::ATTR_INFLATION * 4};

    earr::enum_array_at(ret.attrparam, +data::Attribute::MaxMP) = {
        0,
        CreatureTestData::MAXMP,
        CreatureTestData::MAXMP + CreatureTestData::ATTR_INFLATION,
        CreatureTestData::MAXMP + CreatureTestData::ATTR_INFLATION * 2,
        CreatureTestData::MAXMP + CreatureTestData::ATTR_INFLATION * 3,
        CreatureTestData::MAXMP + CreatureTestData::ATTR_INFLATION * 4};

    earr::enum_array_at(ret.attrparam, +data::Attribute::Atk) = {
        0,
        CreatureTestData::ATK,
        CreatureTestData::ATK + CreatureTestData::ATTR_INFLATION,
        CreatureTestData::ATK + CreatureTestData::ATTR_INFLATION * 2,
        CreatureTestData::ATK + CreatureTestData::ATTR_INFLATION * 3,
        CreatureTestData::ATK + CreatureTestData::ATTR_INFLATION * 4};

    earr::enum_array_at(ret.attrparam, +data::Attribute::Def) = {
        0,
        CreatureTestData::DEF,
        CreatureTestData::DEF + CreatureTestData::ATTR_INFLATION,
        CreatureTestData::DEF + CreatureTestData::ATTR_INFLATION * 2,
        CreatureTestData::DEF + CreatureTestData::ATTR_INFLATION * 3,
        CreatureTestData::DEF + CreatureTestData::ATTR_INFLATION * 4};

    earr::enum_array_at(ret.attrparam, +data::Attribute::Agi) = {
        0,
        CreatureTestData::AGI,
        CreatureTestData::AGI + CreatureTestData::ATTR_INFLATION,
        CreatureTestData::AGI + CreatureTestData::ATTR_INFLATION * 2,
        CreatureTestData::AGI + CreatureTestData::ATTR_INFLATION * 3,
        CreatureTestData::AGI + CreatureTestData::ATTR_INFLATION * 4};

    earr::enum_array_at(ret.attrparam, +data::Attribute::Exp) = {
        0,
        CreatureTestData::EXP,
        CreatureTestData::EXP + CreatureTestData::ATTR_INFLATION,
        CreatureTestData::EXP + CreatureTestData::ATTR_INFLATION * 2,
        CreatureTestData::EXP + CreatureTestData::ATTR_INFLATION * 3,
        CreatureTestData::EXP + CreatureTestData::ATTR_INFLATION * 4};

    return ret;
}

gamecomp::CreatureBattlerGeneComponent
MakeCreatureHelper::make_CreatureBattlerGene() {
    gamecomp::CreatureBattlerGeneComponent ret;

    ret.boniattrfactor.fill(0);
    ret.boniattrinflation.fill(0);

    return ret;
}

gamecomp::CreatureGeneComponent MakeCreatureHelper::make_CreatureGene() {
    gamecomp::CreatureGeneComponent ret;

    ret.generationnr = 1;
    auto creaturelevel = CreatureTestData::CREATURELEVEL;

    ret.gender = CreatureTestData::GENDER;
    ret.min_bmi = CreatureTestData::MIN_BMI;
    ret.ideal_bmi = CreatureTestData::IDEAL_BMI;
    ret.max_bmi = CreatureTestData::MAX_BMI;
    ret.max_bodysize = CreatureTestData::MAX_BODYSIZE_GENE;
    ret.bodymass = CreatureTestData::BODYMASS;

    ret.cangosleep_at_tired = CreatureTestData::CANGOSLEEP_AT_TIRED;
    ret.max_digestionheap = CreatureTestData::MAX_DIGESTIONHEAP;

    auto& perevolution = earr::enum_array_at(ret.perevolution, creaturelevel);

    perevolution.needsleepinpercent = CreatureTestData::NEEDSLEEPINPERCENT;
    perevolution.needrestinhospitalinpercent =
        CreatureTestData::NEEDRESTINHOSPITALINPERCENT;

    ret.totalmaxlifetime = CreatureTestData::TOTALMAXLIFETIME;

    auto& training = perevolution.training;

    training.good_trainitime = CreatureTestData::GOOD_TRAINTIME;
    training.middle_trainitime = CreatureTestData::MIDDLE_TRAINTIME;
    training.min_trainitime = CreatureTestData::MIN_TRAINTIME;

    training.max_hungryoverlay_intraining =
        CreatureTestData::MAX_HUNGRYOVERLAY_INTRAINING;
    training.max_thirstyoverlay_intraining =
        CreatureTestData::MAX_THIRSTYOVERLAY_INTRAINING;
    training.max_tiredoverlay_intraining =
        CreatureTestData::MAX_TIREDOVERLAY_INTRAINING;

    return ret;
}


gamecomp::CreatureMemoryComponent MakeCreatureHelper::make_CreatureMemory() {
    gamecomp::CreatureMemoryComponent ret;

    ret.max_short_memorysize = CreatureTestData::MAX_SHORTMEMORY_SIZE;

    return ret;
}

gamecomp::CreaturePersonalityComponent
MakeCreatureHelper::make_CreaturePersonality() {
    gamecomp::CreaturePersonalityComponent ret;

    return ret;
}

gamecomp::CreatureHungerComponent MakeCreatureHelper::make_CreatureHunger() {
    gamecomp::CreatureHungerComponent ret;

    ret.digestionheap = 0;
    ret.starvationphase = gamecomp::StarvationPhase::None;

    return ret;
}

gamecomp::CreatureEvolveComponent MakeCreatureHelper::make_CreatureEvolve() {
    gamecomp::CreatureEvolveComponent ret;

    return ret;
}

gamecomp::CreatureSleepComponent MakeCreatureHelper::make_CreatureSleep() {
    gamecomp::CreatureSleepComponent ret;

    return ret;
}

gamecomp::CreatureTrainingComponent
MakeCreatureHelper::make_CreatureTraining() {
    gamecomp::CreatureTrainingComponent ret;

    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::MaxHP) =
        CreatureTestData::MAXHP;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::MaxMP) =
        CreatureTestData::MAXMP;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Atk) =
        CreatureTestData::ATK;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Def) =
        CreatureTestData::DEF;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Agi) =
        CreatureTestData::AGI;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Int) =
        CreatureTestData::INT;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Exp) =
        CreatureTestData::EXP;

    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::MaxHP) =
        CreatureTestData::MAXHP;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::MaxMP) =
        CreatureTestData::MAXMP;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Atk) =
        CreatureTestData::ATK;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Def) =
        CreatureTestData::DEF;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Agi) =
        CreatureTestData::AGI;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Int) =
        CreatureTestData::INT;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Exp) =
        CreatureTestData::EXP;

    ret.trainingcounter.fill(0);

    return ret;
}

gamecomp::CreatureBodilyStateComponent
MakeCreatureHelper::make_CreatureBodilyState() {
    gamecomp::CreatureBodilyStateComponent ret;

    ret.hurtcount = 0;
    ret.illcount = 0;

    return ret;
}

gamecomp::CreatureBodyComponent MakeCreatureHelper::make_CreatureBody() {
    gamecomp::CreatureBodyComponent ret;

    ret.bmi = CreatureTestData::BMI;
    ret.bodysize = CreatureTestData::BODYSIZE;
    ret.calories = CreatureTestData::CALORIES;
    ret.weight = CreatureTestData::WEIGHT;

    return ret;
}

gamecomp::CreaturePsycheComponent MakeCreatureHelper::make_CreaturePsyche() {
    gamecomp::CreaturePsycheComponent ret;

    ret.disc = 100;
    ret.luck = 100;

    return ret;
}

gamecomp::CreatureLifeComponent MakeCreatureHelper::make_CreatureLife() {
    gamecomp::CreatureLifeComponent ret;

    ret.name = "Testmon";

    ret.born = true;
    ret.birthday = CreatureTestData::make_time_point_01_01_2000();

    ret.causeofdeath = gamecomp::CauseOfDeath::Alive;
    ret.causeofrunaway = gamecomp::CauseOfRunAway::NotRunAway;
    ret.isdead = false;

    ret.creaturelevel = CreatureTestData::CREATURELEVEL;

    ret.maxlifetime = CreatureTestData::TOTALMAXLIFETIME;
    ret.lifetime = CreatureTestData::LIFETIME;
    ret.ageingtime = CreatureTestData::AGEINGTIME;
    ret.age = CreatureTestData::AGE;

    ret.oldlevel = CreatureTestData::LVL;

    ret.hasstatus.fill(false);
    ret.isbusy = false;

    return ret;
}



gameentity::Entity MakeCreatureHelper::create_Entity_Creature(
    gameentity::EntityManager& entities) {

    auto entity = entities.create();

    entity.assign<gamecomp::CreatureDataComponent>(make_CreatureData());
    entity.assign<gamecomp::CreatureProgressTimersComponent>(
        make_CreatureProgressTimers());

    entity.assign<gamecomp::BattlerStatusesComponent>(make_BattlerStatuses());
    entity.assign<gamecomp::BattlerBattleStateComponent>(
        make_BattlerBattleState());
    entity.assign<gamecomp::BattlerResistsComponent>(make_BattlerResists());
    entity.assign<gamecomp::CreatureBattlerComponent>(make_CreatureBattler());

    entity.assign<gamecomp::CreatureBattlerGeneComponent>(
        make_CreatureBattlerGene());
    entity.assign<gamecomp::CreatureGeneComponent>(make_CreatureGene());

    entity.assign<gamecomp::CreatureMemoryComponent>(make_CreatureMemory());
    entity.assign<gamecomp::CreaturePersonalityComponent>(
        make_CreaturePersonality());

    entity.assign<gamecomp::CreatureHungerComponent>(make_CreatureHunger());
    entity.assign<gamecomp::CreatureEvolveComponent>(make_CreatureEvolve());
    entity.assign<gamecomp::CreatureSleepComponent>(make_CreatureSleep());
    entity.assign<gamecomp::CreatureTrainingComponent>(make_CreatureTraining());
    entity.assign<gamecomp::CreatureBodilyStateComponent>(
        make_CreatureBodilyState());
    entity.assign<gamecomp::CreatureBodyComponent>(make_CreatureBody());
    entity.assign<gamecomp::CreaturePsycheComponent>(make_CreaturePsyche());
    entity.assign<gamecomp::CreatureLifeComponent>(make_CreatureLife());

    return entity;
}


gameentity::Entity MakeCreatureHelper::create_Entity_CreatureAllWaitTime(
    gameentity::EntityManager& entities, std::chrono::milliseconds waittime) {

    auto entity = create_Entity_Creature(entities);
    auto creaturelevel = CreatureTestData::CREATURELEVEL;


    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();

    for (auto timertype : earr::Enum<gamecomp::CreatureProgressTimer>()) {
        earr::enum_array_at(
            earr::enum_array_at(timers->timer, timertype).waittime,
            creaturelevel) = waittime;
    }
    for (auto timertype_callback :
         earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
        earr::enum_array_at(
            earr::enum_array_at(timers->callback, timertype_callback)
                .base.waittime,
            creaturelevel) = waittime;
    }
    for (auto timertype_increment :
         earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
        earr::enum_array_at(
            earr::enum_array_at(timers->increment, timertype_increment)
                .base.waittime,
            creaturelevel) = waittime;
    }

    return entity;
}


gameentity::Entity
MakeCreatureHelper::create_Entity_CreatureAllWaitTime_Starvation(
    gameentity::EntityManager& entities, std::chrono::milliseconds waittime) {

    auto entity = create_Entity_Creature(entities);
    auto creaturelevel = CreatureTestData::CREATURELEVEL;


    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();

    for (auto timertype : earr::Enum<gamecomp::CreatureProgressTimer>()) {
        earr::enum_array_at(
            earr::enum_array_at(timers->timer, timertype).waittime,
            creaturelevel) = waittime;
    }
    for (auto timertype_callback :
         earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
        earr::enum_array_at(
            earr::enum_array_at(timers->callback, timertype_callback)
                .base.waittime,
            creaturelevel) = waittime;
    }
    for (auto timertype_increment :
         earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
        earr::enum_array_at(
            earr::enum_array_at(timers->increment, timertype_increment)
                .base.waittime,
            creaturelevel) = waittime;
    }
    for (auto starvationphase : earr::Enum<gamecomp::StarvationPhase>()) {
        earr::enum_array_at(
            earr::enum_array_at(timers->starvation, starvationphase)
                .base.waittime,
            creaturelevel) = waittime;
    }

    return entity;
}