#include "doctest.h"

#include "dateutil.h"



TEST_CASE("Not leap year 1800") { CHECK_FALSE(dateutil::is_leap_year(1800)); }

TEST_CASE("Not leap year 1900") { CHECK_FALSE(dateutil::is_leap_year(1900)); }

TEST_CASE("Not leap year 2011") { CHECK_FALSE(dateutil::is_leap_year(2011)); }

TEST_CASE("Not leap year 2100") { CHECK_FALSE(dateutil::is_leap_year(2100)); }



TEST_CASE("leap year 2000") { CHECK(dateutil::is_leap_year(2000)); }

TEST_CASE("leap year 2012") { CHECK(dateutil::is_leap_year(2012)); }

TEST_CASE("leap year 2016") { CHECK(dateutil::is_leap_year(2016)); }

TEST_CASE("leap year 2020") { CHECK(dateutil::is_leap_year(2020)); }

TEST_CASE("leap year 2024") { CHECK(dateutil::is_leap_year(2024)); }

TEST_CASE("leap year 2076") { CHECK(dateutil::is_leap_year(2076)); }

TEST_CASE("leap year 2400") { CHECK(dateutil::is_leap_year(2400)); }



TEST_CASE("Days of month Feb. in not leap year 1800") {
    CHECK(28 == dateutil::days_in_month(1800, 2));
}

TEST_CASE("Days of month Jan. in not leap year 1900") {
    CHECK(31 == dateutil::days_in_month(1900, 1));
}

TEST_CASE("Days of month Mar. in not leap year 2011") {
    CHECK(30 == dateutil::days_in_month(2011, 3));
}



TEST_CASE("Days of month Feb. in leap year 2000") {
    CHECK(29 == dateutil::days_in_month(2000, 2));
}

TEST_CASE("Days of month Jan. in leap year 2012") {
    CHECK(31 == dateutil::days_in_month(2012, 1));
}

TEST_CASE("Days of month Mar. in leap year 2016") {
    CHECK(30 == dateutil::days_in_month(2016, 3));
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

    SUBCASE("Is ticks right") { CHECK(ticks_ms == ticks); }
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

    SUBCASE("Is year right") { CHECK(datetime.year == year); }

    SUBCASE("Is month right") { CHECK(datetime.month == month); }

    SUBCASE("Is day right") { CHECK(datetime.day == day); }

    SUBCASE("Is hour right") { CHECK(datetime.hour == hour); }

    SUBCASE("Is minute right") { CHECK(datetime.minute == minute); }

    SUBCASE("Is second right") { CHECK(datetime.second == second); }
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

    SUBCASE("Is ticks right") { CHECK(ticks_ms == ticks); }

    SUBCASE("Is year right") { CHECK(datetime.year == year); }

    SUBCASE("Is month right") { CHECK(datetime.month == month); }

    SUBCASE("Is day right") { CHECK(datetime.day == day); }

    SUBCASE("Is hour right") { CHECK(datetime.hour == hour); }

    SUBCASE("Is minute right") { CHECK(datetime.minute == minute); }

    SUBCASE("Is second right") { CHECK(datetime.second == second); }
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

    SUBCASE("Is year right") { CHECK(datetime.year == year); }

    SUBCASE("Is month right") { CHECK(datetime.month == month); }

    SUBCASE("Is day right") { CHECK(datetime.day == day); }

    SUBCASE("Is hour right") { CHECK(datetime.hour == hour); }

    SUBCASE("Is minute right") { CHECK(datetime.minute == minute); }

    SUBCASE("Is second right") { CHECK(datetime.second == second); }
}
