#include "SystemGameTestMakeCreatureEvolutionHelper.h"


gamecomp::CreatureDataComponent MakeCreatureEvolutionHelper::make_CreatureData() {
    gamecomp::CreatureDataComponent ret;

    data::Creature creature = CreatureTestEvolution::make_DataCreature_Egg();

    ret.creature = creature;

    return ret;
}

gamecomp::CreatureProgressTimersComponent MakeCreatureEvolutionHelper::make_CreatureProgressTimers() {
    gamecomputil::ProgressTimerUtil progresstimer_util;
    computil::DateTimerUtil datetimer_util;

    gamecomp::CreatureProgressTimersComponent ret;
    ret.creaturelevel = CreatureTestEvolutionEgg::CREATURELEVEL;
    auto time = CreatureTestEvolution::make_time_point_01_01_2000();
    float factor = 1.0f;

    for (auto timertype : earr::Enum<gamecomp::CreatureProgressTimer>()) {
        progresstimer_util.init(earr::enum_array_at(ret.timer, timertype), time,
                                factor);
    }
    for (auto timertype_callback :
         earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
        progresstimer_util.init(earr::enum_array_at(ret.callback, timertype_callback),
                                time, factor);
    }
    for (auto timertype_increment :
         earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
        progresstimer_util.init(
            earr::enum_array_at(ret.increment, timertype_increment), time, factor);
    }


    datetimer_util.init(ret.lifetimer, time, factor);
    datetimer_util.start(ret.lifetimer);

    return ret;
}

gamecomp::BattlerStatusesComponent MakeCreatureEvolutionHelper::make_BattlerStatuses() {
    gamecomp::BattlerStatusesComponent ret;

    return ret;
}

gamecomp::BattlerBattleStateComponent MakeCreatureEvolutionHelper::make_BattlerBattleState() {
    gamecomp::BattlerBattleStateComponent ret;

    return ret;
}

gamecomp::BattlerResistsComponent MakeCreatureEvolutionHelper::make_BattlerResists() {
    gamecomp::BattlerResistsComponent ret;

    return ret;
}

