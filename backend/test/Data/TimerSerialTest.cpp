#include <fstream>
#include <thread>

#include <json.hpp>

#include <cereal/archives/json.hpp>

#include "doctest.h"

#include "Data/Timer.h"



static void init_Timer(data::Timer& timer) { timer.start(); }



TEST_CASE("data::Timer serial json") {
    data::Timer data;

    init_Timer(data);

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



TEST_CASE("data::Timer serial json as file") {
    data::Timer data;

    init_Timer(data);

    SUBCASE("serial json") {
        std::ofstream os("timer.json");
        {
            cereal::JSONOutputArchive outar(os);

            CHECK_NOTHROW(outar(cereal::make_nvp("data", data)));
        }
    }
}