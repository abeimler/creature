#include "doctest.h"

#include "basic.hpp"

TEST_CASE("zero value (0.0)") {
    double value = 0.0;

    REQUIRE(util::iszero(value));
}

TEST_CASE("none zero value (1.0)") {
    double value = 1.0;

    REQUIRE_FALSE(util::iszero(value));
}

TEST_CASE("none zero value (-1.0)") {
    double value = -1.0;

    REQUIRE_FALSE(util::iszero(value));
}

TEST_CASE("none zero value (DOUBLE_MIN)") {
    auto value = std::numeric_limits<double>::min();

    REQUIRE_FALSE(util::iszero(value));
}

TEST_CASE("none zero value (DOUBLE_LOWEST)") {
    auto value = std::numeric_limits<double>::lowest();

    REQUIRE_FALSE(util::iszero(value));
}

TEST_CASE("none zero value (infinity)") {
    auto value = std::numeric_limits<double>::infinity();

    REQUIRE_FALSE(util::iszero(value));
}
