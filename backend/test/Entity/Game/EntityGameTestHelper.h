#ifndef ENTITY_GAME_ENTITYGAMETESTHELPER_H_
#define ENTITY_GAME_ENTITYGAMETESTHELPER_H_

#include "Entity/Game/CreatureBattlerCreator.h"

#include "CreatureTestData.h"

class EntityGameTestHelper {
    public:

    static std::chrono::system_clock::time_point
    make_time_point_01_01_2000() {
        // create tm with 1/1/2000:
        std::tm timeinfo = std::tm();
        timeinfo.tm_year = 100; // year: 2000
        timeinfo.tm_mon = 0;    // month: january
        timeinfo.tm_mday = 1;   // day: 1st
        std::time_t tt = std::mktime(&timeinfo);

        return std::chrono::system_clock::from_time_t(tt);
    }

    static gamecomp::CreatureBattlerGeneComponent
    make_CreatureBattlerGene_withValues() {
        gamecomp::CreatureBattlerGeneComponent gene;

        for (auto& boni : gene.boniattrinflation) {
            boni = 5;
        }
        for (auto& boni : gene.boniattrfactor) {
            boni = 2.0f;
        }

        return gene;
    }

    static void init_ProgressTimer(
        gamecomputil::ProgressTimerUtil& progresstimer_util_,
        gamecomp::ProgressTimer& progresstimer) {
        std::chrono::system_clock::time_point time = make_time_point_01_01_2000();
        float factor = 1.0f;

        progresstimer_util_.init(progresstimer, time, factor);

        std::chrono::milliseconds waittime = std::chrono::milliseconds(100);
        progresstimer.waittime.fill(waittime);

        progresstimer.factor = 1.0f;
    }
};

#endif // ENTITY_GAME_ENTITYGAMETESTHELPER_H_
