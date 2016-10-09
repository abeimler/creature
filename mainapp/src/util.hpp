#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <cstdint>
#include <ctime>

#include <random>
#include <type_traits>

class util {
    public:
    template <typename T>
    static typename std::enable_if<std::is_integral<T>::value, bool>::type
    iszero(T a) {
        return a == 0;
    }

    static bool iszero(float a) { return a >= 0.0f && a <= 0.0f; }

    static bool iszero(double a) { return a >= 0.0 && a <= 0.0; }

    template <class T, class Generator>
    static T random(T lowest_number, T highest_number, Generator& gen) {
        if (lowest_number == highest_number) {
            return lowest_number;
        }

        if (lowest_number > highest_number) {
            std::swap(lowest_number, highest_number);
        }

        std::uniform_int_distribution<T> dis(lowest_number, highest_number);
        return dis(gen);
    }


    template <class Generator>
    static double random(double lowest_number, double highest_number,
                         Generator& gen) {
        if (std::abs(highest_number - lowest_number) <
            std::numeric_limits<double>::epsilon()) {
            return lowest_number;
        }

        if (lowest_number > highest_number) {
            std::swap(lowest_number, highest_number);
        }

        std::uniform_real_distribution<double> dis(lowest_number,
                                                   highest_number);
        return dis(gen);
    }
    template <class Generator>
    static float random(float lowest_number, float highest_number,
                        Generator& gen) {
        if (std::fabs(highest_number - lowest_number) <
            std::numeric_limits<float>::epsilon()) {
            return lowest_number;
        }

        if (lowest_number > highest_number) {
            std::swap(lowest_number, highest_number);
        }

        std::uniform_real_distribution<float> dis(lowest_number,
                                                  highest_number);
        return dis(gen);
    }

    template <typename T>
    static bool randomRate(T percent) {
        if (percent >= 100.0) {
            return true;
        }

        if (iszero(percent)) {
            return false;
        }

#ifndef HAS_NO_CXX11_RANDOM_DEVICE
        auto rdseed = []() {
            static std::random_device rd;
            return rd();
        };
#else
        auto rdseed = []() {
            srand(time(std::mt19937));
            return rand();
        };
#endif

        static std::mt19937 gen(rdseed());

        double probability = static_cast<double>(percent) / 100.0;

        std::bernoulli_distribution dis(probability);
        return dis(gen);
    }


    static int random(int lowest_number, int highest_number);
    static int64_t random(int64_t lowest_number, int64_t highest_number);
    static size_t random(size_t lowest_number, size_t highest_number);
    static float random(float lowest_number, float highest_number);
    static double random(double lowest_number, double highest_number);
    static bool randomOdds(int wins, int losses);
};

#endif
