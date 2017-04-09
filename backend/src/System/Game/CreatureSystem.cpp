#include "System/Game/CreatureSystem.h"

namespace gamesystem {


CreatureSystem::CreatureSystem(gameentity::DataManager& datamanager)
    : datamanager_(datamanager) {}



void CreatureSystem::updateUnhappy(
    EventBus& events, Entity entity,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life) {
    data::CreatureLevel creaturelevel = life.creaturelevel;

    auto& unhappy_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::Unhappy);
    gamecomp::ProgressTimer& unhappy_progresstimer = unhappy_timer.base;

    auto& runawayunhappy_timer = earr::enum_array_at(
        timers.callback,
        +gamecomp::CreatureProgressTimerCallback::RunAwayUnhappy);
    gamecomp::ProgressTimer& runawayunhappy_progresstimer =
        runawayunhappy_timer.base;

    auto waittime = earr::enum_array_at(runawayunhappy_progresstimer.waittime,
                                        creaturelevel);

    progresstimer_util_.restart(runawayunhappy_progresstimer);
    progresstimer_util_.stop(unhappy_progresstimer);

    emit_event<gameevent::CreatureMakeRunAwayEvent>(
        events, entity, +gamecomp::CauseOfRunAway::Unhappy, waittime);
}

void CreatureSystem::updateBored(
    EventBus& events, Entity entity,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life) {

    auto& bored_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::Bored);
    gamecomp::ProgressTimer& bored_progresstimer = bored_timer.base;

    if (bored_progresstimer.isfull) {
        life.bored = true;
    } else {
        life.bored = false;
    }

    if (!life.isbusy && !bored_progresstimer.timer.isstart) {
        progresstimer_util_.start(bored_progresstimer);
        emit_event<gameevent::CreatureDoActivityEvent>(
            events, entity, gamecomp::CreatureActivity::Born);
    } else {
        progresstimer_util_.stop(bored_progresstimer);
    }
}

void CreatureSystem::updateLuck(
    EventBus& events, Entity entity,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreaturePsycheComponent& psyche,
    gamecomp::CreatureLifeComponent& life) {

    auto& unluck_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::Unhappy);
    gamecomp::ProgressTimer& unluck_progresstimer = unluck_timer.base;
    // double unluck_value = unluck_progresstimer.value;
    // double unluck_overlayvalue = unluck_progresstimer.overlayvalue;

    auto luck = psyche.luck;
    bool ishappy = luck >= 100.0;
    bool isunhappy = luck <= 0.0;


    if (ishappy &&
        !earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Happy)) {
        emit_event<gameevent::CreatureAddStatusEvent>(
            events, entity, data::CreatureStatus::Happy);
    } else if (earr::enum_array_at(life.hasstatus,
                                   +data::CreatureStatus::Happy)) {
        emit_event<gameevent::CreatureRemoveStatusEvent>(
            events, entity, data::CreatureStatus::Happy);
    }

    if (isunhappy &&
        !earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Happy)) {
        emit_event<gameevent::CreatureAddStatusEvent>(
            events, entity, data::CreatureStatus::Unhappy);
    } else if (earr::enum_array_at(life.hasstatus,
                                   +data::CreatureStatus::Happy)) {
        emit_event<gameevent::CreatureRemoveStatusEvent>(
            events, entity, data::CreatureStatus::Unhappy);
    }

    if (isunhappy && !unluck_progresstimer.timer.isstart) {
        progresstimer_util_.start(unluck_progresstimer);
    } else {
        progresstimer_util_.stop(unluck_progresstimer);
    }
}


void CreatureSystem::updateHasStatuses(
    gamecomp::BattlerStatusesComponent& battlerstatuses,
    gamecomp::CreatureLifeComponent& life) {
    auto& statuses = battlerstatuses.statuses_name;

    life.hasstatus.fill(false);
    for (auto status_name : statuses) {
        auto creaturestatus =
            this->datamanager_.findCreatureBattlerStatus(status_name);

        if (creaturestatus &&
            creaturestatus->getCreatureStatus() !=
                +data::CreatureStatus::Normal) {
            earr::enum_array_at(life.hasstatus,
                                creaturestatus->getCreatureStatus()) = true;
        }
    }
}

void CreatureSystem::updateBMI(gamecomp::CreatureBodyComponent& body,
                               gamecomp::CreatureGeneComponent& gene,
                               gamecomp::CreatureDataComponent& creature_data) {
    body.bmi =
        gameentity::CreatureEntityCreator::getBMI(creature_data, gene, body);
}


