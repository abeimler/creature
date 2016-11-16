#include <string>

#include "benchpress/benchpress.hpp"


void unused_variables_func(int a, double b, std::string c, int ua, double ub, std::string uc) {
    a = a + 1;
    int d = a + static_cast<int>(b);
    c = "Hallo Welt!";
}

void unused_variables_func_opt(int a, double b, std::string c, int /*ua*/, double /*ub*/, std::string /*uc*/) {
    a = a + 1;
    int d = a + static_cast<int>(b);
    c = "Hallo Welt!";
}

BENCHMARK("unused variables function with unused parameters", [](benchpress::context* ctx) {
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        unused_variables_func(1, 2.0, "Hello", 42, 3.0, "Welt!");
    }
})

BENCHMARK("unused variables function without unused parameters", [](benchpress::context* ctx) {
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        unused_variables_func_opt(1, 2.0, "Hello", 42, 3.0, "Welt!");
    }
})