gamecomp::CreatureBattlerComponent MakeCreatureEvolutionHelper::make_CreatureBattler() {
    gamecomp::CreatureBattlerComponent ret;

    earr::enum_array_at(ret.attrbase, +data::Attribute::MaxHP) =
        CreatureTestEvolutionEgg::MAXHP;
    earr::enum_array_at(ret.attrbase, +data::Attribute::MaxMP) =
        CreatureTestEvolutionEgg::MAXMP;
    earr::enum_array_at(ret.attrbase, +data::Attribute::Atk) =
        CreatureTestEvolutionEgg::ATK;
    earr::enum_array_at(ret.attrbase, +data::Attribute::Def) =
        CreatureTestEvolutionEgg::DEF;
    earr::enum_array_at(ret.attrbase, +data::Attribute::Agi) =
        CreatureTestEvolutionEgg::AGI;
    earr::enum_array_at(ret.attrbase, +data::Attribute::Int) =
        CreatureTestEvolutionEgg::INT;
    earr::enum_array_at(ret.attrbase, +data::Attribute::Exp) =
        CreatureTestEvolutionEgg::EXP;

    earr::enum_array_at(ret.attrinf, +data::Attribute::MaxHP) =
        CreatureTestEvolutionEgg::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::MaxMP) =
        CreatureTestEvolutionEgg::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::Atk) =
        CreatureTestEvolutionEgg::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::Def) =
        CreatureTestEvolutionEgg::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::Agi) =
        CreatureTestEvolutionEgg::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::Int) =
        CreatureTestEvolutionEgg::ATTR_INFLATION;
    earr::enum_array_at(ret.attrinf, +data::Attribute::Exp) =
        CreatureTestEvolutionEgg::ATTR_INFLATION;

    earr::enum_array_at(ret.attrplus, +data::Attribute::MaxHP) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::MaxMP) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::Atk) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::Def) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::Agi) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::Int) = 0;
    earr::enum_array_at(ret.attrplus, +data::Attribute::Exp) = 0;

    earr::enum_array_at(ret.attr, +data::Attribute::MaxHP) =
        CreatureTestEvolutionEgg::MAXHP;
    earr::enum_array_at(ret.attr, +data::Attribute::MaxMP) =
        CreatureTestEvolutionEgg::MAXMP;
    earr::enum_array_at(ret.attr, +data::Attribute::Atk) =
        CreatureTestEvolutionEgg::ATK;
    earr::enum_array_at(ret.attr, +data::Attribute::Def) =
        CreatureTestEvolutionEgg::DEF;
    earr::enum_array_at(ret.attr, +data::Attribute::Agi) =
        CreatureTestEvolutionEgg::AGI;
    earr::enum_array_at(ret.attr, +data::Attribute::Int) =
        CreatureTestEvolutionEgg::INT;
    earr::enum_array_at(ret.attr, +data::Attribute::Exp) =
        CreatureTestEvolutionEgg::EXP;


    // set level 1
    ret.exp = 0;
    ret.lvl = CreatureTestEvolutionEgg::LVL;

    ret.hp = CreatureTestEvolutionEgg::MAXHP;
    ret.mp = CreatureTestEvolutionEgg::MAXMP;


    // set attributes for 5 Levels, Index 0-5 => 5 Levels
    earr::enum_array_at(ret.attrparam, +data::Attribute::MaxHP) = {
        0, CreatureTestEvolutionEgg::MAXHP,
        CreatureTestEvolutionEgg::MAXHP +
            CreatureTestEvolutionEgg::ATTR_INFLATION,
        CreatureTestEvolutionEgg::MAXHP +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 2,
        CreatureTestEvolutionEgg::MAXHP +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 3,
        CreatureTestEvolutionEgg::MAXMP +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 4
    };

    earr::enum_array_at(ret.attrparam, +data::Attribute::MaxMP) = {
        0, CreatureTestEvolutionEgg::MAXMP,
        CreatureTestEvolutionEgg::MAXMP +
            CreatureTestEvolutionEgg::ATTR_INFLATION,
        CreatureTestEvolutionEgg::MAXMP +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 2,
        CreatureTestEvolutionEgg::MAXMP +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 3,
        CreatureTestEvolutionEgg::MAXMP +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 4
    };

    earr::enum_array_at(ret.attrparam, +data::Attribute::Atk) = {
        0, CreatureTestEvolutionEgg::ATK,
        CreatureTestEvolutionEgg::ATK +
            CreatureTestEvolutionEgg::ATTR_INFLATION,
        CreatureTestEvolutionEgg::ATK +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 2,
        CreatureTestEvolutionEgg::ATK +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 3,
        CreatureTestEvolutionEgg::ATK +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 4
    };

    earr::enum_array_at(ret.attrparam, +data::Attribute::Def) = {
        0, CreatureTestEvolutionEgg::DEF,
        CreatureTestEvolutionEgg::DEF +
            CreatureTestEvolutionEgg::ATTR_INFLATION,
        CreatureTestEvolutionEgg::DEF +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 2,
        CreatureTestEvolutionEgg::DEF +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 3,
        CreatureTestEvolutionEgg::DEF +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 4
    };

    earr::enum_array_at(ret.attrparam, +data::Attribute::Agi) = {
        0, CreatureTestEvolutionEgg::AGI,
        CreatureTestEvolutionEgg::AGI +
            CreatureTestEvolutionEgg::ATTR_INFLATION,
        CreatureTestEvolutionEgg::AGI +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 2,
        CreatureTestEvolutionEgg::AGI +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 3,
        CreatureTestEvolutionEgg::AGI +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 4
    };

    earr::enum_array_at(ret.attrparam, +data::Attribute::Exp) = {
        0, CreatureTestEvolutionEgg::EXP,
        CreatureTestEvolutionEgg::EXP +
            CreatureTestEvolutionEgg::ATTR_INFLATION,
        CreatureTestEvolutionEgg::EXP +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 2,
        CreatureTestEvolutionEgg::EXP +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 3,
        CreatureTestEvolutionEgg::EXP +
            CreatureTestEvolutionEgg::ATTR_INFLATION * 4
    };

    return ret;
}