void CreatureSystem::updateLifeAttribute(
    EventBus& events, Entity entity,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life,
    gamecomp::CreatureGeneComponent& gene,
    gamecomp::CreatureBattlerComponent& creature_battler,
    gamecomp::CreatureDataComponent& creature_data) {

    const auto& creature = creature_data.creature;

    life.creaturelevel = creature.getCreatureLevel();

    auto& gene_perevolution =
        earr::enum_array_at(gene.perevolution, life.creaturelevel);
    auto& gene_training = gene_perevolution.training;


    if (life.oldlevel != creature_battler.lvl) {
        emit_event<gameevent::CreatureHasLevelUpEvent>(
            events, entity, life.oldlevel, creature_battler.lvl);
        life.oldlevel = creature_battler.lvl;
    }

    life.lifetime = datetimer_util_.getTime(timers.lifetimer);

    auto ageingtime_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(life.ageingtime)
            .count();
    auto lifetime_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(life.lifetime)
            .count();

    life.age = (ageingtime_ms > 0)
                   ? static_cast<gamecomp::age_t>(lifetime_ms / ageingtime_ms)
                   : 0;

    if (!life.isdead) {
        if (life.lifetime > life.maxlifetime) {
            emit_event<gameevent::CreatureMakeDeadEvent>(
                events, entity, gamecomp::CauseOfDeath::Senility);
        } else if (creature_battler.hp <= 0 && !life.inbattle) {
            emit_event<gameevent::CreatureMakeDeadEvent>(
                events, entity, gamecomp::CauseOfDeath::ZeroHP);
        }
    }

    life.caneat = !life.isbusy && !life.isdead && life.born;
    life.candrink = !life.isbusy && !life.isdead && life.born;


    auto& hungry_timer = earr::enum_array_at(
        timers.timer, +gamecomp::CreatureProgressTimer::Hungry);
    gamecomp::ProgressTimer& hungry_progresstimer = hungry_timer;
    auto hungry_value = hungry_progresstimer.value;

    auto& thirsty_timer = earr::enum_array_at(
        timers.timer, +gamecomp::CreatureProgressTimer::Thirsty);
    gamecomp::ProgressTimer& thirsty_progresstimer = thirsty_timer;
    auto thirsty_value = thirsty_progresstimer.value;

    auto& tired_timer = earr::enum_array_at(
        timers.timer, +gamecomp::CreatureProgressTimer::Tired);
    gamecomp::ProgressTimer& tired_progresstimer = tired_timer;
    auto tired_value = tired_progresstimer.value;

    life.cantrain =
        !life.isbusy && !life.isdead && life.born &&
        !earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Ill) &&
        !earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Hurt) &&
        hungry_value <= gene_training.cantrain_with_max_hungry &&
        thirsty_value <= gene_training.cantrain_with_max_thirsty &&
        tired_value <= gene_training.cantrain_with_max_tired;
}


void CreatureSystem::updateCanGoSleep(
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life,
    gamecomp::CreatureGeneComponent& gene,
    gamecomp::CreatureSleepComponent& sleep) {

    auto& tired_timer = earr::enum_array_at(
        timers.timer, +gamecomp::CreatureProgressTimer::Tired);
    gamecomp::ProgressTimer& tired_progresstimer = tired_timer;
    auto tired_value = tired_progresstimer.value;

    sleep.cangosleep = !life.isbusy && tired_value >= gene.cangosleep_at_tired;
}



void CreatureSystem::updatePsycheValues(
    gamecomp::CreaturePsycheComponent& psyche) {
    psyche.luck = clamp(psyche.luck, 0.0, 100.0);
    psyche.disc = clamp(psyche.disc, 0.0, 100.0);
}



void CreatureSystem::updateCreatureTimers(
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life) {
    timers.creaturelevel = life.creaturelevel;

    auto needrefreshin = life.maxlifetime;

    for (auto& timer : timers.timer) {
        if (timer.timer.isstart) {
            needrefreshin = std::min(
                needrefreshin,
                earr::enum_array_at(timer.waittime, timers.creaturelevel));
        }
    }

    for (auto& timer : timers.callback) {
        if (timer.base.timer.isstart) {
            needrefreshin = std::min(
                needrefreshin,
                earr::enum_array_at(timer.base.waittime, timers.creaturelevel));
        }
    }

    for (auto& timer : timers.increment) {
        if (timer.base.timer.isstart) {
            needrefreshin = std::min(
                needrefreshin,
                earr::enum_array_at(timer.base.waittime, timers.creaturelevel));
        }
    }

    for (auto& timer : timers.starvation) {
        if (timer.base.timer.isstart) {
            needrefreshin = std::min(
                needrefreshin,
                earr::enum_array_at(timer.base.waittime, timers.creaturelevel));
        }
    }

    for (auto& timer : timers.memory) {
        if (timer.shortterm.base.timer.isstart) {
            needrefreshin =
                std::min(needrefreshin,
                         earr::enum_array_at(timer.shortterm.base.waittime,
                                             timers.creaturelevel));
        }

        if (timer.mediumterm.base.timer.isstart) {
            needrefreshin =
                std::min(needrefreshin,
                         earr::enum_array_at(timer.shortterm.base.waittime,
                                             timers.creaturelevel));
        }
    }

    life.needrefreshin = needrefreshin;
}


