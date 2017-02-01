#ifndef UTIL_H_
#define UTIL_H_

#include <cstdint>
#include <cstdlib>
#include <ctime>

#include <string>
#include <random>
#include <type_traits>

#include <clamp.hpp>

class util {
    public:
    template <typename T>
    static bool iszero(T a) {
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

    template <class Generator>
    static double rand(Generator& gen) {
        return random(0.0, 1.0, gen);
    }

    template <typename T>
    static bool randomRate(T percent) {
        if (percent >= 100.0) {
            return true;
        }

        if (iszero(percent)) {
            return false;
        }

        static std::mt19937 gen(rdseed());

        double_t percent_d = static_cast<double>(percent);
        auto probability = percent_d / 100.0;

        std::bernoulli_distribution dis (probability);
        return dis(gen);
    }


    static int random_int(int lowest_number, int highest_number);
    static int64_t random_int64(int64_t lowest_number, int64_t highest_number);
    static size_t random_uint(size_t lowest_number, size_t highest_number);
    static float random_float(float lowest_number, float highest_number);
    static double random_double(double lowest_number, double highest_number);

    inline static int random(int lowest_number, int highest_number) { return random_int(lowest_number, highest_number); }
    inline static int64_t random(int64_t lowest_number, int64_t highest_number) { return random_int64(lowest_number, highest_number); }
    inline static size_t random(size_t lowest_number, size_t highest_number){ return random_uint(lowest_number, highest_number); }
    inline static float random(float lowest_number, float highest_number){ return random_float(lowest_number, highest_number); }
    inline static double random(double lowest_number, double highest_number){ return random_double(lowest_number, highest_number); }

    static bool randomOdds(int wins, int losses);

    static std::mt19937 genseed(std::string seedstr);

    private:
    static unsigned int rdseed();
};

#endif // UTIL_HP_
