#include "System/Game/CreatureBornListener.h"

namespace gamesystem {

constexpr gamecomp::progresstimer_percent_t CreatureBornListener::GROWING_PROGRESS_AFTER_BORN_PERCENT;


CreatureBornListener::CreatureBornListener(gameentity::DataManager& datamanager)
    : datamanager_(datamanager)
{}



void CreatureBornListener::born(gameentity::Entity entity, EventBus& events,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureTrainingComponent& training,
    gamecomp::CreatureGeneComponent& gene, gamecomp::CreatureBodyComponent& body,
    gamecomp::CreatureBodilyStateComponent& bodilystate,
    gamecomp::CreatureLifeComponent& life) {

    auto& hungry_timer = earr::enum_array_at(timers.timer, +gamecomp::CreatureProgressTimer::Hungry);
    gamecomp::ProgressTimer& hungry_progresstimer = hungry_timer;

    auto& thristy_timer = earr::enum_array_at(timers.timer, +gamecomp::CreatureProgressTimer::Thirsty);
    gamecomp::ProgressTimer& thristy_progresstimer = thristy_timer;

    auto& evolution_timer = earr::enum_array_at(timers.timer, +gamecomp::CreatureProgressTimer::Evolution);
    gamecomp::ProgressTimer& evolution_progresstimer = evolution_timer;


    auto& growing_timer = earr::enum_array_at(timers.increment, +gamecomp::CreatureProgressTimerIncrement::Growing);
    gamecomp::ProgressTimer& growing_progresstimer = growing_timer.base;

    auto& lostcalories_timer = earr::enum_array_at(timers.increment, +gamecomp::CreatureProgressTimerIncrement::LostCalories);
    gamecomp::ProgressTimer& lostcalories_progresstimer = lostcalories_timer.base;

    auto& gainweightcalories_timer = earr::enum_array_at(timers.increment, +gamecomp::CreatureProgressTimerIncrement::GainWeightCalories);
    gamecomp::ProgressTimer& gainweightcalorie_progresstimer = gainweightcalories_timer.base;


    auto& digestion_timer = earr::enum_array_at(timers.callback, +gamecomp::CreatureProgressTimerCallback::Digestion);
    gamecomp::ProgressTimer& digestion_progresstimer = digestion_timer.base;



    emit_event<gameevent::CreatureRemoveStatusEvent>(events, entity, +data::CreatureStatus::Dead);
    emit_event<gameevent::CreatureRemoveRunAwayEvent>(events, entity);

    progresstimer_util_.restart(hungry_progresstimer);
    progresstimer_util_.restart(thristy_progresstimer);
    progresstimer_util_.restart(growing_progresstimer);
    progresstimer_util_.restart(lostcalories_progresstimer);
    progresstimer_util_.restart(gainweightcalorie_progresstimer);
    progresstimer_util_.restart(digestion_progresstimer);

    progresstimer_util_.restart(evolution_progresstimer);

    datetimer_util_.restart(timers.lifetimer);

    bodilystate.hurtcount = 0;
    bodilystate.illcount = 0;

    body.bodysize = gene.max_bodysize * (GROWING_PROGRESS_AFTER_BORN_PERCENT/100.0);
    growing_progresstimer.value = GROWING_PROGRESS_AFTER_BORN_PERCENT;

    body.weight = gene.min_weight * ((gene.min_bmi + gene.max_bmi) / gene.ideal_bmi) * 1.2;

    training.trainingcounter.fill(0);

    emit_event<gameevent::CreatureRecoverEvent>(events, entity);

    life.birthday = datetimer_util_.getRealTime(timers.lifetimer);
    life.born = true;
    life.isdead = false;
    life.causeofdeath = gamecomp::CauseOfDeath::Alive;
    life.causeofrunaway = gamecomp::CauseOfRunAway::NotRunAway;

    emit_event<gameevent::CreatureIsBornEvent>(events, entity);
    emit_event<gameevent::CreatureDoActivityEvent>(events, entity, gamecomp::CreatureActivity::Born);
}


void CreatureBornListener::update(const gameevent::CreatureBornEvent& event, 
    EntityManager& entities,
    EventBus& events, TimeDelta /*dt*/) {

    auto entity = event.entity;
    if (entity) {
        //auto life = entity.component<gamecomp::CreatureLife>();
        //data::CreatureLevel creaturelevel = life->creaturelevel;

        auto life = entity.component<gamecomp::CreatureLifeComponent>();
        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto gene = entity.component<gamecomp::CreatureGeneComponent>();
        //auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
        auto body = entity.component<gamecomp::CreatureBodyComponent>();
        //auto creature_data = entity.component<gamecomp::CreatureDataComponent>();
        //auto creature_battlergene = entity.component<gamecomp::CreatureBattlerGeneComponent>();
        //auto creature_battler = entity.component<gamecomp::CreatureBattlerComponent>();
        auto training = entity.component<gamecomp::CreatureTrainingComponent>();
        auto bodilystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        //auto evolve = entity.component<gamecomp::CreatureEvolveComponent>();

        born(entity, events,
             *timers.get(), *training.get(), *gene.get(), *body.get(),
             *bodilystate.get(), *life.get());
    }
}

} // namespace gamesystem