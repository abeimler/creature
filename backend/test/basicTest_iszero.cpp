#include "doctest.h"

#include "util.h"

TEST_CASE("zero value (0.0)") {
    double value = 0.0;

    CHECK(util::iszero(value));
}

TEST_CASE("none zero value (1.0)") {
    double value = 1.0;

    CHECK_FALSE(util::iszero(value));
}

TEST_CASE("none zero value (-1.0)") {
    double value = -1.0;

    CHECK_FALSE(util::iszero(value));
}

TEST_CASE("none zero value (DOUBLE_MIN)") {
    auto value = std::numeric_limits<double>::min();

    CHECK_FALSE(util::iszero(value));
}

TEST_CASE("none zero value (DOUBLE_LOWEST)") {
    auto value = std::numeric_limits<double>::lowest();

    CHECK_FALSE(util::iszero(value));
}

TEST_CASE("none zero value (infinity)") {
    auto value = std::numeric_limits<double>::infinity();

    CHECK_FALSE(util::iszero(value));
}
