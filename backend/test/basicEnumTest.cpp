#include "doctest.h"

#include "enum_array.h"

BETTER_ENUM(TestEnum, size_t, BEGIN = 0, None = BEGIN, Type1 = 1, Type2 = 2,
            Type3 = 3, Type4 = 4, END)



TEST_CASE("value at Type2") {
    earr::enum_array<TestEnum, int> enumarr = {{0, 1, 2, 3, 4}};
    TestEnum index = +TestEnum::Type2;

    CHECK(2 == earr::enum_array_at(enumarr, index));
}

TEST_CASE("value at Type2 (const)") {
    const earr::enum_array<TestEnum, int> enumarr = {{0, 1, 2, 3, 4}};
    TestEnum index = +TestEnum::Type2;

    CHECK(2 == earr::enum_array_at(enumarr, index));
}



TEST_CASE("Iterator at begin (TestEnum::None)") {
    earr::enum_array<TestEnum, int> enumarr = {{0, 1, 2, 3, 4}};
    TestEnum index = +TestEnum::None;

    CHECK(std::begin(enumarr) == earr::enum_array_at_it(enumarr, index));
}

TEST_CASE("Iterator at begin (TestEnum::None) (const)") {
    const earr::enum_array<TestEnum, int> enumarr = {{0, 1, 2, 3, 4}};
    TestEnum index = +TestEnum::None;

    CHECK(std::begin(enumarr) == earr::enum_array_at_it(enumarr, index));
}



TEST_CASE("Set Value at Type2 to 10") {
    earr::enum_array<TestEnum, int> enumarr = {{0, 1, 2, 3, 4}};

    int value = 10;
    TestEnum index = +TestEnum::Type2;

    earr::enum_array_set(enumarr, index, value);

    CHECK(value == earr::enum_array_at(enumarr, index));
}


TEST_CASE("Iterate over all elements and set Value to 10") {
    earr::enum_array<TestEnum, int> enumarr = {{0, 1, 2, 3, 4}};

    int value = 10;
    for (auto it = std::begin(enumarr); it != std::end(enumarr); ++it) {
        (*it) = value;
    }

    CHECK(value == enumarr.back());
}

TEST_CASE("Iterate over all elements and set Value to 10 (foreach)") {
    earr::enum_array<TestEnum, int> enumarr = {{0, 1, 2, 3, 4}};

    int value = 10;
    for (auto& v : enumarr) {
        v = value;
    }

    CHECK(value == enumarr.back());
}


TEST_CASE("Set all Values to 10") {
    earr::enum_array<TestEnum, int> enumarr = {{0, 1, 2, 3, 4}};

    int value = 10;
    earr::enum_array_fill(enumarr, value);

    CHECK(value == enumarr.back());
}


TEST_CASE("Get array-Index of Type1") {
    earr::enum_array<TestEnum, int> enumarr = {{0, 1, 2, 3, 4}};

    size_t index = 1;
    TestEnum enum_index = +TestEnum::Type1;

    CHECK(index == earr::enum_to_index(enumarr, enum_index));
}

TEST_CASE("foreach enum") {
    size_t count = 0;

    for (auto e : earr::Enum<TestEnum>()) {
        count++;
    }

    CHECK(5 == count);
}

TEST_CASE("foreach enum ++iterator") {
    size_t count = 0;

    auto e = earr::Enum<TestEnum>();
    for (auto it = e.begin(); it != e.end(); ++it) {
        count++;
    }

    CHECK(5 == count);
}

TEST_CASE("foreach enum iterator++") {
    size_t count = 0;

    auto e = earr::Enum<TestEnum>();
    for (auto it = e.begin(); it != e.end(); it++) {
        count++;
    }

    CHECK(5 == count);
}