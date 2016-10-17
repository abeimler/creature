#include <thread>

#include "doctest.h"

#include "Data/Timer.h"



static void init_Timer(data::Timer& timer) { timer.start(); }



TEST_CASE("start ModelTimer") {
    data::Timer timer;

    timer.start();

    SUBCASE("Timer is started") { REQUIRE(timer.isStarted()); }

    SUBCASE("Timer is not paused") { REQUIRE_FALSE(timer.isPaused()); }
}



TEST_CASE("pause ModelTimer") {
    data::Timer timer;
    init_Timer(timer);

    timer.pause();

    SUBCASE("Timer is started") { REQUIRE(timer.isStarted()); }

    SUBCASE("Timer is paused") { REQUIRE(timer.isPaused()); }
}



TEST_CASE("unpause ModelTimer") {
    data::Timer timer;
    init_Timer(timer);

    timer.unpause();

    SUBCASE("Timer is started") { REQUIRE(timer.isStarted()); }

    SUBCASE("Timer is not paused") { REQUIRE_FALSE(timer.isPaused()); }
}


TEST_CASE("pause and unpause ModelTimer") {
    data::Timer timer;
    init_Timer(timer);

    timer.pause();
    timer.unpause();

    SUBCASE("Timer is started") { REQUIRE(timer.isStarted()); }

    SUBCASE("Timer is not paused") { REQUIRE_FALSE(timer.isPaused()); }
}


TEST_CASE("restart ModelTimer") {
    data::Timer timer;
    init_Timer(timer);

    timer.restart();

    SUBCASE("Timer is started") { REQUIRE(timer.isStarted()); }

    SUBCASE("Timer is not paused") { REQUIRE_FALSE(timer.isPaused()); }
}



TEST_CASE("stop ModelTimer") {
    data::Timer timer;
    init_Timer(timer);

    timer.stop();

    SUBCASE("Timer is not started") { REQUIRE_FALSE(timer.isStarted()); }

    SUBCASE("Timer is not paused") { REQUIRE_FALSE(timer.isPaused()); }
}



TEST_CASE("getTime of ModelTimer") {
    data::Timer timer;
    init_Timer(timer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(10);

    std::this_thread::sleep_for(sleeptime_ms);
    auto time = timer.getTimeNanosec();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    REQUIRE(time_ms >= expectwaittime_ms);
}


TEST_CASE("getTime of ModelTimer with pause") {
    data::Timer timer;
    init_Timer(timer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(10);

    std::this_thread::sleep_for(sleeptime_ms);
    timer.pause();
    std::this_thread::sleep_for(sleeptime_ms);
    auto time = timer.getTimeNanosec();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    REQUIRE(time_ms >= expectwaittime_ms);
}


TEST_CASE("getTime of ModelTimer with pause and unpause") {
    data::Timer timer;
    init_Timer(timer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(20);

    std::this_thread::sleep_for(sleeptime_ms);
    timer.pause();
    std::this_thread::sleep_for(sleeptime_ms);
    timer.unpause();
    std::this_thread::sleep_for(sleeptime_ms);
    auto time = timer.getTimeNanosec();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    REQUIRE(time_ms >= expectwaittime_ms);
}


TEST_CASE("getTime of ModelTimer with restart") {
    data::Timer timer;
    init_Timer(timer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(10);

    std::this_thread::sleep_for(sleeptime_ms);
    timer.restart();
    std::this_thread::sleep_for(sleeptime_ms);
    auto time = timer.getTimeNanosec();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    REQUIRE(time_ms >= expectwaittime_ms);
}

TEST_CASE("getTime of ModelTimer with stop") {
    data::Timer timer;
    init_Timer(timer);

    std::chrono::milliseconds sleeptime_ms(10);
    std::chrono::milliseconds expectwaittime_ms(0);

    std::this_thread::sleep_for(sleeptime_ms);
    timer.stop();
    auto time = timer.getTimeNanosec();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);

    REQUIRE(time_ms <= expectwaittime_ms);
}
