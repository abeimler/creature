#include "util.h"



int util::random(int lowest_number, int highest_number) {
    static std::mt19937 gen(rdseed());
    return random(lowest_number, highest_number, gen);
}

int64_t util::random(int64_t lowest_number, int64_t highest_number) {
    static std::mt19937_64 gen(rdseed());
    return random(lowest_number, highest_number, gen);
}

size_t util::random(size_t lowest_number, size_t highest_number) {
    static std::mt19937 gen(rdseed());
    return random(lowest_number, highest_number, gen);
}

float util::random(float lowest_number, float highest_number) {
    static std::mt19937 gen(rdseed());
    return random(lowest_number, highest_number, gen);
}

double util::random(double lowest_number, double highest_number) {
    static std::mt19937 gen(rdseed());
    return random(lowest_number, highest_number, gen);
}

bool util::randomOdds(int wins, int losses) {
    if (wins == 0) {
        return false;
    }

    if (losses == 0) {
        return true;
    }

    static std::mt19937 gen(rdseed());

    double probability = static_cast<double>(wins) / (wins + losses);
    // double q = 1.0 - p;

    std::bernoulli_distribution dis(probability);
    return dis(gen);
}

unsigned int util::rdseed() {
#ifndef HAS_NO_CXX11_RANDOM_DEVICE
    static std::random_device rd;
    return rd();
#else
#ifndef HAS_NO_CXX11_DEFAULT_RANDOM_DEVICE
    static std::default_random_engine generator(time(0));
    static std::uniform_int_distribution<unsigned int> dis;
    return dis(generator);
#else
    std::srand(std::time(0));
    return std::rand();
#endif
#endif
}