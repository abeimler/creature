#include "doctest.h"

#include "basic.hpp"

TEST_CASE("random value of range 0-10") {
    int min = 0;
    int max = 10;

    int value = util::random(min, max);

    SUBCASE("value is >= min") { REQUIRE(value >= min); }

    SUBCASE("value is <= max") { REQUIRE(value <= max); }
}

TEST_CASE("random value of range 0-10 with seed 5468792135") {
    int min = 0;
    int max = 10;
    int64_t seed = 5468792135L;
    int64_t seednumber = 8; // gen number from the specific seed

    std::default_random_engine gen(seed);

    int value = util::random(min, max, gen);

    SUBCASE("value generadred with seed 5468792135") {
        REQUIRE(value == seednumber);
    }

    SUBCASE("value is >= min") { REQUIRE(value >= min); }

    SUBCASE("value is <= max") { REQUIRE(value <= max); }
}



TEST_CASE("random value of range 0-10 (size_t)") {
    size_t min = 0;
    size_t max = 10;

    size_t value = util::random(min, max);

    SUBCASE("value is >= min") { REQUIRE(value >= min); }

    SUBCASE("value is <= max") { REQUIRE(value <= max); }
}


TEST_CASE("random value of range 0-10 (double)") {
    double min = 0;
    double max = 10;

    double value = util::random(min, max);

    SUBCASE("value is >= min") { REQUIRE(value >= min); }

    SUBCASE("value is <= max") { REQUIRE(value <= max); }
}



TEST_CASE("0:1 loses") { REQUIRE_FALSE(util::randomOdds(0, 1)); }

TEST_CASE("1:0 wins") { REQUIRE(util::randomOdds(1, 0)); }



TEST_CASE("more then 100% wins") { REQUIRE(util::randomRate(101)); }

TEST_CASE("100% wins") { REQUIRE(util::randomRate(100)); }

TEST_CASE("0% loses") { REQUIRE_FALSE(util::randomRate(0)); }
