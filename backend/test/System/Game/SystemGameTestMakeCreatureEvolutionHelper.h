#ifndef SYSTEM_GAME_SYSTEMGAMETESTMAKECREATUREEVOLUTIONHELPER_H_
#define SYSTEM_GAME_SYSTEMGAMETESTMAKECREATUREEVOLUTIONHELPER_H_

#include "Entity/Game/CreatureEntityCreator.h"

#include "Entity/Game/CreatureTestDataEvolution.h"

class MakeCreatureEvolutionHelper {
    public:

    static gamecomp::CreatureDataComponent make_CreatureData();
    static gamecomp::CreatureProgressTimersComponent make_CreatureProgressTimers();
    static gamecomp::BattlerStatusesComponent make_BattlerStatuses();
    static gamecomp::BattlerBattleStateComponent make_BattlerBattleState();
    static gamecomp::BattlerResistsComponent make_BattlerResists();
    static gamecomp::CreatureBattlerComponent make_CreatureBattler();
    static gamecomp::CreatureBattlerGeneComponent make_CreatureBattlerGene();
    static gamecomp::CreatureGeneComponent make_CreatureGene();


    static gamecomp::CreatureMemoryComponent make_CreatureMemory();
    static gamecomp::CreaturePersonalityComponent make_CreaturePersonality();
    static gamecomp::CreatureHungerComponent make_CreatureHunger();
    static gamecomp::CreatureEvolveComponent make_CreatureEvolve();
    static gamecomp::CreatureSleepComponent make_CreatureSleep();
    static gamecomp::CreatureTrainingComponent make_CreatureTraining();
    static gamecomp::CreatureBodilyStateComponent make_CreatureBodilyState();
    static gamecomp::CreatureBodyComponent make_CreatureBody();
    static gamecomp::CreaturePsycheComponent make_CreaturePsyche();
    static gamecomp::CreatureLifeComponent make_CreatureLife();


    static gameentity::Entity create_Entity_Creature(gameentity::EntityManager& entities);


    static gameentity::Entity
    create_Entity_CreatureAllWaitTime(gameentity::EntityManager& entities,
                                    std::chrono::milliseconds waittime);


    static gameentity::Entity
    create_Entity_CreatureAllWaitTime_Starvation(gameentity::EntityManager& entities,
                                    std::chrono::milliseconds waittime);

};


#endif // SYSTEM_GAME_SYSTEMGAMETESTMAKECREATUREEVOLUTIONHELPER_H_
