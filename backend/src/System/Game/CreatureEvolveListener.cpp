#include "System/Game/CreatureEvolveListener.h"

namespace gamesystem {

constexpr data::luck_t CreatureEvolveListener::ADD_LUCK_BYGOODEVOLUTION;
constexpr data::disc_t CreatureEvolveListener::ADD_DISC_BYGOODEVOLUTION;

constexpr data::luck_t CreatureEvolveListener::ADD_LUCK_BYBADEVOLUTION;
constexpr data::disc_t CreatureEvolveListener::ADD_DISC_BYBADEVOLUTION;

constexpr gamecomp::progresstimer_percent_t CreatureEvolveListener::GROWING_PROGRESS_AFTER_GOOD_EVOLVE_PERCENT;
constexpr gamecomp::progresstimer_percent_t CreatureEvolveListener::GROWING_PROGRESS_AFTER_BAD_EVOLVE_PERCENT;

constexpr gamecomp::lifetime_t CreatureEvolveListener::ADD_MAXLIFETIME_BYGOODEVOLUTION;
constexpr gamecomp::lifetime_t CreatureEvolveListener::ADD_MAXLIFETIME_BYBADEVOLUTION;


CreatureEvolveListener::CreatureEvolveListener(gameentity::DataManager& datamanager)
    : datamanager_(datamanager)
{}



void CreatureEvolveListener::evolution(
    gameentity::Entity entity, EventBus& events,
    const gameevent::CreatureEvolveEvent& evolve_event,
    gamecomp::CreatureProgressTimersComponent& timers,
    gamecomp::CreatureDataComponent& creature_data,
    gamecomp::CreatureGeneComponent& gene,
    gamecomp::CreatureBattlerGeneComponent& creature_battlergene,
    gamecomp::CreatureBattlerComponent& creature_battler,
    gamecomp::CreatureTrainingComponent& training,
    gamecomp::CreatureBodyComponent& body,
    gamecomp::CreatureBodilyStateComponent& bodilystate,
    gamecomp::CreaturePsycheComponent& psyche,
    gamecomp::CreatureLifeComponent& life,
    gamecomp::CreatureEvolveComponent& evolve) {
        
    const auto& oldcreature = creature_data.creature;
    const auto& newcreature = evolve_event.newcreature;
    auto oldcreature_name = oldcreature.getName();
    auto newcreature_name = newcreature.getName();

    creature_data.creature = newcreature;

    creaturebattler_creator_.transformCreatureBattler(creature_battler, creature_data.creature, creature_battlergene);

    auto newgene = creaturecreator_.createCreatureGene(creature_data);
    gene.bodymass = newgene.bodymass;
    gene.min_bmi = newgene.min_bmi;
    gene.ideal_bmi = newgene.ideal_bmi;
    gene.max_bmi = newgene.max_bmi;
    gene.max_bodysize = newgene.max_bodysize;
    gene.min_weight = newgene.min_weight;
    gene.max_weight = newgene.max_weight;

    gene.cangosleep_at_tired = newgene.cangosleep_at_tired;
    gene.ill_by_max_poopstack_rate = newgene.ill_by_max_poopstack_rate;
    gene.poop_at_digestion_value = newgene.poop_at_digestion_value;

    gene.max_poopstack = newgene.max_poopstack;

    body.weight = std::min<data::weight_t>(body.weight, gene.min_weight * ((gene.min_bmi + gene.max_bmi) / gene.ideal_bmi) * 1.2);
    
    if (evolve_event.goodevolve) {
        body.bodysize = std::max<data::bodysize_t>(body.bodysize, gene.max_bodysize * (GROWING_PROGRESS_AFTER_GOOD_EVOLVE_PERCENT/100.0));
    } else {
        body.bodysize = std::max<data::bodysize_t>(body.bodysize, gene.max_bodysize * (GROWING_PROGRESS_AFTER_BAD_EVOLVE_PERCENT/100.0));
    }
    body.bodysize = std::min<data::bodysize_t>(body.bodysize, gene.max_bodysize);


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

    progresstimer_util_.restart(hungry_progresstimer);
    progresstimer_util_.restart(thristy_progresstimer);
    progresstimer_util_.restart(growing_progresstimer);
    progresstimer_util_.restart(lostcalories_progresstimer);
    progresstimer_util_.restart(gainweightcalorie_progresstimer);
    progresstimer_util_.restart(digestion_progresstimer);

    progresstimer_util_.restart(evolution_progresstimer);

    if (evolve_event.goodevolve) {
        psyche.luck += ADD_LUCK_BYGOODEVOLUTION;
        psyche.disc += ADD_DISC_BYGOODEVOLUTION;
        life.maxlifetime += ADD_MAXLIFETIME_BYGOODEVOLUTION;
    } else {
        psyche.luck += ADD_LUCK_BYBADEVOLUTION;
        psyche.disc += ADD_DISC_BYBADEVOLUTION;
        life.maxlifetime += ADD_MAXLIFETIME_BYBADEVOLUTION;
    }

    life.creaturelevel = creature_data.creature.getCreatureLevel();

    bodilystate.hurtcount = 0;
    bodilystate.illcount = 0;

    auto mosttrain = training.mosttraintime;
    auto mosttraincounter = earr::enum_array_at(training.trainingcounter, mosttrain);
    training.trainingcounter.fill(0);

    auto& training_trainingcounter = earr::enum_array_at(training.trainingcounter, mosttrain);
    training_trainingcounter = mosttraincounter * 10 / 100;
    training_trainingcounter = std::max(1u, training_trainingcounter);

    gamecomp::EvolutionTrakingInfoDetail evolutiontrakinginfodetail;
    evolutiontrakinginfodetail.datetime = datetimer_util_.getRealTime(timers.lifetimer);
    evolutiontrakinginfodetail.lifetime = life.lifetime;

    evolve.preevolution_creature_name.push_back(oldcreature_name);
    evolve.evolutiontrakinginfo.emplace_back(oldcreature_name, newcreature_name, evolutiontrakinginfodetail);

    if (oldcreature.getCreatureLevel() == +data::CreatureLevel::Egg &&
        creature_data.creature.getCreatureLevel() != +data::CreatureLevel::Egg &&
        !life.born) {
        // reborn(entity, events, timers,  training, gene, body, bodilystate,
        // life);
        emit_event<gameevent::CreatureBornEvent>(events, entity);
    }

    emit_event<gameevent::CreatureIsEvolveFinishEvent>(events, entity, gamecomp::EvolutionStatus::Succ);

    if (evolve_event.goodevolve) {
        emit_event<gameevent::CreatureDoActivityEvent>(events, entity, gamecomp::CreatureActivity::EvolveGood);
    } else {
        emit_event<gameevent::CreatureDoActivityEvent>(events, entity, gamecomp::CreatureActivity::EvolveBad);
    }
}



void CreatureEvolveListener::update(const gameevent::CreatureEvolveEvent& event, 
    EntityManager& entities,
    EventBus& events, TimeDelta /*dt*/) {

    auto entity = event.entity;
    if (entity) {
        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);
        auto& timers = entities.get<gamecomp::CreatureProgressTimersComponent>(entity);
        auto& gene = entities.get<gamecomp::CreatureGeneComponent>(entity);
        auto& psyche = entities.get<gamecomp::CreaturePsycheComponent>(entity);
        auto& body = entities.get<gamecomp::CreatureBodyComponent>(entity);
        auto& creature_data = entities.get<gamecomp::CreatureDataComponent>(entity);
        auto& creature_battlergene = entities.get<gamecomp::CreatureBattlerGeneComponent>(entity);
        auto& creature_battler = entities.get<gamecomp::CreatureBattlerComponent>(entity);
        auto& training = entities.get<gamecomp::CreatureTrainingComponent>(entity);
        auto& bodilystate = entities.get<gamecomp::CreatureBodilyStateComponent>(entity);
        auto& evolve = entities.get<gamecomp::CreatureEvolveComponent>(entity);

        evolution(entity, events, event, 
                    timers, creature_data, gene,
                    creature_battlergene, creature_battler, training, body,
                    bodilystate, psyche, life, evolve);
    }
}

} // namespace gamesystem
