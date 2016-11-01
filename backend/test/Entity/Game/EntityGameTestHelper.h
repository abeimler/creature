#ifndef ENTITY_GAME_ENTITYGAMETESTHELPER_H_
#define ENTITY_GAME_ENTITYGAMETESTHELPER_H_

#include "Entity/Game/CreatureBattlerCreator.h"

#include "CreatureTestData.h"

class EntityGameTestHelper {
    public:

    static std::chrono::system_clock::time_point make_time_point_01_01_2000();
    
    static gamecomp::CreatureBattlerGeneComponent make_CreatureBattlerGene_withValues();

    static void init_ProgressTimer(gamecomputil::ProgressTimerUtil& progresstimer_util_, gamecomp::ProgressTimer& progresstimer);

};

#endif // ENTITY_GAME_ENTITYGAMETESTHELPER_H_
