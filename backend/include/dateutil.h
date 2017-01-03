#ifndef DATEUTIL_H_
#define DATEUTIL_H_

#include <ctime>

#include <algorithm>
#include <array>
#include <chrono>
#include <limits>
#include <tuple>

class dateutil {
    public:
    struct DateTimeResult {
        int64_t year;
        int64_t month;
        int64_t day;
        int64_t hour;
        int64_t minute;
        int64_t second;
    };

    enum class DatePart { Year, Month, Day };

    using days = std::chrono::duration<
        int, std::ratio_multiply<std::ratio<24>, std::chrono::hours::period>>;

    template <typename T>
    static constexpr bool is_leap_year(T year) {
        return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    }

    template <typename T, typename U>
    static constexpr int64_t days_in_month(T year, U month) {
        const auto& DIM = !is_leap_year(year) ? MONTH_DAYS : MONTH_DAYS_LEAP;

        return (month > 0 && static_cast<size_t>(month) < DIM.size())
                   ? DIM[month] - DIM[month - 1]
                   : 0;
    }

    template <class Duration = std::chrono::milliseconds>
    static Duration datetime_to_ticks(int year, int month, int day, int hour,
                                      int minute, int second) {

        const auto& DIM = (!is_leap_year(year)) ? MONTH_DAYS : MONTH_DAYS_LEAP;

        if (day == 0 && month == 0 && year == 0 && hour == 0 && minute == 0 &&
            second == 0) {
            return Duration::zero();
        }

        if (second >= 60) {
            minute += second / 60;
            second = second % 60;
        }
        if (minute >= 60) {
            hour += minute / 60;
            minute = minute % 60;
        }
        if (hour >= 24) {
            day += hour / 24;
            hour = hour % 24;
        }
        if (month > 12) {
            year += month / 12;
            month = month % 12;
        }

        if (year > 0) {
            year--;
        }

        int64_t leap_days =
            (year > 0) ? (year / 4) - (year / 100) + (year / 400) : 0;

        int64_t monthdays =
            (month > 0 && static_cast<size_t>(month) < DIM.size())
                ? DIM[month - 1]
                : 0;

        int64_t yeardays = year * 365;

        std::chrono::seconds ret =
            std::chrono::seconds(yeardays * SECONDS_PER_DAY) +
            std::chrono::seconds(leap_days * SECONDS_PER_DAY) +
            std::chrono::seconds(monthdays * SECONDS_PER_DAY) +
            std::chrono::seconds(((day > 0) ? day - 1 : 0) * SECONDS_PER_DAY) +
            std::chrono::hours(hour) + std::chrono::minutes(minute) +
            std::chrono::seconds(second);

        return std::chrono::duration_cast<Duration>(ret);
    }

    template <class Duration = std::chrono::milliseconds,
              typename Rep = typename Duration::rep>
    static Rep date_part(const Duration& ticks, DatePart part) {

        Rep result = 1; // Default to MIN_DATE parts

        if (ticks != Duration::zero()) {
            std::chrono::seconds ticks_sec =
                std::chrono::duration_cast<std::chrono::seconds>(ticks);

            // const auto& DIM = MONTH_DAYS;
            Rep total_days = ticks_sec.count() / SECONDS_PER_DAY;
            Rep span_400 = 0; // # of 400 year spans
            Rep span_100 = 0; // # of 100 year spans
            Rep span_4 = 0;   // # of 4 year spans
            Rep span = 0;     // # of years in the current span

            span_400 = total_days / DAYS_IN_400;

            // Remove all 400 year spans
            total_days -= span_400 * DAYS_IN_400;
            span_100 = total_days / DAYS_IN_100;

            // This year is a century leap year, but we don't care yet
            if (span_100 == 4) {
                span_100 = 3;
            }

            // Remove all 100 year spans
            total_days -= span_100 * DAYS_IN_100;
            span_4 = total_days / DAYS_IN_4;
            total_days -= span_4 * DAYS_IN_4; // Remove all 4 year spans
            span = total_days / 365;

            // This year is a leap year, but we still don't care yet
            if (span == 4) {
                span = 3;
            }

            // Remove elapsed years in the current span
            total_days -= span * 365;

            // Sum up all of the span years including the current one to get the
            // final year
            Rep year =
                (span_400 * 400) + (span_100 * 100) + (span_4 * 4) + span + 1;

            if (part == DatePart::Year) {
                return year;
            } else {
                // *Now* we care about the leap year for matching the month day
                const auto& DIML =
                    (!is_leap_year(year)) ? MONTH_DAYS : MONTH_DAYS_LEAP;

                // dim has 13 elements; dim[0] will never be a match in this
                // loop
                for (size_t m = 1; m <= 12 && m < DIML.size(); m++) {
                    if (total_days < DIML[m]) {
                        if (part == DatePart::Month) {
                            return m;
                        } else {
                            return total_days - DIML[m - 1] + 1;
                        }
                    }
                }
            }
        }

        return result;
    }

    template <class Duration = std::chrono::milliseconds>
    static DateTimeResult ticks_to_datetime(const Duration& ticks) {
        std::chrono::seconds ticks_sec =
            std::chrono::duration_cast<std::chrono::seconds>(ticks);

        std::chrono::hours hours(ticks_sec.count() % SECONDS_PER_DAY /
                                 SECONDS_PER_HOUR);
        std::chrono::minutes minutes(ticks_sec.count() % SECONDS_PER_HOUR /
                                     SECONDS_PER_MINUTE);
        std::chrono::seconds seconds(ticks_sec.count() % SECONDS_PER_MINUTE);

        DateTimeResult ret;
        ret.year = date_part(ticks_sec, DatePart::Year);
        ret.month = date_part(ticks_sec, DatePart::Month);
        ret.day = date_part(ticks_sec, DatePart::Day);
        ret.hour = hours.count();
        ret.minute = minutes.count();
        ret.second = seconds.count();

        return ret;
    }

    private:
    static constexpr int64_t SECONDS_PER_DAY = 86400L;
    static constexpr int64_t SECONDS_PER_HOUR = 3600L;
    static constexpr int64_t SECONDS_PER_MINUTE = 60L;
    static constexpr int64_t DAYS_IN_400 = 146097L;
    static constexpr int64_t DAYS_IN_100 = 36524L;
    static constexpr int64_t DAYS_IN_4 = 1461L;

    static constexpr std::array<int, 13> MONTH_DAYS = {
        0,
        31,
        31 + 28,
        31 + 28 + 30,
        31 + 28 + 31 + 30,
        31 + 28 + 31 + 30 + 31,
        31 + 28 + 31 + 30 + 31 + 30,
        31 + 28 + 31 + 30 + 31 + 30 + 31,
        31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
        31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
        31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
        31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30,
        31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31};

    static constexpr std::array<int, 13> MONTH_DAYS_LEAP = {
        0,
        31,
        31 + 29,
        31 + 29 + 30,
        31 + 29 + 31 + 30,
        31 + 29 + 31 + 30 + 31,
        31 + 29 + 31 + 30 + 31 + 30,
        31 + 29 + 31 + 30 + 31 + 30 + 31,
        31 + 29 + 31 + 30 + 31 + 30 + 31 + 31,
        31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
        31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
        31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30,
        31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31};
};

#endif // DATEUTIL_H_
