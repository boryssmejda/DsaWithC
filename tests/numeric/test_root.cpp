#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>
#include <numbers>

#include "dsa/numeric/root.h"

namespace
{
    constexpr double delta{1e-6};
}

TEST_CASE("Solving simple quadratic equation with 2 real solutions", "[root_newton]")
{
    auto f = [](double x) { return x * x - 4.0; }; // root at ±2
    auto g = [](double x) { return 2.0 * x; };

    std::array<double, 10> x{};
    const double expectedPositiveRoot = 2.0;
    const double expectedNegativeRoot = -2.0;

    SECTION("Find positive root")
    {
        x[0] = 1.0;
        size_t n = x.size();

        REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, delta) == DSA_ROOT_SUCCESS);
        REQUIRE(n <= 10);
        REQUIRE_THAT(x[n - 1], Catch::Matchers::WithinAbs(expectedPositiveRoot, delta));
    }

    SECTION("Find negative root")
    {
        x[0] = -2.5;
        size_t n = x.size();

        REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, delta) == DSA_ROOT_SUCCESS);
        REQUIRE(n <= 10);
        REQUIRE_THAT(x[n - 1], Catch::Matchers::WithinAbs(expectedNegativeRoot, delta));
    }
}

TEST_CASE("Non-polynomial function: sin(x)", "[root_newton]")
{
    auto f = [](double x) { return sin(x); };
    auto g = [](double x) { return cos(x); };
    std::array<double, 20> x{3.0}; // near pi

    size_t n = x.size();
    REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, delta) == DSA_ROOT_SUCCESS);
    REQUIRE_THAT(x[n - 1], Catch::Matchers::WithinAbs(std::numbers::pi_v, delta));
}

TEST_CASE("Maximum number of iterations exceeded", "[root_newton]")
{
    std::array<double, 10> x{-3.0};
    auto f = [](double x) { return x * x + 1.0; };
    auto g = [](double x) { return 2 * x; };
    size_t n = x.size();

    REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, delta) == DSA_ROOT_MAX_ITERATIONS);
    REQUIRE(x[0] != x[1]);
    for (size_t i = 1; i < n; ++i) {
        REQUIRE(std::isfinite(x[i]));
    }
}

TEST_CASE("Invalid input", "[root_newton]")
{
    auto f = [](double x) { return x; };
    auto g = [](double x) { return 1.0; };

    std::array<double, 5> x{1.0};
    size_t n = x.size();

    SECTION("Too small size of x")
    {
        size_t tooSmallSize = 1;
        REQUIRE(dsa_find_root_newton(f, g, x.data(), &tooSmallSize, delta) == DSA_ROOT_INVALID_ARGUMENT);
    }

    SECTION("Missing f function")
    {
        REQUIRE(dsa_find_root_newton(nullptr, g, x.data(), &n, delta) == DSA_ROOT_INVALID_ARGUMENT);
    }

    SECTION("Missing g derivative function")
    {
        REQUIRE(dsa_find_root_newton(f, nullptr, x.data(), &n, delta) == DSA_ROOT_INVALID_ARGUMENT);
    }

    SECTION("Missing x parameter")
    {
        REQUIRE(dsa_find_root_newton(f, g, nullptr, &n, delta) == DSA_ROOT_INVALID_ARGUMENT);
    }

    SECTION("Missing number of elements in x")
    {
        REQUIRE(dsa_find_root_newton(f, g, x.data(), nullptr, delta) == DSA_ROOT_INVALID_ARGUMENT);
    }

    SECTION("Delta equal to 0.0")
    {
        REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, 0.0) == DSA_ROOT_INVALID_ARGUMENT);
    }

    SECTION("Negative delta")
    {
        REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, -0.1) == DSA_ROOT_INVALID_ARGUMENT);
    }
}

TEST_CASE("Handling extreme values", "[root_newton]")
{
    std::array<double, 10> x{1.0};
    size_t n = x.size();

    SECTION("Handling Inf")
    {
        auto f = [](double x) { return 1.0; };
        auto g = [](double x) { return 0.0; };

        REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, delta) == DSA_ROOT_NUMERICAL_ERROR);
    }

    SECTION("Handling fx returning inf")
    {
        auto f = [](double x) { return std::numeric_limits<double>::infinity(); };
        auto g = [](double x) { return 1.0; };

        REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, delta) == DSA_ROOT_NUMERICAL_ERROR);
    }

    SECTION("Handling overflow resulting in Inf")
    {
        auto f = [](double x) { return 1e300; };
        auto g = [](double x) { return 1e-300; };

        REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, delta) == DSA_ROOT_NUMERICAL_ERROR);
    }

    SECTION("Handle division by 0")
    {
        auto f = [](double x) { return 2.0 * x; };
        auto g = [](double x) { return 0.0; };

        REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, delta) == DSA_ROOT_NUMERICAL_ERROR);
    }

    SECTION("Handling NaN")
    {
        auto f = [](double x) { return 0.0; };
        auto g = [](double x) { return 0.0; };

        REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, delta) == DSA_ROOT_NUMERICAL_ERROR);
    }
}

TEST_CASE("Checking algorithm converges when starting close to root", "[root_newton]")
{
    auto f = [](double x) { return x; };
    auto g = [](double x) { return 1.0; };
    std::array<double, 5> x{1e-8};
    size_t n = x.size();

    REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, delta) == DSA_ROOT_SUCCESS);
    REQUIRE_THAT(x[n - 1], Catch::Matchers::WithinAbs(0.0, delta));
}

TEST_CASE("Checking root on boundary", "[root_newton]")
{
    auto f = [](double x) { return x; };
    auto g = [](double x) { return 1.0; };
    std::array<double, 5> x{1.0};
    size_t n = x.size();

    REQUIRE(dsa_find_root_newton(f, g, x.data(), &n, delta) == DSA_ROOT_SUCCESS);
    REQUIRE_THAT(x[n - 1], Catch::Matchers::WithinAbs(0.0, delta));
}
