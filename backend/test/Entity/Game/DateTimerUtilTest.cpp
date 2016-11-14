#include <thread>

#include "doctest.h"

#include "Entity/Game/DateTimerUtil.h"

#include "Entity/Game/EntityGameTestHelper.h"


void init_DateTimer(computil::DateTimerUtil& datetimer_util,
                           comp::DateTimer& datetimer) {
    datetimer_util.init(datetimer);
}



TEST_CASE("start DateTimer") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    datetimer_util.start(datetimer);

    SUBCASE("DateDateTimer is started") { CHECK(datetimer.isstart); }

    SUBCASE("DateDateTimer is not paused") { CHECK_FALSE(datetimer.ispause); }
}



TEST_CASE("pause without start DateTimer") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    datetimer_util.pause(datetimer);

    SUBCASE("DateTimer is started") { CHECK_FALSE(datetimer.isstart); }

    SUBCASE("DateTimer is paused") { CHECK_FALSE(datetimer.ispause); }
}


TEST_CASE("start and pause DateTimer") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    datetimer_util.start(datetimer);
    datetimer_util.pause(datetimer);

    SUBCASE("DateTimer is started") { CHECK(datetimer.isstart); }

    SUBCASE("DateTimer is paused") { CHECK(datetimer.ispause); }
}



TEST_CASE("unpause without pause and start DateTimer") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    datetimer_util.unpause(datetimer);

    SUBCASE("DateTimer is started") { CHECK_FALSE(datetimer.isstart); }

    SUBCASE("DateTimer is not paused") { CHECK_FALSE(datetimer.ispause); }
}

TEST_CASE("unpause without pause DateTimer") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    datetimer_util.unpause(datetimer);

    SUBCASE("DateTimer is started") { CHECK_FALSE(datetimer.isstart); }

    SUBCASE("DateTimer is not paused") { CHECK_FALSE(datetimer.ispause); }
}

TEST_CASE("start pause and unpause DateTimer") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    datetimer_util.start(datetimer);
    datetimer_util.pause(datetimer);
    datetimer_util.unpause(datetimer);

    SUBCASE("DateTimer is started") { CHECK(datetimer.isstart); }

    SUBCASE("DateTimer is not paused") { CHECK_FALSE(datetimer.ispause); }
}


TEST_CASE("restart DateTimer") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    datetimer_util.restart(datetimer);

    SUBCASE("DateTimer is started") { CHECK(datetimer.isstart); }

    SUBCASE("DateTimer is not paused") { CHECK_FALSE(datetimer.ispause); }
}



TEST_CASE("stop DateTimer") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    datetimer_util.stop(datetimer);

    SUBCASE("DateTimer is not started") { CHECK_FALSE(datetimer.isstart); }

    SUBCASE("DateTimer is not paused") { CHECK_FALSE(datetimer.ispause); }
}


TEST_CASE("getTime of DateTimer") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);


    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(10);

    datetimer_util.start(datetimer);

    std::this_thread::sleep_for(sleeptime_ms);
    datetimer_util.update(datetimer);
    auto time = datetimer_util.getTime(datetimer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    CHECK(time_ms >= expectwaittime_ms);
}


TEST_CASE("getTime of DateTimer Speedup with factor") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    int factor = 2;
    datetimer.realtime_factor = factor;

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(20);

    datetimer_util.start(datetimer);

    std::this_thread::sleep_for(sleeptime_ms);
    datetimer_util.update(datetimer);
    auto time = datetimer_util.getTime(datetimer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    CHECK(time_ms >= expectwaittime_ms);
}

TEST_CASE("getTime of DateTimer Slowdown with factor") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    double factor = 2;
    datetimer.realtime_factor = 1.0 / factor;

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(5);


    datetimer_util.start(datetimer);

    std::this_thread::sleep_for(sleeptime_ms);
    datetimer_util.update(datetimer);
    auto time = datetimer_util.getTime(datetimer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    SUBCASE("getTime >= expected time") {
        CHECK(time_ms >= expectwaittime_ms);
    }

    SUBCASE("getTime < sleeped time") { CHECK(time_ms < sleeptime_ms); }
}



TEST_CASE("getTime of DateTimer with pause") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(10);

    datetimer_util.start(datetimer);

    std::this_thread::sleep_for(sleeptime_ms);
    datetimer_util.update(datetimer);
    datetimer_util.pause(datetimer);
    std::this_thread::sleep_for(sleeptime_ms);
    datetimer_util.update(datetimer);
    auto time = datetimer_util.getTime(datetimer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    CHECK(time_ms >= expectwaittime_ms);
}


TEST_CASE("getTime of DateTimer with pause and unpause") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(20);

    datetimer_util.start(datetimer);

    std::this_thread::sleep_for(sleeptime_ms);
    datetimer_util.update(datetimer);
    datetimer_util.pause(datetimer);
    std::this_thread::sleep_for(sleeptime_ms);
    datetimer_util.update(datetimer);
    datetimer_util.unpause(datetimer);
    std::this_thread::sleep_for(sleeptime_ms);
    datetimer_util.update(datetimer);
    auto time = datetimer_util.getTime(datetimer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    CHECK(time_ms >= expectwaittime_ms);
}


TEST_CASE("getTime of DateTimer with restart") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(10);

    datetimer_util.start(datetimer);

    std::this_thread::sleep_for(sleeptime_ms);
    datetimer_util.restart(datetimer);
    std::this_thread::sleep_for(sleeptime_ms);
    datetimer_util.update(datetimer);
    auto time = datetimer_util.getTime(datetimer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    CHECK(time_ms >= expectwaittime_ms);
}

TEST_CASE("getTime of DateTimer with stop") {
    computil::DateTimerUtil datetimer_util;
    comp::DateTimer datetimer;
    init_DateTimer(datetimer_util, datetimer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(0);

    datetimer_util.start(datetimer);

    std::this_thread::sleep_for(sleeptime_ms);
    datetimer_util.stop(datetimer);
    datetimer_util.update(datetimer);
    auto time = datetimer_util.getTime(datetimer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    CHECK(time_ms <= expectwaittime_ms);
}