gamecomp::CreatureBattlerGeneComponent MakeCreatureEvolutionHelper::make_CreatureBattlerGene() {
    gamecomp::CreatureBattlerGeneComponent ret;

    ret.boniattrfactor.fill(0);
    ret.boniattrinflation.fill(0);

    return ret;
}

gamecomp::CreatureGeneComponent MakeCreatureEvolutionHelper::make_CreatureGene() {
    gamecomp::CreatureGeneComponent ret;

    auto creaturelevel = CreatureTestEvolutionEgg::CREATURELEVEL;

    ret.generationnr = 1;

    ret.gender = CreatureTestEvolutionEgg::GENDER;
    ret.min_bmi = CreatureTestEvolutionEgg::MIN_BMI;
    ret.ideal_bmi = CreatureTestEvolutionEgg::IDEAL_BMI;
    ret.max_bmi = CreatureTestEvolutionEgg::MAX_BMI;
    ret.max_bodysize = CreatureTestEvolutionEgg::MAX_BODYSIZE_GENE;
    ret.bodymass = CreatureTestEvolutionEgg::BODYMASS;

    ret.cangosleep_at_tired = CreatureTestEvolutionEgg::CANGOSLEEP_AT_TIRED;
    ret.max_digestionheap = CreatureTestEvolutionEgg::MAX_DIGESTIONHEAP;

    auto& perevolution = earr::enum_array_at(ret.perevolution, creaturelevel);

    perevolution.needsleepinpercent = CreatureTestEvolutionEgg::NEEDSLEEPINPERCENT;
    perevolution.needrestinhospitalinpercent = CreatureTestEvolutionEgg::NEEDRESTINHOSPITALINPERCENT;

    ret.totalmaxlifetime = CreatureTestEvolutionEgg::TOTALMAXLIFETIME;

    auto& training = perevolution.training;
    
    training.good_trainitime = CreatureTestEvolutionEgg::GOOD_TRAINTIME;
    training.middle_trainitime = CreatureTestEvolutionEgg::MIDDLE_TRAINTIME;
    training.min_trainitime = CreatureTestEvolutionEgg::MIN_TRAINTIME;

    training.max_hungryoverlay_intraining =
        CreatureTestEvolutionEgg::MAX_HUNGRYOVERLAY_INTRAINING;
    training.max_thirstyoverlay_intraining =
        CreatureTestEvolutionEgg::MAX_THIRSTYOVERLAY_INTRAINING;
    training.max_tiredoverlay_intraining =
        CreatureTestEvolutionEgg::MAX_TIREDOVERLAY_INTRAINING;

    return ret;
}


gamecomp::CreatureMemoryComponent MakeCreatureEvolutionHelper::make_CreatureMemory() {
    gamecomp::CreatureMemoryComponent ret;

    ret.max_short_memorysize = CreatureTestEvolutionEgg::MAX_SHORTMEMORY_SIZE;

    return ret;
}

gamecomp::CreaturePersonalityComponent MakeCreatureEvolutionHelper::make_CreaturePersonality() {
    gamecomp::CreaturePersonalityComponent ret;

    return ret;
}

gamecomp::CreatureHungerComponent MakeCreatureEvolutionHelper::make_CreatureHunger() {
    gamecomp::CreatureHungerComponent ret;

    ret.digestionheap = 0;
    ret.starvationphase = gamecomp::StarvationPhase::None;

    return ret;
}

gamecomp::CreatureEvolveComponent MakeCreatureEvolutionHelper::make_CreatureEvolve() {
    gamecomp::CreatureEvolveComponent ret;

    return ret;
}

