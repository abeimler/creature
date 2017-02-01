#include "util.h"



int util::random_int(int lowest_number, int highest_number) {
    static std::mt19937 gen(rdseed());
    return random(lowest_number, highest_number, gen);
}

int64_t util::random_int64(int64_t lowest_number, int64_t highest_number) {
    static std::mt19937_64 gen(rdseed());
    return random(lowest_number, highest_number, gen);
}

size_t util::random_uint(size_t lowest_number, size_t highest_number) {
    static std::mt19937 gen(rdseed());
    return random(lowest_number, highest_number, gen);
}

float util::random_float(float lowest_number, float highest_number) {
    static std::mt19937 gen(rdseed());
    return random(lowest_number, highest_number, gen);
}

double util::random_double(double lowest_number, double highest_number) {
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

    auto wins_d = static_cast<double>(wins);
    auto losses_d = static_cast<double>(losses);

    // p = W / (W + L)
    auto probability = wins_d / (wins_d + losses_d);

    std::bernoulli_distribution dis (probability);

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

std::mt19937 util::genseed(std::string seedstr) {

    int seed = 0;

    for (size_t i = 0; i < seedstr.size(); i += 2) {
        int character1 = (i < seedstr.size()) ? seedstr[i] : '\0';
        int character2 = (i + 1 < seedstr.size()) ? seedstr[i + 1] : '\0';
        int h = (character1 << 8) | character2;
        seed ^= h;
    }

    return std::mt19937(seed);
}