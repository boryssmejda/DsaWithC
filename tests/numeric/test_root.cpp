#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>

extern "C"
{
#include "dsa/numeric/root.h"
}

TEST_CASE("Newton root-finding: simple quadratic", "[root_newton]") {
    auto f = [](double x) { return x * x - 4.0; }; // root at ±2
    auto g = [](double x) { return 2.0 * x; };

    std::array<double, 10> x{};
    const double delta = 1e-6;
    const double expectedPositiveRoot = 2.0;
    const double expectedNegativeRoot = -2.0;

    SECTION("Find positive root")
    {
        x[0] = 1.0;
        size_t n = x.size();

        REQUIRE(root_newton(f, g, x.data(), &n, delta));
        REQUIRE(n <= 10);
        REQUIRE_THAT(x[n - 1], Catch::Matchers::WithinAbs(expectedPositiveRoot, delta));
    }

    SECTION("Find negative root")
    {
        x[0] = -2.5;
        size_t n = x.size();

        REQUIRE(root_newton(f, g, x.data(), &n, delta));
        REQUIRE(n <= 10);
        REQUIRE_THAT(x[n - 1], Catch::Matchers::WithinAbs(expectedNegativeRoot, delta));
    }
}

TEST_CASE("Newton root-finding: invalid input", "[root_newton]") {
    auto f = [](double x) { return x; };
    auto g = [](double x) { return 1.0; };

    std::array<double, 5> x{1.0};
    size_t n = x.size();
    const double delta = 1e-6;

    SECTION("Too small size of x")
    {
        size_t tooSmallSize = 1;
        REQUIRE_FALSE(root_newton(f, g, x.data(), &tooSmallSize, delta));
    }

    SECTION("Missing f function")
    {
        REQUIRE_FALSE(root_newton(nullptr, g, x.data(), &n, delta));
    }

    SECTION("Missing g derivative function")
    {
        REQUIRE_FALSE(root_newton(f, nullptr, x.data(), &n, delta));
    }

    SECTION("Missing x parameter")
    {
        REQUIRE_FALSE(root_newton(f, g, nullptr, &n, delta));
    }

    SECTION("Missing number of elements in x")
    {
        REQUIRE_FALSE(root_newton(f, g, x.data(), nullptr, delta));
    }

    SECTION("Delta equal to 0.0")
    {
        REQUIRE_FALSE(root_newton(f, g, x.data(), &n, 0.0));
    }

    SECTION("Negative delta")
    {
        REQUIRE_FALSE(root_newton(f, g, x.data(), &n, -0.1));
    }
}

TEST_CASE("Newton root-finding: division by zero", "[root_newton]") {
    auto f = [](double x) { return 2.0 * x; };
    auto g = [](double x) { return 0.0; }; // Derivative always zero

    std::array<double, 5> x{1.0};
    size_t n = x.size();
    const double delta = 1e-6;

    REQUIRE_FALSE(root_newton(f, g, x.data(), &n, delta));
}

TEST_CASE("Newton root-finding: NaN and Inf handling", "[root_newton]") {
    auto f = [](double x) { return x; };
    auto g = [](double x) { return x == 1.0 ? 1e-300 : 1.0; };

    std::array<double, 10> x{1.0};
    size_t n = x.size();
    const double delta = 1e-6;

    REQUIRE_FALSE(root_newton(f, g, x.data(), &n, delta)); // Causes large jump or inf
}
