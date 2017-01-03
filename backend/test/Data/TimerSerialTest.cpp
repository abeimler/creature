#include <fstream>
#include <thread>

#include <cereal/archives/json.hpp>
#include <json.hpp>


#include "doctest.h"

#include "Data/Timer.h"



static void init_start_Timer(data::Timer& timer) { timer.start(); }

static void init_stop_Timer(data::Timer& timer) { timer.stop(); }


TEST_CASE("data::Timer serial json") {
    data::Timer data;

    init_start_Timer(data);

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

    init_start_Timer(data);

    SUBCASE("serial json") {
        std::ofstream os("timer.start.json");
        {
            cereal::JSONOutputArchive outar(os);

            CHECK_NOTHROW(outar(cereal::make_nvp("data", data)));
        }
    }
}

TEST_CASE("data::Timer serial json as file") {
    data::Timer data;

    init_stop_Timer(data);

    SUBCASE("serial json") {
        std::ofstream os("timer.stop.json");
        {
            cereal::JSONOutputArchive outar(os);

            CHECK_NOTHROW(outar(cereal::make_nvp("data", data)));
        }
    }
}