#include <thread>

#include "doctest.h"

#include "Entity/Game/ProgressTimerUtil.h"

#include "Entity/Game/EntityGameTestHelper.h"




TEST_CASE("start ProgressTimer") {
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    gamecomp::ProgressTimer progresstimer;
    EntityGameTestHelper::init_ProgressTimer(progresstimer_util_, progresstimer);

    progresstimer_util_.start(progresstimer);

    SUBCASE("DateProgressTimer is started") {
        CHECK(progresstimer.timer.isstart);
    }

    SUBCASE("DateProgressTimer is not paused") {
        CHECK_FALSE(progresstimer.timer.ispause);
    }
}



TEST_CASE("pause without start ProgressTimer") {
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    gamecomp::ProgressTimer progresstimer;
    EntityGameTestHelper::init_ProgressTimer(progresstimer_util_, progresstimer);

    progresstimer_util_.pause(progresstimer);

    SUBCASE("ProgressTimer is started") {
        CHECK_FALSE(progresstimer.timer.isstart);
    }

    SUBCASE("ProgressTimer is paused") {
        CHECK_FALSE(progresstimer.timer.ispause);
    }
}


TEST_CASE("start and pause ProgressTimer") {
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    gamecomp::ProgressTimer progresstimer;
    EntityGameTestHelper::init_ProgressTimer(progresstimer_util_, progresstimer);

    progresstimer_util_.start(progresstimer);
    progresstimer_util_.pause(progresstimer);

    SUBCASE("ProgressTimer is started") {
        CHECK(progresstimer.timer.isstart);
    }

    SUBCASE("ProgressTimer is paused") { REQUIRE(progresstimer.timer.ispause); }
}



TEST_CASE("unpause without pause ProgressTimer") {
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    gamecomp::ProgressTimer progresstimer;
    EntityGameTestHelper::init_ProgressTimer(progresstimer_util_, progresstimer);

    progresstimer_util_.unpause(progresstimer);

    SUBCASE("ProgressTimer is not started") {
        CHECK_FALSE(progresstimer.timer.isstart);
    }

    SUBCASE("ProgressTimer is not paused") {
        CHECK_FALSE(progresstimer.timer.ispause);
    }
}

TEST_CASE("start unpause without paused ProgressTimer") {
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    gamecomp::ProgressTimer progresstimer;
    EntityGameTestHelper::init_ProgressTimer(progresstimer_util_, progresstimer);

    progresstimer_util_.start(progresstimer);
    progresstimer_util_.unpause(progresstimer);

    SUBCASE("ProgressTimer is started") {
        CHECK(progresstimer.timer.isstart);
    }

    SUBCASE("ProgressTimer is not paused") {
        CHECK_FALSE(progresstimer.timer.ispause);
    }
}

TEST_CASE("start pause and unpause ProgressTimer") {
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    gamecomp::ProgressTimer progresstimer;
    EntityGameTestHelper::init_ProgressTimer(progresstimer_util_, progresstimer);

    progresstimer_util_.start(progresstimer);
    progresstimer_util_.pause(progresstimer);
    progresstimer_util_.unpause(progresstimer);

    SUBCASE("ProgressTimer is started") {
        CHECK(progresstimer.timer.isstart);
    }

    SUBCASE("ProgressTimer is not paused") {
        CHECK_FALSE(progresstimer.timer.ispause);
    }
}


TEST_CASE("restart ProgressTimer") {
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    gamecomp::ProgressTimer progresstimer;
    EntityGameTestHelper::init_ProgressTimer(progresstimer_util_, progresstimer);

    progresstimer_util_.restart(progresstimer);

    SUBCASE("ProgressTimer is started") {
        CHECK(progresstimer.timer.isstart);
    }

    SUBCASE("ProgressTimer is not paused") {
        CHECK_FALSE(progresstimer.timer.ispause);
    }
}



TEST_CASE("stop ProgressTimer") {
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    gamecomp::ProgressTimer progresstimer;
    EntityGameTestHelper::init_ProgressTimer(progresstimer_util_, progresstimer);

    progresstimer_util_.stop(progresstimer);

    SUBCASE("ProgressTimer is not started") {
        CHECK_FALSE(progresstimer.timer.isstart);
    }

    SUBCASE("ProgressTimer is not paused") {
        CHECK_FALSE(progresstimer.timer.ispause);
    }
}