gamecomp::CreatureSleepComponent MakeCreatureEvolutionHelper::make_CreatureSleep() {
    gamecomp::CreatureSleepComponent ret;

    return ret;
}

gamecomp::CreatureTrainingComponent MakeCreatureEvolutionHelper::make_CreatureTraining() {
    gamecomp::CreatureTrainingComponent ret;

    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::MaxHP) =
        CreatureTestEvolutionEgg::MAXHP;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::MaxMP) =
        CreatureTestEvolutionEgg::MAXMP;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Atk) =
        CreatureTestEvolutionEgg::ATK;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Def) =
        CreatureTestEvolutionEgg::DEF;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Agi) =
        CreatureTestEvolutionEgg::AGI;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Int) =
        CreatureTestEvolutionEgg::INT;
    earr::enum_array_at(ret.attrparam_befortrain, +data::Attribute::Exp) =
        CreatureTestEvolutionEgg::EXP;

    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::MaxHP) =
        CreatureTestEvolutionEgg::MAXHP;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::MaxMP) =
        CreatureTestEvolutionEgg::MAXMP;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Atk) =
        CreatureTestEvolutionEgg::ATK;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Def) =
        CreatureTestEvolutionEgg::DEF;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Agi) =
        CreatureTestEvolutionEgg::AGI;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Int) =
        CreatureTestEvolutionEgg::INT;
    earr::enum_array_at(ret.attrparam_aftertrain, +data::Attribute::Exp) =
        CreatureTestEvolutionEgg::EXP;

    ret.trainingcounter.fill(0);

    return ret;
}

gamecomp::CreatureBodilyStateComponent MakeCreatureEvolutionHelper::make_CreatureBodilyState() {
    gamecomp::CreatureBodilyStateComponent ret;

    ret.hurtcount = 0;
    ret.illcount = 0;

    return ret;
}

gamecomp::CreatureBodyComponent MakeCreatureEvolutionHelper::make_CreatureBody() {
    gamecomp::CreatureBodyComponent ret;

    ret.bmi = CreatureTestEvolutionEgg::BMI;
    ret.bodysize = CreatureTestEvolutionEgg::BODYSIZE;
    ret.calories = CreatureTestEvolutionEgg::CALORIES;
    ret.weight = CreatureTestEvolutionEgg::WEIGHT;

    return ret;
}

gamecomp::CreaturePsycheComponent MakeCreatureEvolutionHelper::make_CreaturePsyche() {
    gamecomp::CreaturePsycheComponent ret;

    ret.disc = 100;
    ret.luck = 100;

    return ret;
}

gamecomp::CreatureLifeComponent MakeCreatureEvolutionHelper::make_CreatureLife() {
    gamecomp::CreatureLifeComponent ret;

    ret.name = "Testmon";

    ret.born = false;
    ret.birthday = CreatureTestEvolution::make_time_point_01_01_2000();

    ret.causeofdeath = gamecomp::CauseOfDeath::Alive;
    ret.causeofrunaway = gamecomp::CauseOfRunAway::NotRunAway;
    ret.isdead = false;

    ret.creaturelevel = CreatureTestEvolutionEgg::CREATURELEVEL;

    ret.maxlifetime = CreatureTestEvolutionEgg::TOTALMAXLIFETIME;
    ret.lifetime = CreatureTestEvolutionEgg::LIFETIME;
    ret.ageingtime = CreatureTestEvolutionEgg::AGEINGTIME;
    ret.age = CreatureTestEvolutionEgg::AGE;

    ret.oldlevel = CreatureTestEvolutionEgg::LVL;

    ret.hasstatus.fill(false);
    ret.isbusy = false;

    return ret;
}






