#include "doctest.h"

#include "util.h"

TEST_CASE("random value of range 0-10") {
    int min = 0;
    int max = 10;

    int value = util::random(min, max);

    SUBCASE("value is >= min") { CHECK(value >= min); }

    SUBCASE("value is <= max") { CHECK(value <= max); }
}

TEST_CASE("random value of range 0-10 with seed 5468792135") {
    int min = 0;
    int max = 10;
    int64_t seed = 5468792135L;
    int64_t seednumber = 8; // gen number from the specific seed

    std::default_random_engine gen(seed);

    int value = util::random(min, max, gen);

    SUBCASE("value generadred with seed 5468792135") {
        CHECK(value == seednumber);
    }

    SUBCASE("value is >= min") { CHECK(value >= min); }

    SUBCASE("value is <= max") { CHECK(value <= max); }
}



TEST_CASE("random value of range 0-10 (size_t)") {
    size_t min = 0;
    size_t max = 10;

    size_t value = util::random(min, max);

    SUBCASE("value is >= min") { CHECK(value >= min); }

    SUBCASE("value is <= max") { CHECK(value <= max); }
}


TEST_CASE("random value of range 0-10 (double)") {
    double min = 0;
    double max = 10;

    double value = util::random(min, max);

    SUBCASE("value is >= min") { CHECK(value >= min); }

    SUBCASE("value is <= max") { CHECK(value <= max); }
}



TEST_CASE("0:1 loses") { CHECK_FALSE(util::randomOdds(0, 1)); }

TEST_CASE("1:0 wins") { CHECK(util::randomOdds(1, 0)); }



TEST_CASE("more then 100% wins") { CHECK(util::randomRate(101)); }

TEST_CASE("100% wins") { CHECK(util::randomRate(100)); }

TEST_CASE("0% loses") { CHECK_FALSE(util::randomRate(0)); }


TEST_CASE("random value of range 0-100 with gen seed 'Spike the Dragon'") {
    int min = 0;
    int max = 100;

    std::string seedstr = "Spike the Dragon";
    auto gen = util::genseed(seedstr);

    int value = util::random(min, max, gen);

    SUBCASE("value is ") { CHECK(value == 43); }
}
