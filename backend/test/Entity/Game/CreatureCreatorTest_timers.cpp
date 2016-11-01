#include "doctest.h"

#include "Entity/Game/CreatureCreator.h"

#include "Entity/Game/EntityGameTestHelper.h"


TEST_CASE("create CreatePrograssTimers with time 01.01.2000") {
    gameentity::CreatureCreator creaturecreator;
    auto time = CreatureTestData::make_time_point_01_01_2000();
    float factor = 1.0f;

    auto timers = creaturecreator.createCreatureProgressTimers(time, factor);

    SUBCASE("Is realtime in lifetimer set") {
        CHECK(timers.lifetimer.realtime > std::chrono::milliseconds::zero());
    }

    SUBCASE("Is realtime in ProgressTimer set") {
        auto& timer = earr::enum_array_at(timers.timer,
                                    +gamecomp::CreatureProgressTimer::Hungry);
        CHECK(timer.timer.realtime > std::chrono::milliseconds::zero());
    }
}

TEST_CASE("create empty CreatePrograssTimers and set with time 01.01.2000") {
    gameentity::CreatureCreator creaturecreator;
    auto time = CreatureTestData::make_time_point_01_01_2000();
    float factor = 1.0f;

    gamecomp::CreatureProgressTimersComponent timers;
    creaturecreator.setCreatureProgressTimersRealTime(timers, time, factor);

    SUBCASE("Is realtime in lifetimer set") {
        CHECK(timers.lifetimer.realtime > std::chrono::milliseconds::zero());
    }

    SUBCASE("Is realtime in ProgressTimer set") {
        auto& timer = earr::enum_array_at(timers.timer,
                                    +gamecomp::CreatureProgressTimer::Hungry);
        CHECK(timer.timer.realtime > std::chrono::milliseconds::zero());
    }
}

TEST_CASE("create CreatePrograssTimers and setup with lifetimer") {
    computil::DateTimerUtil datetimer_util;
    gameentity::CreatureCreator creaturecreator;
    auto time = CreatureTestData::make_time_point_01_01_2000();
    float factor = 1.0f;

    gamecomp::CreatureProgressTimersComponent timers;
    datetimer_util.init(timers.lifetimer, time, factor);
    creaturecreator.setCreatureProgressTimersRealTimeFromLifetimer(timers);

    SUBCASE("Is realtime in lifetimer set") {
        CHECK(timers.lifetimer.realtime > std::chrono::milliseconds::zero());
    }

    SUBCASE("Is realtime in ProgressTimer set") {
        auto& timer = earr::enum_array_at(timers.timer,
                                    +gamecomp::CreatureProgressTimer::Hungry);
        CHECK(timer.timer.realtime >= timers.lifetimer.realtime);
    }
}