gameentity::Entity MakeCreatureEvolutionHelper::create_Entity_Creature(gameentity::EntityManager& entities) {

    auto entity = entities.create();

    entity.assign<gamecomp::CreatureDataComponent>( make_CreatureData() );
    entity.assign<gamecomp::CreatureProgressTimersComponent>( make_CreatureProgressTimers() );

    entity.assign<gamecomp::BattlerStatusesComponent>( make_BattlerStatuses() );
    entity.assign<gamecomp::BattlerBattleStateComponent>( make_BattlerBattleState() );
    entity.assign<gamecomp::BattlerResistsComponent>( make_BattlerResists() );
    entity.assign<gamecomp::CreatureBattlerComponent>( make_CreatureBattler() );

    entity.assign<gamecomp::CreatureBattlerGeneComponent>( make_CreatureBattlerGene() );
    entity.assign<gamecomp::CreatureGeneComponent>( make_CreatureGene() );

    entity.assign<gamecomp::CreatureMemoryComponent>( make_CreatureMemory() );
    entity.assign<gamecomp::CreaturePersonalityComponent>( make_CreaturePersonality() );

    entity.assign<gamecomp::CreatureHungerComponent>( make_CreatureHunger() );
    entity.assign<gamecomp::CreatureEvolveComponent>( make_CreatureEvolve() );
    entity.assign<gamecomp::CreatureSleepComponent>( make_CreatureSleep() );
    entity.assign<gamecomp::CreatureTrainingComponent>( make_CreatureTraining() );
    entity.assign<gamecomp::CreatureBodilyStateComponent>( make_CreatureBodilyState() );
    entity.assign<gamecomp::CreatureBodyComponent>( make_CreatureBody() );
    entity.assign<gamecomp::CreaturePsycheComponent>( make_CreaturePsyche() );
    entity.assign<gamecomp::CreatureLifeComponent>( make_CreatureLife() );

    return entity;
}


gameentity::Entity
MakeCreatureEvolutionHelper::create_Entity_CreatureAllWaitTime(gameentity::EntityManager& entities,
                                std::chrono::milliseconds waittime) {

    auto entity = create_Entity_Creature(entities);
    auto creaturelevel = CreatureTestEvolutionEgg::CREATURELEVEL;


    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();

    for (auto timertype : earr::Enum<gamecomp::CreatureProgressTimer>()) {
        earr::enum_array_at(earr::enum_array_at(timers->timer, timertype).waittime,
                    creaturelevel) = waittime;
    }
    for (auto timertype_callback :
        earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
        earr::enum_array_at(
            earr::enum_array_at(timers->callback, timertype_callback).base.waittime,
            creaturelevel) = waittime;
    }
    for (auto timertype_increment :
        earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
        earr::enum_array_at(
            earr::enum_array_at(timers->increment, timertype_increment).base.waittime,
            creaturelevel) = waittime;
    }

    return entity;
}


gameentity::Entity
MakeCreatureEvolutionHelper::create_Entity_CreatureAllWaitTime_Starvation(gameentity::EntityManager& entities,
                                std::chrono::milliseconds waittime) {

    auto entity = create_Entity_Creature(entities);
    auto creaturelevel = CreatureTestEvolutionEgg::CREATURELEVEL;


    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();

    for (auto timertype : earr::Enum<gamecomp::CreatureProgressTimer>()) {
        earr::enum_array_at(earr::enum_array_at(timers->timer, timertype).waittime,
                    creaturelevel) = waittime;
    }
    for (auto timertype_callback :
        earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
        earr::enum_array_at(earr::enum_array_at(timers->callback, timertype_callback).base.waittime,
            creaturelevel) = waittime;
    }
    for (auto timertype_increment :
        earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
        earr::enum_array_at(
            earr::enum_array_at(timers->increment, timertype_increment).base.waittime,
            creaturelevel) = waittime;
    }
    for (auto starvationphase :
        earr::Enum<gamecomp::StarvationPhase>()) {
        earr::enum_array_at(
            earr::enum_array_at(timers->starvation, starvationphase).base.waittime,
            creaturelevel) = waittime;
    }

    return entity;
}