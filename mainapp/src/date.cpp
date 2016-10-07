#include "date.hpp"

/*
int64_t dateutil::SECONDS_PER_DAY = 86400L;
int64_t dateutil::SECONDS_PER_HOUR = 3600L;
int64_t dateutil::SECONDS_PER_MINUTE = 60L;
int64_t dateutil::DAYS_IN_400 = 146097L;
int64_t dateutil::DAYS_IN_100 = 36524L;
int64_t dateutil::DAYS_IN_4 = 1461L;
*/

constexpr std::array<int, 13> dateutil::MONTH_DAYS;
constexpr std::array<int, 13> dateutil::MONTH_DAYS_LEAP;
