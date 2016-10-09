#include "benchpress/benchpress.hpp"

#include "util.hpp"


BENCHMARK("util::iszero 0", [](benchpress::context* ctx) {
    int value = 0;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = util::iszero(value);
        benchpress::escape(&ret);
    }
})

BENCHMARK("util::iszero 0.0f", [](benchpress::context* ctx) {
    float valuezero = 0.0f;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = util::iszero(valuezero);
        benchpress::escape(&ret);
    }
})


BENCHMARK("util::random 1 1000", [](benchpress::context* ctx) {
    int min = 1;
    int max = 1000;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = util::random(min, max);
        benchpress::escape(&ret);
    }
})



BENCHMARK("util::randomRate 50", [](benchpress::context* ctx) {
    int rate = 50;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = util::randomRate(rate);
        benchpress::escape(&ret);
    }
})


BENCHMARK("util::randomOdds 1:1000", [](benchpress::context* ctx) {
    int wins = 1;
    int losses = 1000;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = util::randomOdds(wins, losses);
        benchpress::escape(&ret);
    }
})