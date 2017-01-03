#include "System/Game/CreatureTryToEvolveListener.h"

namespace gamesystem {

CreatureTryToEvolveListener::CreatureTryToEvolveListener(gameentity::DataManager& datamanager)
    : datamanager_(datamanager)
{}





bool CreatureTryToEvolveListener::hasNextCreatureEvolutionConditionTrainingTime(
    const gamecomp::CreatureDataComponent& creature_data,
    data::CreatureTrainTime trainin) {

    auto find_traintime = [&](const auto& creature_name) {
        auto creature = datamanager_.findCreature(creature_name);
        return (creature)? creature->getEvolCondition().getTrainTime(trainin) : false;
    };


    const auto& creature = creature_data.creature;
    const auto& next_creatures = creature.getNextCreatures();

    auto it = std::find_if(std::begin(next_creatures), std::end(next_creatures),
                           find_traintime);

    return it != std::end(next_creatures);
}


bool CreatureTryToEvolveListener::haveEvolutionCondition(
    const gamecomp::CreatureBattlerComponent& creature_battler,
    const gamecomp::CreatureTrainingComponent& training,
    const gamecomp::CreaturePsycheComponent& psyche,
    const gamecomp::CreatureBodyComponent& body,
    const gamecomp::CreatureBodilyStateComponent& bodilystate,
    const data::EvolutionCondition& condition) {

    auto must_evolve_at_level = condition.getMustEvolveAtLevel();
    if (must_evolve_at_level != data::EvolutionCondition::MUSTEVOLVEATLEVEL_NONE &&
        creature_battler.lvl >= must_evolve_at_level) {
        return true;
    }


    bool canEvol = true;

    if (canEvol) {
        for (auto attr : earr::Enum<data::Attribute>()) {
            canEvol = canEvol && earr::enum_array_at(creature_battler.attr, attr) >= condition.getAttr(attr);
        }
    }

    if (canEvol) {
        bool mostTrain = false;
        for (auto traintime : earr::Enum<data::CreatureTrainTime>()) {
            if (mostTrain) {
                break;
            }
            
            if (condition.getTrainTime(traintime)) {
                mostTrain = mostTrain || traintime == training.mosttraintime;
            }
        }
        canEvol = canEvol && mostTrain;
    }

    canEvol = canEvol && 
                psyche.disc >= condition.getDisc() &&
                psyche.luck >= condition.getLuck() &&
                body.weight >= condition.getWeight() &&
                ((condition.wasNotIll()) ? bodilystate.illcount == 0 : true) &&
                ((condition.wasNotHurt()) ? bodilystate.hurtcount == 0 : true);

    return canEvol;
}

void CreatureTryToEvolveListener::tryEvolve(gameentity::Entity entity, EventBus& events,
    gamecomp::CreatureDataComponent& creature_data,
    gamecomp::CreatureBattlerComponent& creature_battler,
    gamecomp::CreatureTrainingComponent& training,
    gamecomp::CreaturePsycheComponent& psyche,
    gamecomp::CreatureBodyComponent& body,
    gamecomp::CreatureBodilyStateComponent& bodilystate,
    bool& isEvol,
    size_t nextcreatures_index, size_t nextcreatures_size, const data::Creature& nextcreature, bool goodevolve) {

    const auto& condition = nextcreature.getEvolCondition();

    bool canEvol = hasNextCreatureEvolutionConditionTrainingTime(creature_data, training.mosttraintime);
    if (canEvol) {
        canEvol = haveEvolutionCondition(creature_battler, training, psyche,
                                         body, bodilystate, condition);
        if (canEvol) {
            /**
            * the last creature has the lowest evolve rate,
            * for example with 5 possible next creatures:
            * 5. creature: 20 %
            * 4. creature: 40 %
            * 3. creature: 60 %
            * 2. creature: 80 %
            * 1. creature: 100 %
            * */
            auto rate = (nextcreatures_size > 1)? (nextcreatures_size - nextcreatures_index) * 100 / nextcreatures_size : 100;
            rate = std::max<decltype(rate)>(1, rate);

            if (canEvol && util::randomRate(rate)) {
                emit_event<gameevent::CreatureEvolveEvent>(events, entity, goodevolve, nextcreature);
                isEvol = true;
            }
        }
    }
}


void CreatureTryToEvolveListener::tryEvolveFromList(gameentity::Entity entity, EventBus& events,
    const std::vector<std::string>& nextcreatures,
    gamecomp::CreatureDataComponent& creature_data,
    gamecomp::CreatureBattlerComponent& creature_battler,
    gamecomp::CreatureTrainingComponent& training,
    gamecomp::CreaturePsycheComponent& psyche,
    gamecomp::CreatureBodyComponent& body,
    gamecomp::CreatureBodilyStateComponent& bodilystate,
    bool& isEvol,
    bool goodevolve) {
    if (!isEvol && !nextcreatures.empty()) {
        auto nextcreatures_size = nextcreatures.size();
        auto nextcreatures_index = nextcreatures_size - 1;

        // HACK: std::find_if = std::for_each + break
        std::find_if(std::crbegin(nextcreatures), std::crend(nextcreatures), [&](const std::string& nextcreature_name) {
            if(!isEvol) {
                auto nextcreature = datamanager_.findCreature(nextcreature_name);
                
                if(nextcreature) {
                    tryEvolve(entity, events,
                        creature_data, creature_battler, training,
                        psyche, body, bodilystate, isEvol,
                        nextcreatures_index, nextcreatures_size, *nextcreature, goodevolve);
                }
                nextcreatures_index++;
            }
            return isEvol;
        });
    }
}

void CreatureTryToEvolveListener::tryToEvolve(gameentity::Entity entity, EventBus& events,
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
    if (life.isdead || life.isbusy) {
        emit_event<gameevent::CreatureIsEvolveFinishEvent>(events, entity, +gamecomp::EvolutionStatus::DeadOrNotReady);
        return;
    }

    const auto& creature = creature_data.creature;

    const auto& nextcreatures = creature.getNextCreatures();
    const auto& misscreatures = creature.getMissCreatures();

    if (nextcreatures.empty() && misscreatures.empty()) {
        emit_event<gameevent::CreatureIsEvolveFinishEvent>(events, entity, +gamecomp::EvolutionStatus::NoneNextCreatures);
        return;
    }

    bool isEvol = false;

    tryEvolveFromList(entity, events,
        nextcreatures,
        creature_data, creature_battler,
        training, psyche, body, bodilystate,
        isEvol, true);
    
    tryEvolveFromList(entity, events, 
        misscreatures,
        creature_data, creature_battler,
        training, psyche, body, bodilystate,
        isEvol, false);

    if (!isEvol) {
        emit_event<gameevent::CreatureIsEvolveFinishEvent>(events, entity, +gamecomp::EvolutionStatus::Fail);
    }
}


void CreatureTryToEvolveListener::update(const gameevent::CreatureTryToEvolveEvent& event, 
    EntityManager& entities,
    EventBus& events, TimeDelta /*dt*/) {

    auto entity = event.entity;
    if (entity) {
        /*
        auto life = entity.component<gamecomp::CreatureLife>();
        model::data::CreatureLevel creaturelevel = life->creaturelevel;
        */

        auto life = entity.component<gamecomp::CreatureLifeComponent>();

        if (life->readytoevolve) {
            auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
            auto gene = entity.component<gamecomp::CreatureGeneComponent>();
            auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
            auto body = entity.component<gamecomp::CreatureBodyComponent>();
            auto creature_data = entity.component<gamecomp::CreatureDataComponent>();
            auto creature_battlergene = entity.component<gamecomp::CreatureBattlerGeneComponent>();
            auto creature_battler = entity.component<gamecomp::CreatureBattlerComponent>();
            auto training = entity.component<gamecomp::CreatureTrainingComponent>();
            auto bodilystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
            auto evolve = entity.component<gamecomp::CreatureEvolveComponent>();

            tryToEvolve(entity, events, 
                        *timers.get(), *creature_data.get(), *gene.get(),
                        *creature_battlergene.get(), *creature_battler.get(), *training.get(), *body.get(),
                        *bodilystate.get(), *psyche.get(), *life.get(), *evolve.get());
        }
    }
}

} // namespace gamesystem