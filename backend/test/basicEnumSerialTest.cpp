#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "doctest.h"

#include <json.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/unordered_map.hpp>

#include "enum_array.h"


BETTER_ENUM(TestEnum, size_t, BEGIN = 0, None = BEGIN, Type1 = 1, Type2 = 2,
            Type3 = 3, Type4 = 4, END)

TEST_CASE("save better-enum serial binary") {
    TestEnum e = TestEnum::Type2;

    std::stringstream ss;
    {
        cereal::BinaryOutputArchive ar(ss);

        ar(e);
    }

    CHECK(!ss.str().empty());
}

TEST_CASE("load better-enum serial binary") {
    TestEnum e = TestEnum::END;

    auto value = +TestEnum::Type2;

    std::stringstream ss;
    {
        ss.write((char*)&value, sizeof(value));
        cereal::BinaryInputArchive ar(ss);

        ar(e);
    }

    CHECK(+TestEnum::Type2 == e);
}



TEST_CASE("save better-enum serial json") {
    TestEnum e = TestEnum::Type2;

    std::stringstream ss;
    {
        cereal::JSONOutputArchive ar(
            ss, cereal::JSONOutputArchive::Options::NoIndent());

        ar(CEREAL_NVP(e));
    }

    std::string expected = "{\n\"e\": \"Type2\"\n}";
    CHECK(expected == ss.str());
}

TEST_CASE("load better-enum serial json") {
    TestEnum e = TestEnum::END;

    std::stringstream ss;
    {
        ss << "{\n\"e\": \"Type2\"\n}";
        cereal::JSONInputArchive ar(ss);

        ar(CEREAL_NVP(e));
    }

    CHECK(e == +TestEnum::Type2);
}



TEST_CASE("enum_array serial json as file") {
    earr::enum_array<TestEnum, bool> arr;

    earr::enum_array_fill(arr, false);

    SUBCASE("serial json") {
        std::ofstream os("enum_array.json");
        {
            cereal::JSONOutputArchive outar(os);

            CHECK_NOTHROW(outar(cereal::make_nvp("arr", arr)));
        }
    }
}