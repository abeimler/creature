#include "doctest.h"

#include "date.hpp"



TEST_CASE("Not leap year 1800") { REQUIRE_FALSE(dateutil::is_leap_year(1800)); }

TEST_CASE("Not leap year 1900") { REQUIRE_FALSE(dateutil::is_leap_year(1900)); }

TEST_CASE("Not leap year 2011") { REQUIRE_FALSE(dateutil::is_leap_year(2011)); }

TEST_CASE("Not leap year 2100") { REQUIRE_FALSE(dateutil::is_leap_year(2100)); }



TEST_CASE("leap year 2000") { REQUIRE(dateutil::is_leap_year(2000)); }

TEST_CASE("leap year 2012") { REQUIRE(dateutil::is_leap_year(2012)); }

TEST_CASE("leap year 2016") { REQUIRE(dateutil::is_leap_year(2016)); }

TEST_CASE("leap year 2020") { REQUIRE(dateutil::is_leap_year(2020)); }

TEST_CASE("leap year 2024") { REQUIRE(dateutil::is_leap_year(2024)); }

TEST_CASE("leap year 2076") { REQUIRE(dateutil::is_leap_year(2076)); }

TEST_CASE("leap year 2400") { REQUIRE(dateutil::is_leap_year(2400)); }



TEST_CASE("Days of month Feb. in not leap year 1800") {
    REQUIRE(28 == dateutil::days_in_month(1800, 2));
}

TEST_CASE("Days of month Jan. in not leap year 1900") {
    REQUIRE(31 == dateutil::days_in_month(1900, 1));
}

TEST_CASE("Days of month Mar. in not leap year 2011") {
    REQUIRE(30 == dateutil::days_in_month(2011, 3));
}



TEST_CASE("Days of month Feb. in leap year 2000") {
    REQUIRE(29 == dateutil::days_in_month(2000, 2));
}

TEST_CASE("Days of month Jan. in leap year 2012") {
    REQUIRE(31 == dateutil::days_in_month(2012, 1));
}

TEST_CASE("Days of month Mar. in leap year 2016") {
    REQUIRE(30 == dateutil::days_in_month(2016, 3));
}



TEST_CASE("datetime to ticks") {
    int year = 1991;
    int month = 8;
    int day = 7;
    int hour = 15;
    int minute = 3;
    int second = 59;
    std::chrono::milliseconds ticks(62817174239000LL);

    auto ticks_ms = dateutil::datetime_to_ticks<std::chrono::milliseconds>(
        year, month, day, hour, minute, second);

    SUBCASE("Is ticks right") { REQUIRE(ticks_ms == ticks); }
}

TEST_CASE("ticks to datetime") {
    int year = 1991;
    int month = 8;
    int day = 7;
    int hour = 15;
    int minute = 3;
    int second = 59;
    std::chrono::milliseconds ticks(62817174239000LL);

    auto datetime = dateutil::ticks_to_datetime(ticks);

    SUBCASE("Is year right") { REQUIRE(datetime.year == year); }

    SUBCASE("Is month right") { REQUIRE(datetime.month == month); }

    SUBCASE("Is day right") { REQUIRE(datetime.day == day); }

    SUBCASE("Is hour right") { REQUIRE(datetime.hour == hour); }

    SUBCASE("Is minute right") { REQUIRE(datetime.minute == minute); }

    SUBCASE("Is second right") { REQUIRE(datetime.second == second); }
}

TEST_CASE("DateTime to ticks and ticks to datetime") {
    int year = 1991;
    int month = 8;
    int day = 7;
    int hour = 15;
    int minute = 3;
    int second = 59;
    std::chrono::milliseconds ticks(62817174239000LL);

    auto ticks_ms = dateutil::datetime_to_ticks<std::chrono::milliseconds>(
        year, month, day, hour, minute, second);

    auto datetime = dateutil::ticks_to_datetime(ticks_ms);

    SUBCASE("Is ticks right") { REQUIRE(ticks_ms == ticks); }

    SUBCASE("Is year right") { REQUIRE(datetime.year == year); }

    SUBCASE("Is month right") { REQUIRE(datetime.month == month); }

    SUBCASE("Is day right") { REQUIRE(datetime.day == day); }

    SUBCASE("Is hour right") { REQUIRE(datetime.hour == hour); }

    SUBCASE("Is minute right") { REQUIRE(datetime.minute == minute); }

    SUBCASE("Is second right") { REQUIRE(datetime.second == second); }
}



TEST_CASE("DateTime to ticks and ticks to datetime. year 2038-problem") {
    int year = 2038;
    int month = 1;
    int day = 19;
    int hour = 3;
    int minute = 14;
    int second = 8;

    auto ticks_ms = dateutil::datetime_to_ticks<std::chrono::milliseconds>(
        year, month, day, hour, minute, second);

    auto datetime = dateutil::ticks_to_datetime(ticks_ms);

    SUBCASE("Is year right") { REQUIRE(datetime.year == year); }

    SUBCASE("Is month right") { REQUIRE(datetime.month == month); }

    SUBCASE("Is day right") { REQUIRE(datetime.day == day); }

    SUBCASE("Is hour right") { REQUIRE(datetime.hour == hour); }

    SUBCASE("Is minute right") { REQUIRE(datetime.minute == minute); }

    SUBCASE("Is second right") { REQUIRE(datetime.second == second); }
}
