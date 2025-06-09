#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>

#include "dsa/numeric/polynomial_interpolation.h"

TEST_CASE("Interpolating constant function", "[interpolation]")
{
    const std::array<double, 1> x{5.0};
    const std::array<double, 1> fx{1.0};
    const std::array<double, 1> expectedCoefficients{1.0};

    std::array<double, 1> coefficients{};
    REQUIRE(dsa_interpolation_find_newton_coefficients(x.data(), fx.data(), coefficients.data(), x.size()));

    for (size_t i = 0; i < expectedCoefficients.size(); i++)
    {
        REQUIRE_THAT(coefficients[i], Catch::Matchers::WithinAbs(expectedCoefficients[i], 0.0001));
    }

    std::array<double, 3> z{-5.0, 0.0, 10.0};
    std::array<double, 3> pz{};
    std::array<double, 3> expectedFunctionValues{1.0, 1.0, 1.0};
    REQUIRE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), pz.data(), pz.size()));

    for (size_t i = 0; i < expectedFunctionValues.size(); i++)
    {
        REQUIRE_THAT(pz[i], Catch::Matchers::WithinAbs(expectedFunctionValues[i], 0.0001));
    }
}

TEST_CASE("Interpolating linear function", "[interpolation]")
{
    const std::array<double, 2> x{1.0, 2.0};
    const std::array<double, 2> fx{2.0, 4.0}; // f(x) = 2x
    const std::array<double, 2> expectedValues{2.0, 2.0};

    std::array<double, 2> coefficients{};

    REQUIRE(dsa_interpolation_find_newton_coefficients(
        x.data(), fx.data(), coefficients.data(), x.size()));

    for (size_t i = 0; i < expectedValues.size(); ++i)
    {
        REQUIRE_THAT(coefficients[i], Catch::Matchers::WithinAbs(expectedValues[i], 0.0001));
    }

    std::array<double, 3> z{-10.0, 5.0, 7.0};
    std::array<double, 3> pz{};
    std::array<double, 3> expectedFunctionValues{-20.0, 10.0, 14.0};
    REQUIRE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), pz.data(), pz.size()));

    for (size_t i = 0; i < expectedFunctionValues.size(); i++)
    {
        REQUIRE_THAT(pz[i], Catch::Matchers::WithinAbs(expectedFunctionValues[i], 0.0001));
    }
}

TEST_CASE("Interpolating quadratic function", "[interpolation]")
{
    const std::array<double, 3> x{-1.0, 1.0, 2.0};
    const std::array<double, 3> fx{2.0, 2.0, 5.0}; // f(x) = x^2 + 1
    const std::array<double, 3> expectedValues{2.0, 0.0, 1.0};

    std::array<double, 3> coefficients{};

    REQUIRE(dsa_interpolation_find_newton_coefficients(
        x.data(), fx.data(), coefficients.data(), x.size()));

    for (size_t i = 0; i < expectedValues.size(); ++i)
    {
        REQUIRE_THAT(coefficients[i], Catch::Matchers::WithinAbs(expectedValues[i], 0.0001));
    }

    std::array<double, 3> z{-3.0, 0, 7.0};
    std::array<double, 3> pz{};
    std::array<double, 3> expectedFunctionValues{10.0, 1.0, 50.0};
    REQUIRE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), pz.data(), pz.size()));

    for (size_t i = 0; i < expectedFunctionValues.size(); i++)
    {
        REQUIRE_THAT(pz[i], Catch::Matchers::WithinAbs(expectedFunctionValues[i], 0.0001));
    }
}

