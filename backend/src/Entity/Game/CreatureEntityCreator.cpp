#include "Entity/Game/CreatureEntityCreator.h"

namespace gameentity {


constexpr std::chrono::seconds CreatureEntityCreator::DEFAULT_MIN_NEEDREFRESHIN;
constexpr std::chrono::seconds CreatureEntityCreator::DEFAULT_MAX_NEEDREFRESHIN;
constexpr std::chrono::seconds CreatureEntityCreator::DEFAULT_MIN_TOTALLIFETIME;
constexpr std::chrono::seconds CreatureEntityCreator::DEFAULT_AGEINGTIME;

constexpr size_t CreatureEntityCreator::DEFAULT_MAX_SHORT_MEMORYSIZE;
constexpr int CreatureEntityCreator::DEFAULT_MAX_SHORT_MEMORYSIZE_VARIANCE;

gamecomp::CreatureTrainingComponent
CreatureEntityCreator::createCreatureTraining() {
    gamecomp::CreatureTrainingComponent ret;

    earr::enum_array_fill(ret.trainingcounter, 0);

    earr::enum_array_fill(ret.trainattrs, false);
    earr::enum_array_fill(ret.lasttrainattrs, false);
    earr::enum_array_fill(ret.attrparam_befortrain, 0);
    earr::enum_array_fill(ret.attrparam_aftertrain, 0);

    earr::enum_array_fill(ret.trainingcounter, 0);

    return ret;
}


gamecomp::CreatureBodyComponent CreatureEntityCreator::createCreatureBody(
    const data::Creature& creature_data,
    const gamecomp::CreatureGeneComponent& gene) {
    gamecomp::CreatureBodyComponent ret;

    ret.weight = 5.0;
    ret.bodysize = 0.3;
    ret.bmi = getBMI(gene, 2, 40, ret.weight, ret.bodysize);


    double weight = creature_data.getEvolCondition().getWeight() * 1.3;
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
    gamecomp::CreaturePsycheComponent ret;

    ret.luck = 100.0;
    ret.disc = 100.0;

    return ret;
}

gamecomp::CreatureLifeComponent CreatureEntityCreator::createCreatureLife(
    const data::Creature& creature,
    std::chrono::system_clock::time_point realtime,
    const gamecomp::CreatureBattlerComponent& battler,
    const gamecomp::CreatureGeneComponent& gene) {
    gamecomp::CreatureLifeComponent ret;


    ret.name = creature.getName();
    ret.creaturelevel = creature.getCreatureLevel();
    ret.creaturecircadianrhythm = creature.getCreatureCircadianRhythm();

    ret.birthday = realtime;
    ret.causeofdeath = gamecomp::CauseOfDeath::Alive;
    ret.isdead = false;

    if (!ret.born && ret.creaturelevel > +data::CreatureLevel::Egg) {
        ret.born = true;
    }


    ret.needrefreshin_ms = min_needrefreshin_;

    ret.oldlevel = battler.lvl;

    ret.maxlifetime = gene.totalmaxlifetime;

    ret.ageingtime = ageingtime_;

    ret.hasstatus.fill(false);
    ret.isbusy = false;

    return ret;
}



void CreatureEntityCreator::create(Entity& entity) {
    auto time = std::chrono::system_clock::now();

    auto timers = createCreatureProgressTimers(time);
    auto training = createCreatureTraining();

    entity.assign<gamecomp::CreatureDataComponent>();
    entity.assign<gamecomp::CreatureProgressTimersComponent>(timers);

    entity.assign<gamecomp::BattlerStatusesComponent>();
    entity.assign<gamecomp::BattlerBattleStateComponent>();
    entity.assign<gamecomp::BattlerResistsComponent>();

    entity.assign<gamecomp::CreatureBattlerComponent>();

    entity.assign<gamecomp::CreatureBattlerGeneComponent>();
    entity.assign<gamecomp::CreatureGeneComponent>();

    entity.assign<gamecomp::CreatureMemoryComponent>();
    entity.assign<gamecomp::CreaturePersonalityComponent>();

    entity.assign<gamecomp::CreatureHungerComponent>();
    entity.assign<gamecomp::CreatureEvolveComponent>();
    entity.assign<gamecomp::CreatureSleepComponent>();
    entity.assign<gamecomp::CreatureTrainingComponent>(training);
    entity.assign<gamecomp::CreatureBodilyStateComponent>();
    entity.assign<gamecomp::CreatureBodyComponent>();
    entity.assign<gamecomp::CreaturePsycheComponent>();
    entity.assign<gamecomp::CreatureLifeComponent>();
}

void CreatureEntityCreator::create(
    Entity& entity, const data::Creature& creature,
    std::chrono::system_clock::time_point realtime, double realtime_factor) {
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


    entity.assign<gamecomp::CreatureDataComponent>(creaturedata);
    entity.assign<gamecomp::CreatureProgressTimersComponent>(timers);

    entity.assign<gamecomp::BattlerStatusesComponent>();
    entity.assign<gamecomp::BattlerBattleStateComponent>(battlerstate);
    entity.assign<gamecomp::BattlerResistsComponent>(battlerresists);
    entity.assign<gamecomp::CreatureBattlerComponent>(creaturebattler);

    entity.assign<gamecomp::CreatureBattlerGeneComponent>(battlergene);
    entity.assign<gamecomp::CreatureGeneComponent>(gene);

    entity.assign<gamecomp::CreatureMemoryComponent>(memory);
    entity.assign<gamecomp::CreaturePersonalityComponent>();

    entity.assign<gamecomp::CreatureHungerComponent>();
    entity.assign<gamecomp::CreatureEvolveComponent>();
    entity.assign<gamecomp::CreatureSleepComponent>();
    entity.assign<gamecomp::CreatureTrainingComponent>(training);
    entity.assign<gamecomp::CreatureBodilyStateComponent>();
    entity.assign<gamecomp::CreatureBodyComponent>(body);
    entity.assign<gamecomp::CreaturePsycheComponent>(psyche);
    entity.assign<gamecomp::CreatureLifeComponent>(life);
}
} // namespace gameentity
