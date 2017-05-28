#include "System/Game/CreatureSystemCallbackListener.h"

namespace gamesystem {


CreatureSystemCallbackListener::CreatureSystemCallbackListener() {}


void CreatureSystemCallbackListener::runAwayUnhappyStart(
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

void CreatureSystemCallbackListener::updateBored(
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

/*
void CreatureSystemCallbackListener::updateLuck(
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
*/


void CreatureSystemCallbackListener::runAwayUnhappy(
    EventBus& events, Entity entity,
    gamecomp::CreatureProgressTimersComponent& timers) {

    auto& runawayunhappy_timer = earr::enum_array_at(
        timers.callback, +gamecomp::CreatureProgressTimerCallback::RunAwayUnhappy);
    gamecomp::ProgressTimer& runawayunhappy_progresstimer =
        runawayunhappy_timer.base;

    progresstimer_util_.stop(runawayunhappy_progresstimer);


    emit_event<gameevent::CreatureAddStatusEvent>(events,
        entity, data::CreatureStatus::Ill);
    emit_event<gameevent::CreatureRemoveRunAwayEvent>(events, entity);
}



void CreatureSystemCallbackListener::update(
    const gameevent::ProgressTimerCallbackEvent& event, EntityManager& entities,
    EventBus& events, TimeDelta /*dt*/) {

    for(auto entity : entities.view<gamecomp::CreatureProgressTimersComponent, 
            gamecomp::CreatureHungerComponent, 
            gamecomp::CreatureGeneComponent, gamecomp::CreaturePsycheComponent, gamecomp::CreaturePersonalityComponent>()) {
        
        auto& timers = entities.get<gamecomp::CreatureProgressTimersComponent>(entity);
        //auto& hunger = entities.get<gamecomp::CreatureHungerComponent>(entity);
        //auto& gene = entities.get<gamecomp::CreatureGeneComponent>(entity);    
        //auto& psyche = entities.get<gamecomp::CreaturePsycheComponent>(entity);   
        //auto& body = entities.get<gamecomp::CreatureBodyComponent>(entity);   
        //auto& personality = entities.get<gamecomp::CreaturePersonalityComponent>(entity);   
        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);   

        if (event.type == +gamecomp::CreatureProgressTimerCallback::Unhappy) {
            runAwayUnhappyStart(events, entity,
                                timers, life);
        } else if (event.type ==
                   +gamecomp::CreatureProgressTimerCallback::RunAwayUnhappy) {
            runAwayUnhappy(events, entity,
                            timers);
        } else if (event.type ==
                   +gamecomp::CreatureProgressTimerCallback::Bored) {
            updateBored(events, entity,
                            timers, life);
        }
    }
}

} // namespace gamesystem
