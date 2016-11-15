#include "benchpress/benchpress.hpp"

#include "dateutil.h"
#include "util.h"


BENCHMARK("dateutil::is_leap_year 4", [](benchpress::context* ctx) {
    int year = 4;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = dateutil::is_leap_year(year);
        benchpress::escape(&ret);
    }
})

BENCHMARK("dateutil::is_leap_year 100", [](benchpress::context* ctx) {
    int year = 100;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = dateutil::is_leap_year(year);
        benchpress::escape(&ret);
    }
})

BENCHMARK("dateutil::is_leap_year 300", [](benchpress::context* ctx) {
    int year = 300;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = dateutil::is_leap_year(year);
        benchpress::escape(&ret);
    }
})

BENCHMARK("dateutil::is_leap_year 400", [](benchpress::context* ctx) {
    int year = 400;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = dateutil::is_leap_year(year);
        benchpress::escape(&ret);
    }
})



BENCHMARK("dateutil::days_in_month 400 12", [](benchpress::context* ctx) {
    int year = 400;
    int month = 12;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = dateutil::days_in_month(year, month);
        benchpress::escape(&ret);
    }
})

BENCHMARK("dateutil::days_in_month 1991 08", [](benchpress::context* ctx) {
    int year = 1991;
    int month = 8;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = dateutil::days_in_month(year, month);
        benchpress::escape(&ret);
    }
})



BENCHMARK("dateutil::datetime_to_ticks 0000-00-00T00:00:00",
          [](benchpress::context* ctx) {
              int year = 0;
              int month = 0;
              int day = 0;
              int hour = 0;
              int minute = 0;
              int second = 0;

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                  auto ret = dateutil::datetime_to_ticks(year, month, day, hour,
                                                         minute, second);
                  benchpress::escape(&ret);
              }
          })


BENCHMARK("dateutil::datetime_to_ticks 1991-07-08T12:13:14",
          [](benchpress::context* ctx) {
              int year = 1991;
              int month = 8;
              int day = 7;
              int hour = 12;
              int minute = 13;
              int second = 14;

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                  auto ret = dateutil::datetime_to_ticks(year, month, day, hour,
                                                         minute, second);
                  benchpress::escape(&ret);
              }
          })



BENCHMARK("dateutil::datetime_to_ticks 9999-12-31T23:59:59",
          [](benchpress::context* ctx) {
              int year = 9999;
              int month = 12;
              int day = 31;
              int hour = 23;
              int minute = 59;
              int second = 59;

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                  auto ret = dateutil::datetime_to_ticks(year, month, day, hour,
                                                         minute, second);
                  benchpress::escape(&ret);
              }
          })



BENCHMARK("dateutil::date_part 1991-07-08T12:13:14 Year",
          [](benchpress::context* ctx) {
              int year = 1991;
              int month = 8;
              int day = 7;
              int hour = 12;
              int minute = 13;
              int second = 14;

              auto ticks = dateutil::datetime_to_ticks(year, month, day, hour,
                                                       minute, second);

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                  auto ret =
                      dateutil::date_part(ticks, dateutil::DatePart::Year);
                  benchpress::escape(&ret);
              }
          })


BENCHMARK("dateutil::date_part 1991-07-08T12:13:14 Month",
          [](benchpress::context* ctx) {
              int year = 1991;
              int month = 8;
              int day = 7;
              int hour = 12;
              int minute = 13;
              int second = 14;

              auto ticks = dateutil::datetime_to_ticks(year, month, day, hour,
                                                       minute, second);

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                  auto ret =
                      dateutil::date_part(ticks, dateutil::DatePart::Month);
                  benchpress::escape(&ret);
              }
          })




BENCHMARK("dateutil::date_part 1991-07-08T12:13:14 Day",
          [](benchpress::context* ctx) {
              int year = 1991;
              int month = 8;
              int day = 7;
              int hour = 12;
              int minute = 13;
              int second = 14;

              auto ticks = dateutil::datetime_to_ticks(year, month, day, hour,
                                                       minute, second);

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                  auto ret =
                      dateutil::date_part(ticks, dateutil::DatePart::Day);
                  benchpress::escape(&ret);
              }
          })



BENCHMARK("dateutil::ticks_to_datetime 1991-07-08T12:13:14",
          [](benchpress::context* ctx) {
              int year = 1991;
              int month = 8;
              int day = 7;
              int hour = 12;
              int minute = 13;
              int second = 14;

              auto ticks = dateutil::datetime_to_ticks(year, month, day, hour,
                                                       minute, second);

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                  auto ret = dateutil::ticks_to_datetime(ticks);
                  benchpress::escape(&ret);
              }
          })


BENCHMARK("dateutil::ticks_to_datetime 9999-12-31T23:59:59",
          [](benchpress::context* ctx) {
              int year = 9999;
              int month = 12;
              int day = 31;
              int hour = 23;
              int minute = 59;
              int second = 59;

              auto ticks = dateutil::datetime_to_ticks(year, month, day, hour,
                                                       minute, second);

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                  auto ret = dateutil::ticks_to_datetime(ticks);
                  benchpress::escape(&ret);
              }
          })