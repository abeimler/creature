#include "doctest.h"

#include "basic.hpp"

enum class TestEnum : size_t {
    BEGIN = 0,
    None = BEGIN,
    Type1 = 1,
    Type2 = 2,
    Type3 = 3,
    Type4 = 4,
    END
};



TEST_CASE("value at Type2") {
    earr::enum_array<TestEnum, int> enumarr = {0, 1, 2, 3, 4};

    REQUIRE(2 == earr::enum_array_at(enumarr, TestEnum::Type2));
}

TEST_CASE("value at Type2 (const)") {
    const earr::enum_array<TestEnum, int> enumarr = {0, 1, 2, 3, 4};

    REQUIRE(2 == earr::enum_array_at(enumarr, TestEnum::Type2));
}



TEST_CASE("Iterator at begin (TestEnum::None)") {
    earr::enum_array<TestEnum, int> enumarr = {0, 1, 2, 3, 4};

    REQUIRE(std::begin(enumarr) ==
            earr::enum_array_at_it(enumarr, TestEnum::None));
}

TEST_CASE("Iterator at begin (TestEnum::None) (const)") {
    const earr::enum_array<TestEnum, int> enumarr = {0, 1, 2, 3, 4};

    REQUIRE(std::begin(enumarr) ==
            earr::enum_array_at_it(enumarr, TestEnum::None));
}



TEST_CASE("Set Value at Type2 to 10") {
    earr::enum_array<TestEnum, int> enumarr = {0, 1, 2, 3, 4};

    int value = 10;
    TestEnum index = TestEnum::Type2;

    earr::enum_array_set(enumarr, index, value);

    REQUIRE(value == earr::enum_array_at(enumarr, index));
}


TEST_CASE("Iterate over all elements and set Value to 10") {
    earr::enum_array<TestEnum, int> enumarr = {0, 1, 2, 3, 4};

    int value = 10;
    for (auto it = std::begin(enumarr); it != std::end(enumarr); ++it) {
        (*it) = value;
    }

    REQUIRE(value == enumarr.back());
}

TEST_CASE("Iterate over all elements and set Value to 10 (foreach)") {
    earr::enum_array<TestEnum, int> enumarr = {0, 1, 2, 3, 4};

    int value = 10;
    for (auto& v : enumarr) {
        v = value;
    }

    REQUIRE(value == enumarr.back());
}


TEST_CASE("Set all Values to 10") {
    earr::enum_array<TestEnum, int> enumarr = {0, 1, 2, 3, 4};

    int value = 10;
    earr::enum_array_fill(enumarr, value);

    REQUIRE(value == enumarr.back());
}


TEST_CASE("Get array-Index of Type1") {
    earr::enum_array<TestEnum, int> enumarr = {0, 1, 2, 3, 4};

    size_t index = 1;
    TestEnum enum_index = TestEnum::Type1;

    REQUIRE(index == earr::enum_to_index(enumarr, enum_index));
}
