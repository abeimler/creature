#include "System/Game/CreatureDigestionCallbackSystem.h"

namespace gamesystem {


CreatureDigestionCallbackSystem::CreatureDigestionCallbackSystem() {}



void CreatureDigestionCallbackSystem::makePoop(EventBus& events, Entity entity,
                gamecomp::CreatureProgressTimersComponent& timers,
                gamecomp::CreatureHungerComponent& hunger,
                gamecomp::CreatureGeneComponent& gene, gamecomp::CreatureBodyComponent& body,
                gamecomp::CreaturePsycheComponent& psyche, bool usetoilet) {

    // auto digistation_value = digistation_progresstimer.value;
    auto digistation_overlayvalue = digistation_progresstimer.overlayvalue;

    if (!usetoilet) {
        /// Anzahl der zusätzlichen Haufen
        auto morePoopStack = digistation_overlayvalue / 100;

        /// Anzahl der Hinzugefügten Haufen
        auto addToPoopStack = 1 + morePoopStack; 

        int newpoopstack = hunger.poopstack + addToPoopStack; ///< Zusätliche haufen hinzufügen
        newpoopstack = std::max<int>(newpoopstack, 0);
        newpoopstack = std::min<int>(newpoopstack, gene.max_poopstack);
        hunger.poopstack = newpoopstack;

        // wenn haufen nicht weg geräumt wurden
        if (addToPoopStack > 1 && util::randomRate(UNLUCK_BY_MORETHENMAXPOOPSTACK)) {
            psyche.luck -= UNLUCK_BY_MOREDIGESTIONHEAP * addDigHeap;
        }
        
        emit_events<gameevent::CreatureMakeDigestionHeapEvent>(events, entity, hunger.poopstack);

        emit_events<gameevent::CreatureDoActivityEvent>(events, entity, gamecomp::CreatureActivity::MakeDigestionHeap);
    } else {
        emit_events<gameevent::CreatureDoActivityEvent>(events, entity, gamecomp::CreatureActivity::MakeDigestionHeapToilet);
    }

    lostWeightbyStool(body, gene);
    fullDigestionHeap(timers, hunger, gene, psyche);
}

void CreatureDigestionCallbackSystem::lostWeightbyStool(
    gamecomp::CreatureBodyComponent& body, gamecomp::CreatureGeneComponent& gene) {
    auto ideal_bmi_percent =
        (!util::iszero(gene.max_bmi)) ? gene.ideal_bmi / gene.max_bmi : 0.0;
    auto stool_weight_kg = util::random(100, 200) / 1000.0;
    auto sub_weight = stool_weight_kg * ideal_bmi_percent;
    body.weight -= sub_weight;
}

void CreatureDigestionCallbackSystem::fullPoopStack(
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureHungerComponent& hunger,
    gamecomp::CreatureGeneComponent& gene,
    gamecomp::CreaturePsycheComponent& psyche) {
    // max. haufen erreicht
    if (hunger.poopstack >= gene.max_poopstack) {
        // psyche verringern
        psyche.luck -= UNLUCK_BY_MAXPOOPSTACK;
        psyche.disc -= UNDISC_BY_MAXPOOPSTACK;

        auto& full_poopstack_timer = earr::enum_array_at(
            timers.callback,
            gamecomp::CreatureProgressTimerCallback::FullPoopStack);
        gamecomp::ProgressTimer& full_poopstack_progresstimer =
            full_poopstack_timer.base;

        progresstimer_util_.start(full_poopstack_progresstimer);
    }
}

void CreatureDigestionCallbackSystem::pauseDigestionbyHunger(
    gamecomp::CreatureProgressTimersComponent& timers) {

    auto& hungry_timer =
        earr::enum_array_at(timers.timer, gamecomp::CreatureProgressTimer::Hungry);
    gamecomp::ProgressTimer& hungry_progresstimer = hungry_timer;
    // auto hungry_value = hungry_progresstimer.value;
    auto hungry_overlayvalue = hungry_progresstimer.overlayvalue;
    bool ishungry = hungry_progresstimer.isfull;


    auto& digistation_timer = earr::enum_array_at(
        timers.callback, gamecomp::CreatureProgressTimerCallback::Digestion);
    gamecomp::ProgressTimer& digistation_progresstimer = digistation_timer.base;
    // auto digistation_value = digistation_progresstimer.value;
    // auto digistation_overlayvalue = digistation_progresstimer.overlayvalue;

    if (ishungry) {
        if (hungry_overlayvalue >= PAUSE_DIGISTATION_BY_HUNGRY_OVERLAYVALUE) {
            progresstimer_util_.pause(digistation_progresstimer);
        }
    } else if (digistation_progresstimer.timer.ispause) {
        progresstimer_util_.unpause(digistation_progresstimer);
    }
}

void CreatureDigestionCallbackSystem::illByFullDigestionHeap(Entity entity, EventBus& events, 
    gamecomp::CreatureGeneComponent& gene) {
    if (util::randomRate(gene.rate_ill_by_max_poopstack)) {
        emit_event<gameevent::CreatureAddStatusEvent>(events, entity, data::CreatureStatus::Ill);
    }
}



void CreatureDigestionCallbackSystem::update(const gameevent::ProgressTimerCallbackEvent& event,
                                EntityManager& entities, EventBus& events,
                                TimeDelta /*dt*/) {
    gamecomp::CreatureProgressTimersComponent timers;
    gamecomp::CreatureHungerComponent hunger;
    gamecomp::CreatureGeneComponent gene;
    gamecomp::CreaturePsycheComponent psyche;
    gamecomp::CreatureBodyComponent body;

    for (auto entity :
         entities.entities_with_components(timers, hunger, gene, psyche, body)) {
        
        if(callback_event.type == +gamecomp::CreatureProgressTimerCallback::Digestion) {
            makeDigestionHeap(events, entity, timers, hunger, gene, body, psyche, false);
        } else if(callback_event.type == +gamecomp::CreatureProgressTimerCallback::PauseDigestionHungry) {
            pauseDigestionbyHunger(timers);
        } else if(callback_event.type == +gamecomp::CreatureProgressTimerCallback::FullDigestionHeap) {
            illByFullDigestionHeap(entity, events);
        }
    }
}

} // namespace gamesystem