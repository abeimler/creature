#include "doctest.h"

#include <thread>

#include "Entity/Game/TimerUtil.h"

void init_Timer(computil::TimerUtil& timer_util, comp::Timer& timer) {
    timer_util.start(timer);
}



TEST_CASE("start Timer") {
    computil::TimerUtil timer_util;
    comp::Timer timer;

    timer_util.start(timer);

    SUBCASE("Timer is started") { CHECK(timer.isstart); }

    SUBCASE("Timer is not paused") { CHECK_FALSE(timer.ispause); }
}



TEST_CASE("pause Timer") {
    computil::TimerUtil timer_util;
    comp::Timer timer;
    init_Timer(timer_util, timer);

    timer_util.pause(timer);

    SUBCASE("Timer is started") { CHECK(timer.isstart); }

    SUBCASE("Timer is paused") { CHECK(timer.ispause); }
}



TEST_CASE("unpause Timer") {
    computil::TimerUtil timer_util;
    comp::Timer timer;
    init_Timer(timer_util, timer);

    timer_util.unpause(timer);

    SUBCASE("Timer is started") { CHECK(timer.isstart); }

    SUBCASE("Timer is not paused") { CHECK_FALSE(timer.ispause); }
}


TEST_CASE("pause and unpause Timer") {
    computil::TimerUtil timer_util;
    comp::Timer timer;
    init_Timer(timer_util, timer);

    timer_util.pause(timer);
    timer_util.unpause(timer);

    SUBCASE("Timer is started") { CHECK(timer.isstart); }

    SUBCASE("Timer is not paused") { CHECK_FALSE(timer.ispause); }
}


TEST_CASE("restart Timer") {
    computil::TimerUtil timer_util;
    comp::Timer timer;
    init_Timer(timer_util, timer);

    timer_util.restart(timer);

    SUBCASE("Timer is started") { CHECK(timer.isstart); }

    SUBCASE("Timer is not paused") { CHECK_FALSE(timer.ispause); }
}



TEST_CASE("stop Timer") {
    computil::TimerUtil timer_util;
    comp::Timer timer;
    init_Timer(timer_util, timer);

    timer_util.stop(timer);

    SUBCASE("Timer is not started") { CHECK_FALSE(timer.isstart); }

    SUBCASE("Timer is not paused") { CHECK_FALSE(timer.ispause); }
}


TEST_CASE("getTime of Timer") {
    computil::TimerUtil timer_util;
    comp::Timer timer;
    init_Timer(timer_util, timer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(10);

    std::this_thread::sleep_for(sleeptime_ms);
    auto time = timer_util.getTime(timer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    CHECK(time_ms >= expectwaittime_ms);
}


TEST_CASE("getTime of Timer with pause") {
    computil::TimerUtil timer_util;
    comp::Timer timer;
    init_Timer(timer_util, timer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(10);

    std::this_thread::sleep_for(sleeptime_ms);
    timer_util.pause(timer);
    std::this_thread::sleep_for(sleeptime_ms);
    auto time = timer_util.getTime(timer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    CHECK(time_ms >= expectwaittime_ms);
}


TEST_CASE("getTime of Timer with pause and unpause") {
    computil::TimerUtil timer_util;
    comp::Timer timer;
    init_Timer(timer_util, timer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(20);

    std::this_thread::sleep_for(sleeptime_ms);
    timer_util.pause(timer);
    std::this_thread::sleep_for(sleeptime_ms);
    timer_util.unpause(timer);
    std::this_thread::sleep_for(sleeptime_ms);
    auto time = timer_util.getTime(timer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    CHECK(time_ms >= expectwaittime_ms);
}


TEST_CASE("getTime of Timer with restart") {
    computil::TimerUtil timer_util;
    comp::Timer timer;
    init_Timer(timer_util, timer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(10);

    std::this_thread::sleep_for(sleeptime_ms);
    timer_util.restart(timer);
    std::this_thread::sleep_for(sleeptime_ms);
    auto time = timer_util.getTime(timer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    CHECK(time_ms >= expectwaittime_ms);
}

TEST_CASE("getTime of Timer with stop") {
    computil::TimerUtil timer_util;
    comp::Timer timer;
    init_Timer(timer_util, timer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(0);

    std::this_thread::sleep_for(sleeptime_ms);
    timer_util.stop(timer);
    auto time = timer_util.getTime(timer);
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    CHECK(time_ms <= expectwaittime_ms);
}
