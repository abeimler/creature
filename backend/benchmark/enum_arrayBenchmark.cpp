#include "benchpress/benchpress.hpp"

#include "enum_array.h"
#include "util.h"

enum class TestKeys : size_t {
    BEGIN,
    Key1 = BEGIN,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    Key10,
    Key11,
    Key12,
    Key13,
    Key14,
    Key15,
    Key16,
    Key17,
    Key18,
    Key19,
    Key20,
    END
};

using test_enum_array = earr::enum_array<TestKeys, int>;

test_enum_array make_test_enum_array() { return test_enum_array(); }

int make_value() { return util::random(1, 42); }


BENCHMARK("earr::enum_array_at", [](benchpress::context* ctx) {
    auto arr = make_test_enum_array();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto& ret = earr::enum_array_at(arr, TestKeys::Key3);
        benchpress::escape(&ret);
    }
})

BENCHMARK("earr::enum_array_at const", [](benchpress::context* ctx) {
    const auto arr = make_test_enum_array();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        const auto& ret = earr::enum_array_at(arr, TestKeys::Key3);
        // benchpress::escape(&ret);
    }
})


BENCHMARK("earr::enum_array_at_it", [](benchpress::context* ctx) {
    auto arr = make_test_enum_array();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = earr::enum_array_at_it(arr, TestKeys::Key3);
        benchpress::escape(&ret);
    }
})

BENCHMARK("earr::enum_array_at_it const", [](benchpress::context* ctx) {
    const auto arr = make_test_enum_array();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto ret = earr::enum_array_at_it(arr, TestKeys::Key3);
        benchpress::escape(&ret);
    }
})

BENCHMARK("earr::enum_array_set", [](benchpress::context* ctx) {
    auto arr = make_test_enum_array();
    int value = make_value();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        earr::enum_array_set(arr, TestKeys::Key3, value);
    }
})

BENCHMARK("earr::enum_to_index", [](benchpress::context* ctx) {
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        size_t index = earr::enum_to_index(TestKeys::Key3);
        benchpress::escape(&index);
    }
})

BENCHMARK("earr::enum_array_fill", [](benchpress::context* ctx) {
    auto arr = make_test_enum_array();
    int value = make_value();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        earr::enum_array_fill(arr, value);
    }
})