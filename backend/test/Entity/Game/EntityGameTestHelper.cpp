#include "Entity/Game/EntityGameTestHelper.h"

std::chrono::system_clock::time_point
EntityGameTestHelper::make_time_point_01_01_2000() {
    // create tm with 1/1/2000:
    std::tm timeinfo = std::tm();
    timeinfo.tm_year = 100; // year: 2000
    timeinfo.tm_mon = 0;    // month: january
    timeinfo.tm_mday = 1;   // day: 1st
    std::time_t tt = std::mktime(&timeinfo);

    return std::chrono::system_clock::from_time_t(tt);
}

gamecomp::CreatureBattlerGeneComponent
EntityGameTestHelper::make_CreatureBattlerGene_withValues() {
    gamecomp::CreatureBattlerGeneComponent gene;

    for (auto& boni : gene.boniattrinflation) {
        boni = 5;
    }
    for (auto& boni : gene.boniattrfactor) {
        boni = 2.0f;
    }

    return gene;
}

void EntityGameTestHelper::init_ProgressTimer(
    gamecomputil::ProgressTimerUtil& progresstimer_util_,
    gamecomp::ProgressTimer& progresstimer) {
    std::chrono::system_clock::time_point time = make_time_point_01_01_2000();
    float factor = 1.0f;

    progresstimer_util_.init(progresstimer, time, factor);

    std::chrono::milliseconds waittime = std::chrono::milliseconds(100);
    progresstimer.waittime.fill(waittime);

    progresstimer.factor = 1.0f;
}