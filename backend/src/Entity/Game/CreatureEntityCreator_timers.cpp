#include "Entity/Game/CreatureEntityCreator.h"

namespace gameentity {

gamecomp::CreatureProgressTimersComponent
CreatureEntityCreator::createCreatureProgressTimers(
    std::chrono::system_clock::time_point time, gamecomp::progresstimer_factor_t realtime_factor) {
    gamecomp::CreatureProgressTimersComponent ret;

    datetimer_util_.init(ret.lifetimer, time, realtime_factor);

    for (auto& timer : ret.timer) {
        progresstimer_util_.init(timer, time, realtime_factor);
    }
    for (auto& timer : ret.callback) {
        progresstimer_util_.init(timer, time, realtime_factor);
    }
    for (auto& timer : ret.increment) {
        progresstimer_util_.init(timer, time, realtime_factor);
    }

    for (auto& timer : ret.starvation) {
        progresstimer_util_.init(timer, time, realtime_factor);
    }

    for (auto& memory : ret.memory) {
        progresstimer_util_.init(memory.shortterm, time, realtime_factor);
        progresstimer_util_.init(memory.mediumterm, time, realtime_factor);
    }

    return ret;
}

void CreatureEntityCreator::setCreatureProgressTimersRealTime(
    gamecomp::CreatureProgressTimersComponent& timers,
    std::chrono::system_clock::time_point time, gamecomp::progresstimer_factor_t realtime_factor) {
    datetimer_util_.setRealTime(timers.lifetimer, time, realtime_factor);

    for (auto& timer : timers.timer) {
        datetimer_util_.setRealTime(timer.timer, time, realtime_factor);
    }
    for (auto& timer : timers.callback) {
        datetimer_util_.setRealTime(timer.base.timer, time, realtime_factor);
    }
    for (auto& timer : timers.increment) {
        datetimer_util_.setRealTime(timer.base.timer, time, realtime_factor);
    }

    for (auto& timer : timers.starvation) {
        datetimer_util_.setRealTime(timer.base.timer, time, realtime_factor);
    }

    for (auto& memory : timers.memory) {
        datetimer_util_.setRealTime(memory.shortterm.base.timer, time,
                                    realtime_factor);
        datetimer_util_.setRealTime(memory.mediumterm.base.timer, time,
                                    realtime_factor);
    }
}

void CreatureEntityCreator::setCreatureProgressTimersRealTimeFromLifetimer(
    gamecomp::CreatureProgressTimersComponent& timers) {
    auto time = std::chrono::system_clock::time_point() + timers.lifetimer.realtime;
    auto factor = timers.lifetimer.realtime_factor;

    setCreatureProgressTimersRealTime(timers, time, factor);
}

gamecomp::CreatureProgressTimersComponent
CreatureEntityCreator::createCreatureProgressTimersCreature(
    std::chrono::system_clock::time_point time, gamecomp::progresstimer_factor_t realtime_factor) {
    auto timers = createCreatureProgressTimers(time, realtime_factor);

    datetimer_util_.restart(timers.lifetimer);
    progresstimer_util_.restart(earr::enum_array_at(
        timers.timer, +gamecomp::CreatureProgressTimer::Evolution));

    return timers;
}


void CreatureEntityCreator::setupCreatureProgressTimers(
    gamecomp::CreatureProgressTimersComponent& timers,
    const data::Creature& creature, const gamecomp::CreatureLifeComponent& life,
    const gamecomp::CreatureGeneComponent& gene,
    const gamecomp::CreatureBodyComponent& body) {
    timers.creaturelevel = life.creaturelevel;

    auto maxbodysize =
        std::min<data::bodysize_t>(gene.max_bodysize, creature.getMaxBodySize());

    auto& growing_timer = earr::enum_array_at(timers.increment, 
        +gamecomp::CreatureProgressTimerIncrement::Growing);

    growing_timer.addvalue_per_percent = (maxbodysize - body.bodysize) / 100.0;

    auto& illbyOverweight_timer = earr::enum_array_at(
        timers.callback,
        +gamecomp::CreatureProgressTimerCallback::IllbyOverweight);
    illbyOverweight_timer.isendless = true;

    auto& lostweighthungry_timer = earr::enum_array_at(
        timers.increment,
        +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerHungry);
    lostweighthungry_timer.isendless = true;

    auto& lostweighthirsty_timer = earr::enum_array_at(
        timers.increment,
        +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerThirsty);
    lostweighthirsty_timer.isendless = true;

    auto& lostcalories_timer = earr::enum_array_at(
        timers.increment,
        +gamecomp::CreatureProgressTimerIncrement::LostCalories);
    lostcalories_timer.isendless = true;

    auto& gainweightcalories_timer = earr::enum_array_at(
        timers.increment,
        +gamecomp::CreatureProgressTimerIncrement::GainWeightCalories);
    gainweightcalories_timer.isendless = true;

    auto& hurtToDead_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::HurtToDead);
    hurtToDead_timer.isendless = true;

    auto& hurtLostHP_timer = earr::enum_array_at(
        timers.increment,
        +gamecomp::CreatureProgressTimerIncrement::HurtLostHP);
    hurtLostHP_timer.isendless = true;

    auto& illToDead_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::IllToDead);
    illToDead_timer.isendless = true;

    auto& digestion_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::Digestion);
    digestion_timer.isendless = true;

    auto& pauseDigestionHungry_timer = earr::enum_array_at(
        timers.callback,
        +gamecomp::CreatureProgressTimerCallback::PauseDigestionHungry);
    pauseDigestionHungry_timer.isendless = true;

    auto& fullDigestionHeap_timer = earr::enum_array_at(
        timers.callback,
        +gamecomp::CreatureProgressTimerCallback::FullDigestionHeap);
    fullDigestionHeap_timer.isendless = true;


    for (auto creature_level : earr::Enum<data::CreatureLevel>()) {
        auto& gene_perevolution =
            earr::enum_array_at(gene.perevolution, creature_level);

        for (auto index : earr::Enum<gamecomp::CreatureProgressTimer>()) {
            getCreatureProgressTimersWaitTime(timers.timer, index,
                                              creature_level) =
                earr::enum_array_at(gene_perevolution.waittime.timer, index);
        }

        for (auto index :
             earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
            getCreatureProgressTimersWaitTime(timers.callback, index,
                                              creature_level) =
                earr::enum_array_at(gene_perevolution.waittime.callback, index);
        }

        for (auto index :
             earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
            getCreatureProgressTimersWaitTime(timers.increment, index,
                                              creature_level) =
                earr::enum_array_at(gene_perevolution.waittime.increment,
                                    index);
        }

        for (auto index : earr::Enum<gamecomp::StarvationPhase>()) {
            getCreatureProgressTimersWaitTime(timers.starvation, index,
                                              creature_level) =
                earr::enum_array_at(gene_perevolution.waittime.starvation,
                                    index);
        }

        for (auto index : earr::Enum<gamecomp::CreatureActivity>()) {
            earr::enum_array_at(earr::enum_array_at(timers.memory, index)
                                    .shortterm.base.waittime,
                                creature_level) =
                earr::enum_array_at(gene_perevolution.waittime.shorttermmemory,
                                    index);

            earr::enum_array_at(earr::enum_array_at(timers.memory, index)
                                    .mediumterm.base.waittime,
                                creature_level) =
                earr::enum_array_at(gene_perevolution.waittime.mediumtermmemory,
                                    index);
        }
    }
}
} // namespace gameentity
