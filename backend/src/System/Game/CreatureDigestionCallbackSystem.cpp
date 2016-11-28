#include "System/Game/CreatureDigestionCallbackSystem.h"

namespace gamesystem {

constexpr gamecomp::counter_t CreatureDigestionCallbackSystem::RATE_UNLUCK_BY_MORETHENMAXPOOPSTACK;
constexpr data::luck_t CreatureDigestionCallbackSystem::UNLUCK_BY_MORETHENMAXPOOPSTACK;
constexpr data::luck_t CreatureDigestionCallbackSystem::UNLUCK_BY_MAXPOOPSTACK;
constexpr data::disc_t CreatureDigestionCallbackSystem::UNDISC_BY_MAXPOOPSTACK;
constexpr gamecomp::progresstimer_percent_t CreatureDigestionCallbackSystem::PAUSE_DIGESTION_BY_HUNGRY_OVERLAYVALUE;

CreatureDigestionCallbackSystem::CreatureDigestionCallbackSystem() {}


void CreatureDigestionCallbackSystem::makePoop(EventBus& events, Entity entity,
                gamecomp::CreatureProgressTimersComponent& timers,
                gamecomp::CreatureHungerComponent& hunger,
                gamecomp::CreatureGeneComponent& gene, gamecomp::CreatureBodyComponent& body,
                gamecomp::CreaturePsycheComponent& psyche, bool usetoilet) {


    auto& digestion_timer = earr::enum_array_at(timers.callback,
        +gamecomp::CreatureProgressTimerCallback::Digestion);
    gamecomp::ProgressTimer& digestion_progresstimer =
        digestion_timer.base;

    auto digestion_value = digestion_progresstimer.value;

    if(digestion_value >= gene.poop_at_digestion_value) {
    
        auto digestion_overlayvalue = digestion_progresstimer.overlayvalue;

        if (!usetoilet) {
            /// Anzahl der zusätzlichen Haufen
            auto morePoopStack = digestion_overlayvalue / 100;

            /// Anzahl der Hinzugefügten Haufen
            auto addToPoopStack = 1 + morePoopStack; 

            int newpoopstack = hunger.poopstack + addToPoopStack; ///< Zusätliche haufen hinzufügen
            newpoopstack = std::max<int>(newpoopstack, 0);
            newpoopstack = std::min<int>(newpoopstack, gene.max_poopstack);
            hunger.poopstack = newpoopstack;

            // wenn haufen nicht weg geräumt wurden
            if (addToPoopStack > 1 && util::randomRate(UNLUCK_BY_MORETHENMAXPOOPSTACK)) {
                psyche.luck -= UNLUCK_BY_MAXPOOPSTACK * addToPoopStack;
            }
            
            emit_event<gameevent::CreatureMakePoopEvent>(events, entity, hunger.poopstack);

            emit_event<gameevent::CreatureDoActivityEvent>(events, entity, gamecomp::CreatureActivity::MakePoop);
        } else {
            emit_event<gameevent::CreatureDoActivityEvent>(events, entity, gamecomp::CreatureActivity::MakePoopInToilet);
        }

        progresstimer_util_.restart(digestion_progresstimer);

        lostWeightbyStool(body, gene);
        fullPoopStack(timers, hunger, gene, psyche);
    } else {
        emit_event<gameevent::CreatureDoActivityEvent>(events, entity, gamecomp::CreatureActivity::MakeNoPoop);
    }
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

        auto& full_poopstack_timer = earr::enum_array_at(timers.callback,
            +gamecomp::CreatureProgressTimerCallback::FullPoopStack);
        gamecomp::ProgressTimer& full_poopstack_progresstimer =
            full_poopstack_timer.base;

        progresstimer_util_.start(full_poopstack_progresstimer);
    }
}

void CreatureDigestionCallbackSystem::pauseDigestionbyHunger(
    gamecomp::CreatureProgressTimersComponent& timers) {

    auto& hungry_timer = earr::enum_array_at(timers.timer, 
        +gamecomp::CreatureProgressTimer::Hungry);
    gamecomp::ProgressTimer& hungry_progresstimer = hungry_timer;
    // auto hungry_value = hungry_progresstimer.value;
    auto hungry_overlayvalue = hungry_progresstimer.overlayvalue;
    bool ishungry = hungry_progresstimer.isfull;


    auto& digestion_timer = earr::enum_array_at(timers.callback, 
        +gamecomp::CreatureProgressTimerCallback::Digestion);
    gamecomp::ProgressTimer& digestion_progresstimer = digestion_timer.base;
    // auto digestion_value = digestion_progresstimer.value;
    // auto digestion_overlayvalue = digestion_progresstimer.overlayvalue;

    if (ishungry) {
        if (hungry_overlayvalue >= PAUSE_DIGESTION_BY_HUNGRY_OVERLAYVALUE) {
            progresstimer_util_.pause(digestion_progresstimer);
        }
    } else if (digestion_progresstimer.timer.ispause) {
        progresstimer_util_.unpause(digestion_progresstimer);
    }
}

void CreatureDigestionCallbackSystem::illByFullPoopStack(Entity entity, EventBus& events, 
    gamecomp::CreatureGeneComponent& gene) {
    if (util::randomRate(gene.ill_by_max_poopstack_rate)) {
        emit_event<gameevent::CreatureAddStatusEvent>(events, entity, data::CreatureStatus::Ill);
    }
}



void CreatureDigestionCallbackSystem::update(const gameevent::ProgressTimerCallbackEvent& event,
                                EntityManager& entities, EventBus& events,
                                TimeDelta /*dt*/) {
    Component<gamecomp::CreatureProgressTimersComponent> timers;
    Component<gamecomp::CreatureHungerComponent> hunger;
    Component<gamecomp::CreatureGeneComponent> gene;
    Component<gamecomp::CreaturePsycheComponent> psyche;
    Component<gamecomp::CreatureBodyComponent> body;
    Component<gamecomp::CreaturePersonalityComponent> personality;

    for (auto entity :
         entities.entities_with_components(timers, hunger, gene, psyche, body, personality)) {
        
        if(event.type == +gamecomp::CreatureProgressTimerCallback::Digestion) {
            makePoop(events, entity, *timers.get(), *hunger.get(), *gene.get(), *body.get(), *psyche.get(), personality->housebroken);
        } else if(event.type == +gamecomp::CreatureProgressTimerCallback::PauseDigestionHungry) {
            pauseDigestionbyHunger(*timers.get());
        } else if(event.type == +gamecomp::CreatureProgressTimerCallback::FullPoopStack) {
            illByFullPoopStack(entity, events, *gene.get());
        }
    }
}

} // namespace gamesystem