#include <cereal/archives/json.hpp>
#include <fstream>
#include <json.hpp>

#include "doctest.h"

#include "Data/Element.h"


class ElementTest {
    public:
    static const std::string NAME;

    static void init_Element(data::Element& element) { element.setName(NAME); }
};
const std::string ElementTest::NAME = "Fire";



TEST_CASE("data::Element serial json") {
    data::Element data;

    ElementTest::init_Element(data);

    SUBCASE("serial json") {
        std::stringstream ss;
        {
            cereal::JSONOutputArchive outar(ss);

            CHECK_NOTHROW(outar(cereal::make_nvp("data", data)));
        }

        std::string output = ss.str();
        REQUIRE(!output.empty());

        SUBCASE("deserial json") {
            {
                cereal::JSONInputArchive inar(ss);

                CHECK_NOTHROW(inar(cereal::make_nvp("data", data)));
            }
        }
    }
}



TEST_CASE("data::Element serial json as file") {
    data::Element data;

    ElementTest::init_Element(data);

    SUBCASE("serial json") {
        std::ofstream os("element.json");
        {
            cereal::JSONOutputArchive outar(os);

            CHECK_NOTHROW(outar(cereal::make_nvp("data", data)));
        }
    }
}