void CreatureSystem::updateCreatureTimersFactor(
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureLifeComponent& life) {

    //auto isrunaway =
    //    earr::enum_array_at(life.hasstatus, +data::CreatureStatus::RunAway);
    //auto isinhospital =
    //    earr::enum_array_at(life.hasstatus, +data::CreatureStatus::InHospital);

    auto issleep =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Sleep);
    auto isrestinhospital = earr::enum_array_at(
        life.hasstatus, +data::CreatureStatus::RestInHospital);
    auto isrest =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Rest);

    auto istraining =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Training);

    auto ishungry =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Hungry);
    auto isthirsty =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Thirsty);
    auto isreplete =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Replete);

    auto isill =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Ill);
    auto ishurt =
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Hurt);

    auto isasleep = issleep || isrestinhospital || isrest;
    auto ishurtill = isill || ishurt;


    auto& hungry_timer = earr::enum_array_at(
        timers.timer, +gamecomp::CreatureProgressTimer::Hungry);
    gamecomp::ProgressTimer& hungry_progresstimer = hungry_timer;

    auto& thirsty_timer = earr::enum_array_at(
        timers.timer, +gamecomp::CreatureProgressTimer::Thirsty);
    gamecomp::ProgressTimer& thirsty_progresstimer = thirsty_timer;

    auto& tired_timer = earr::enum_array_at(
        timers.timer, +gamecomp::CreatureProgressTimer::Tired);
    gamecomp::ProgressTimer& tired_progresstimer = tired_timer;

    auto& digestion_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::Digestion);
    gamecomp::ProgressTimer& digestion_progresstimer = digestion_timer.base;

    auto& hurttodead_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::HurtToDead);
    gamecomp::ProgressTimer& hurttodead_progresstimer = hurttodead_timer.base;

    auto& illtodead_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::IllToDead);
    gamecomp::ProgressTimer& illtodead_progresstimer = illtodead_timer.base;

    auto& evolution_timer = earr::enum_array_at(
        timers.timer, +gamecomp::CreatureProgressTimer::Evolution);
    gamecomp::ProgressTimer& evolution_progresstimer = evolution_timer;


    tired_progresstimer.factor = 1.0;
    hungry_progresstimer.factor = 1.0;
    thirsty_progresstimer.factor = 1.0;
    digestion_progresstimer.factor = 1.0;
    hurttodead_progresstimer.factor = 1.0;
    illtodead_progresstimer.factor = 1.0;
    evolution_progresstimer.factor = 1.0;

    if (isasleep) {
        hungry_progresstimer.factor *= 0.75;
        thirsty_progresstimer.factor *= 0.75;
        digestion_progresstimer.factor *= 0.10;
    }

    if (istraining) {
        hungry_progresstimer.factor *= 1.05;
        thirsty_progresstimer.factor *= 1.08;
        digestion_progresstimer.factor *= 1.01;

        hurttodead_progresstimer.factor *= 1.005;
        illtodead_progresstimer.factor *= 1.005;
        evolution_progresstimer.factor *= 1.001;
    }

    if (ishurtill) {
        hungry_progresstimer.factor *= 0.995;
        thirsty_progresstimer.factor *= 0.998;
        digestion_progresstimer.factor *= 1.001;

        evolution_progresstimer.factor *= 0.995;
    }

    if (ishungry) {
        digestion_progresstimer.factor *= 0.95;
    }
    if (isthirsty) {
        digestion_progresstimer.factor *= 0.98;
    }
    if (isreplete) {
        tired_progresstimer.factor *= 1.05;
    }

    tired_progresstimer.factor = (isasleep)
                                     ? -std::abs(tired_progresstimer.factor)
                                     : std::abs(tired_progresstimer.factor);
}

void CreatureSystem::update(EntityManager& entities, EventBus& events,
                            TimeDelta /*dt*/) {

    Component<gamecomp::CreatureProgressTimersComponent> timers;
    Component<gamecomp::CreaturePsycheComponent> psyche;
    Component<gamecomp::CreatureLifeComponent> life;
    Component<gamecomp::CreatureBodyComponent> body;
    Component<gamecomp::CreatureGeneComponent> gene;
    Component<gamecomp::CreatureSleepComponent> sleep;
    Component<gamecomp::CreatureDataComponent> creature_data;
    Component<gamecomp::CreatureBattlerComponent> creature_battler;
    Component<gamecomp::BattlerStatusesComponent> battler_statuses;

    for (auto entity : entities.entities_with_components(
             timers, psyche, life, body, gene, sleep, creature_data,
             creature_battler, battler_statuses)) {
        updateCreatureTimers(*timers.get(), *life.get());
        updateCreatureTimersFactor(*timers.get(), *life.get());

        updateHasStatuses(*battler_statuses.get(), *life.get());
        updateBMI(*body.get(), *gene.get(), *creature_data.get());

        updatePsycheValues(*psyche.get());
        updateCanGoSleep(*timers.get(), *life.get(), *gene.get(), *sleep.get());
        updateLifeAttribute(events, entity, *timers.get(), *life.get(),
                            *gene.get(), *creature_battler.get(),
                            *creature_data.get());
    }
}

} // namespace gamesystem
