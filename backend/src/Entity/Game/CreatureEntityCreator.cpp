#include "Entity/Game/CreatureEntityCreator.h"

namespace gameentity {


constexpr gamecomp::waittime_t CreatureEntityCreator::DEFAULT_MIN_NEEDREFRESHIN;
constexpr gamecomp::waittime_t CreatureEntityCreator::DEFAULT_MAX_NEEDREFRESHIN;
constexpr gamecomp::waittime_t CreatureEntityCreator::DEFAULT_MIN_TOTALLIFETIME;
constexpr gamecomp::waittime_t CreatureEntityCreator::DEFAULT_AGEINGTIME;

constexpr size_t CreatureEntityCreator::DEFAULT_MAX_SHORT_MEMORYSIZE;
constexpr int CreatureEntityCreator::DEFAULT_MAX_SHORT_MEMORYSIZE_VARIANCE;

constexpr gamecomp::progresstimer_percent_t
    CreatureEntityCreator::CANGOSLEEP_AT_TIRED;
constexpr gamecomp::counter_t CreatureEntityCreator::MAX_POOPSTACK;
constexpr data::percent_rate_t CreatureEntityCreator::ILL_BY_MAXPOOPSTACK_RATE;
constexpr gamecomp::progresstimer_percent_t
    CreatureEntityCreator::POOP_AT_DIGESTIONS_VALUE;

constexpr data::bmi_t CreatureEntityCreator::MIN_BMI;
constexpr data::bmi_t CreatureEntityCreator::IDEAL_BMI;
constexpr data::bmi_t CreatureEntityCreator::MAX_BMI;

constexpr data::bmi_t CreatureEntityCreator::LOW_MIN_BMI;
constexpr data::bmi_t CreatureEntityCreator::LOW_IDEAL_BMI;
constexpr data::bmi_t CreatureEntityCreator::LOW_MAX_BMI;

constexpr data::bmi_t CreatureEntityCreator::HIGH_MIN_BMI;
constexpr data::bmi_t CreatureEntityCreator::HIGH_IDEAL_BMI;
constexpr data::bmi_t CreatureEntityCreator::HIGH_MAX_BMI;


gamecomp::CreatureTrainingComponent
CreatureEntityCreator::createCreatureTraining() {
    gamecomp::CreatureTrainingComponent ret;

    earr::enum_array_fill(ret.trainingcounter, 0u);

    earr::enum_array_fill(ret.trainattrs, false);
    earr::enum_array_fill(ret.lasttrainattrs, false);
    earr::enum_array_fill(ret.attrparam_befortrain, 0);
    earr::enum_array_fill(ret.attrparam_aftertrain, 0);

    return ret;
}


gamecomp::CreatureBodyComponent CreatureEntityCreator::createCreatureBody(
    const data::Creature& creature_data,
    const gamecomp::CreatureGeneComponent& gene) {
  gamecomp::CreatureBodyComponent ret{};

  // ret.weight = 5.0;
  // ret.bodysize = 0.3;
  // ret.bmi = getBMI(gene, 2, 40, ret.weight, ret.bodysize);

  ret.bodysize = creature_data.getMinBodySize();

  auto weight = creature_data.getEvolCondition().getWeight() * 1.3;
  if (creature_data.getEvolCondition().getWeight() <= 0.0 ||
      util::iszero(weight)) {
    weight = creature_data.getMinWeight() * 4.0;
    }
    ret.weight = weight;

    ret.bmi = getBMI(creature_data, gene, ret.weight);

    /// 1 kcal/kg h * Weight * 24 h = need kcal per day
    ret.calories = 1.0 * ret.weight * 24;


    return ret;
}

gamecomp::CreaturePsycheComponent
CreatureEntityCreator::createCreaturePsyche() {
  gamecomp::CreaturePsycheComponent ret{};

  ret.luck = 100.0;
  ret.disc = 100.0;

  return ret;
}

gamecomp::CreatureLifeComponent CreatureEntityCreator::createCreatureLife(
    const data::Creature& creature, gamecomp::birthday_t birthday,
    const gamecomp::CreatureBattlerComponent& battler,
    const gamecomp::CreatureGeneComponent& gene) {
    gamecomp::CreatureLifeComponent ret;


    ret.name = creature.getName();
    ret.creaturelevel = creature.getCreatureLevel();
    ret.creaturecircadianrhythm = creature.getCreatureCircadianRhythm();

    ret.birthday = birthday;
    ret.causeofdeath = gamecomp::CauseOfDeath::Alive;
    ret.isdead = false;

    if (!ret.born && ret.creaturelevel > +data::CreatureLevel::Egg) {
        ret.born = true;
    }


    ret.needrefreshin = min_needrefreshin_;

    ret.oldlevel = battler.lvl;

    ret.maxlifetime = gene.totalmaxlifetime;

    ret.ageingtime = ageingtime_;

    ret.hasstatus.fill(false);
    ret.isbusy = false;

    return ret;
}



void CreatureEntityCreator::create(EntityManager& entities, Entity& entity) {
    auto time = std::chrono::system_clock::now();

    auto timers = createCreatureProgressTimers(time);
    auto training = createCreatureTraining();

    entities.assign<gamecomp::CreatureDataComponent>(entity);
    entities.assign<gamecomp::CreatureProgressTimersComponent>(entity, timers);

    entities.assign<gamecomp::BattlerStatusesComponent>(entity);
    entities.assign<gamecomp::BattlerBattleStateComponent>(entity);
    entities.assign<gamecomp::BattlerResistsComponent>(entity);

    entities.assign<gamecomp::CreatureBattlerComponent>(entity);

    entities.assign<gamecomp::CreatureBattlerGeneComponent>(entity);
    entities.assign<gamecomp::CreatureGeneComponent>(entity);

    entities.assign<gamecomp::CreatureMemoryComponent>(entity);
    entities.assign<gamecomp::CreaturePersonalityComponent>(entity);

    entities.assign<gamecomp::CreatureHungerComponent>(entity);
    entities.assign<gamecomp::CreatureEvolveComponent>(entity);
    entities.assign<gamecomp::CreatureSleepComponent>(entity);
    entities.assign<gamecomp::CreatureTrainingComponent>(entity, training);
    entities.assign<gamecomp::CreatureBodilyStateComponent>(entity);
    entities.assign<gamecomp::CreatureBodyComponent>(entity);
    entities.assign<gamecomp::CreaturePsycheComponent>(entity);
    entities.assign<gamecomp::CreatureLifeComponent>(entity);
}

void CreatureEntityCreator::create(EntityManager& entities, 
    Entity& entity, const data::Creature& creature,
    std::chrono::system_clock::time_point realtime,
    gamecomp::progresstimer_factor_t realtime_factor) {
    auto timers =
        createCreatureProgressTimersCreature(realtime, realtime_factor);

    auto creaturedata = creaturebattler_creator_.createCreatureData(creature);
    auto creaturebattler = creaturebattler_creator_.createCreatureBattler();

    gamecomp::CreatureBattlerGeneComponent battlergene =
        creaturebattler_creator_.createCreatureBattlerGene();

    creaturebattler_creator_.loadCreatureBattler(creaturebattler, creature,
                                                 battlergene);


    auto battlerstate =
        creaturebattler_creator_.createBattlerBattleState(creature);
    auto battlerresists =
        creaturebattler_creator_.createBattlerResists(creature);
    auto gene = createCreatureGene(creature);

    auto memory = createCreatureMemory();
    auto training = createCreatureTraining();
    auto body = createCreatureBody(creaturedata, gene);
    auto psyche = createCreaturePsyche();
    auto life =
        createCreatureLife(creaturedata, realtime, creaturebattler, gene);

    setupCreatureProgressTimers(timers, creaturedata, life, gene, body);


    entities.assign<gamecomp::CreatureDataComponent>(entity, creaturedata);
    entities.assign<gamecomp::CreatureProgressTimersComponent>(entity, timers);

    entities.assign<gamecomp::BattlerStatusesComponent>(entity);
    entities.assign<gamecomp::BattlerBattleStateComponent>(entity, battlerstate);
    entities.assign<gamecomp::BattlerResistsComponent>(entity, battlerresists);
    entities.assign<gamecomp::CreatureBattlerComponent>(entity, creaturebattler);

    entities.assign<gamecomp::CreatureBattlerGeneComponent>(entity, battlergene);
    entities.assign<gamecomp::CreatureGeneComponent>(entity, gene);

    entities.assign<gamecomp::CreatureMemoryComponent>(entity, memory);
    entities.assign<gamecomp::CreaturePersonalityComponent>(entity);

    entities.assign<gamecomp::CreatureHungerComponent>(entity);
    entities.assign<gamecomp::CreatureEvolveComponent>(entity);
    entities.assign<gamecomp::CreatureSleepComponent>(entity);
    entities.assign<gamecomp::CreatureTrainingComponent>(entity, training);
    entities.assign<gamecomp::CreatureBodilyStateComponent>(entity);
    entities.assign<gamecomp::CreatureBodyComponent>(entity, body);
    entities.assign<gamecomp::CreaturePsycheComponent>(entity, psyche);
    entities.assign<gamecomp::CreatureLifeComponent>(entity, life);

}
} // namespace gameentity