TEST_CASE("Interpolating cubic function", "[interpolation]")
{
    const std::array<double, 5> x{-3.0, -1.0, 0.0, 1.0, 4.0};
    const std::array<double, 5> fx{-7.0, 5.0, 5.0, 9.0, 105.0}; // f(x) = x^3 + 2x^2 + x + 5
    const std::array<double, 5> expectedValues{-7.0, 6.0, -2.0, 1.0, 0.0};

    std::array<double, 5> coefficients{};

    REQUIRE(dsa_interpolation_find_newton_coefficients(
        x.data(), fx.data(), coefficients.data(), x.size()));

    for (size_t i = 0; i < expectedValues.size(); ++i)
    {
        REQUIRE_THAT(coefficients[i], Catch::Matchers::WithinAbs(expectedValues[i], 0.0001));
    }

    std::array<double, 3> z{-4.0, 0.5, 3.5};
    std::array<double, 3> pz{};
    std::array<double, 3> expectedFunctionValues{-31.0, 6.125, 75.875};
    REQUIRE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), pz.data(), pz.size()));

    for (size_t i = 0; i < expectedFunctionValues.size(); i++)
    {
        REQUIRE_THAT(pz[i], Catch::Matchers::WithinAbs(expectedFunctionValues[i], 0.0001));
    }
}

TEST_CASE("Rejects repeated x values", "[interpolation]")
{
    constexpr std::array<double, 2> x{1.0, 1.0};
    constexpr std::array<double, 2> fx{2.0, 2.0};
    std::array<double, 2> coefficients{};

    REQUIRE_FALSE(dsa_interpolation_find_newton_coefficients(x.data(), fx.data(), coefficients.data(), x.size()));
}

TEST_CASE("Handle invalid input values for finding coefficients", "[interpolation]")
{
    constexpr std::array<double, 2> x{0.0, 1.0};
    constexpr std::array<double, 2> fx{1.0, 2.0}; // y = x + 1
    std::array<double, 2> coefficients{};

    REQUIRE(x.size() == 2);
    REQUIRE(fx.size() == 2);
    REQUIRE(coefficients.size() == 2);

    SECTION("x array is nullptr")
    {
        REQUIRE_FALSE(dsa_interpolation_find_newton_coefficients(nullptr, fx.data(), coefficients.data(), fx.size()));
    }

    SECTION("fx array is nullptr")
    {
        REQUIRE_FALSE(dsa_interpolation_find_newton_coefficients(x.data(), nullptr, coefficients.data(), x.size()));
    }

    SECTION("coefficients array is nullptr")
    {
        REQUIRE_FALSE(dsa_interpolation_find_newton_coefficients(x.data(), fx.data(), nullptr, x.size()));
    }

    SECTION("Incorrect size for x array")
    {
        REQUIRE_FALSE(dsa_interpolation_find_newton_coefficients(x.data(), fx.data(), coefficients.data(), 0));
    }

    SECTION("All incorrect parameters")
    {
        REQUIRE_FALSE(dsa_interpolation_find_newton_coefficients(nullptr, nullptr, nullptr, 0));
    }
}

TEST_CASE("Handle invalid input values for evaluating polynomial", "[interpolation]")
{
    constexpr std::array<double, 2> x{0.0, 1.0};
    constexpr std::array<double, 1> z{0.5};
    constexpr std::array<double, 2> coefficients{1.0, 1.0};
    std::array<double, 1> pz{};

    SECTION("x array is nullptr")
    {
        REQUIRE_FALSE(dsa_interpolation_evaluate_newton_polynomial(nullptr, coefficients.data(), coefficients.size(), z.data(), pz.data(), pz.size()));
    }

    SECTION("coefficients array is nullptr")
    {
        REQUIRE_FALSE(dsa_interpolation_evaluate_newton_polynomial(x.data(), nullptr, coefficients.size(), z.data(), pz.data(), pz.size()));
    }

    SECTION("coefficients array size is 0")
    {
        REQUIRE_FALSE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), 0, z.data(), pz.data(), pz.size()));
    }

    SECTION("z array is nullptr")
    {
        REQUIRE_FALSE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), nullptr, pz.data(), pz.size()));
    }

    SECTION("pz array is nullptr")
    {
        REQUIRE_FALSE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), nullptr, pz.size()));
    }

    SECTION("pz size is 0")
    {
        REQUIRE_FALSE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), pz.data(), 0));
    }

    SECTION("All incorrect parameters")
    {
        REQUIRE_FALSE(dsa_interpolation_evaluate_newton_polynomial(nullptr, nullptr, 0, nullptr, nullptr, 0));
    }
}
