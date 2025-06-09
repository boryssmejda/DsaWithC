#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>
#include <span>

#include "dsa/numeric/polynomial_interpolation.h"

namespace
{
constexpr double tolerance{0.0001};

void assert_coefficients(const std::span<const double> actual, const std::span<const double> expected)
{
    REQUIRE(actual.size() == expected.size());

    for (size_t i = 0; i < expected.size(); i++)
    {
        REQUIRE_THAT(actual[i], Catch::Matchers::WithinAbs(expected[i], tolerance));
        CAPTURE(i, actual[i], expected[i]);
    }
}
} // namespace

TEST_CASE("Interpolating constant function", "[interpolation]")
{
    const std::array<double, 1> x{5.0};
    const std::array<double, 1> fx{1.0};
    const std::array<double, 1> expectedCoefficients{1.0};

    std::array<double, 1> coefficients{};
    REQUIRE(dsa_interpolation_find_newton_coefficients(x.data(), fx.data(), coefficients.data(), x.size()));

    assert_coefficients(coefficients, expectedCoefficients);

    std::array<double, 3> z{-5.0, 0.0, 10.0};
    std::array<double, 3> pz{};
    std::array<double, 3> expectedFunctionValues{1.0, 1.0, 1.0};
    REQUIRE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), pz.data(), pz.size()));

    assert_coefficients(pz, expectedFunctionValues);
}

TEST_CASE("Interpolating linear function", "[interpolation]")
{
    const std::array<double, 2> x{1.0, 2.0};
    const std::array<double, 2> fx{2.0, 4.0}; // f(x) = 2x
    const std::array<double, 2> expectedCoefficients{2.0, 2.0};

    std::array<double, 2> coefficients{};

    REQUIRE(dsa_interpolation_find_newton_coefficients(
        x.data(), fx.data(), coefficients.data(), x.size()));

    assert_coefficients(coefficients, expectedCoefficients);

    std::array<double, 3> z{-10.0, 5.0, 7.0};
    std::array<double, 3> pz{};
    std::array<double, 3> expectedFunctionValues{-20.0, 10.0, 14.0};
    REQUIRE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), pz.data(), pz.size()));

    assert_coefficients(pz, expectedFunctionValues);
}

TEST_CASE("Interpolation with close x values", "[interpolation][stability]") {
    const std::array<double, 3> x{1.000, 1.001, 1.002};
    const std::array<double, 3> fx{2.0, 2.002, 2.004}; // f(x) = 2x (linear)
    const std::array<double, 3> expectedCoefficients{2.0, 2.0, 0.0}; // almost exactly linear
    std::array<double, 3> coefficients{};

    REQUIRE(dsa_interpolation_find_newton_coefficients(x.data(), fx.data(), coefficients.data(), x.size()));
    assert_coefficients(coefficients, expectedCoefficients);

    const std::array<double, 3> z{1.0005, 1.0015, 1.0025};
    const std::array<double, 3> expectedValues{2.001, 2.003, 2.005};
    std::array<double, 3> pz{};

    REQUIRE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), pz.data(), pz.size()));
    assert_coefficients(pz, expectedValues);
}

TEST_CASE("Interpolating quadratic function", "[interpolation]")
{
    const std::array<double, 3> x{-1.0, 1.0, 2.0};
    const std::array<double, 3> fx{2.0, 2.0, 5.0}; // f(x) = x^2 + 1
    const std::array<double, 3> expectedCoefficients{2.0, 0.0, 1.0};
    std::array<double, 3> coefficients{};

    REQUIRE(dsa_interpolation_find_newton_coefficients(
        x.data(), fx.data(), coefficients.data(), x.size()));

    assert_coefficients(coefficients, expectedCoefficients);

    std::array<double, 3> z{-3.0, 0, 7.0};
    std::array<double, 3> pz{};
    std::array<double, 3> expectedFunctionValues{10.0, 1.0, 50.0};
    REQUIRE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), pz.data(), pz.size()));

    assert_coefficients(pz, expectedFunctionValues);
}

//TEST_CASE("Interpolation with out-of-order x values", "[interpolation]") {
//    const std::array<double, 3> x{2.0, -1.0, 1.0}; // out of order
//    const std::array<double, 3> fx{5.0, 2.0, 2.0}; // f(x) = x^2 + 1
//    const std::array<double, 3> expectedCoefficients{5.0, -1.0, 1.0};
//    std::array<double, 3> coefficients{};
//
//    REQUIRE(dsa_interpolation_find_newton_coefficients(x.data(), fx.data(), coefficients.data(), x.size()));
//    assert_coefficients(coefficients, expectedCoefficients);
//
//    const std::array<double, 2> z{0.0, 3.0};
//    const std::array<double, 2> expectedValues{1.0, 10.0};
//    std::array<double, 2> pz{};
//
//    REQUIRE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), pz.data(), pz.size()));
//    assert_coefficients(pz, expectedValues);
//}

TEST_CASE("Interpolating cubic function", "[interpolation]")
{
    const std::array<double, 5> x{-3.0, -1.0, 0.0, 1.0, 4.0};
    const std::array<double, 5> fx{-7.0, 5.0, 5.0, 9.0, 105.0}; // f(x) = x^3 + 2x^2 + x + 5
    const std::array<double, 5> expectedCoefficients{-7.0, 6.0, -2.0, 1.0, 0.0};
    std::array<double, 5> coefficients{};

    REQUIRE(dsa_interpolation_find_newton_coefficients(
        x.data(), fx.data(), coefficients.data(), x.size()));

    assert_coefficients(coefficients, expectedCoefficients);

    std::array<double, 3> z{-4.0, 0.5, 3.5};
    std::array<double, 3> pz{};
    std::array<double, 3> expectedFunctionValues{-31.0, 6.125, 75.875};
    REQUIRE(dsa_interpolation_evaluate_newton_polynomial(x.data(), coefficients.data(), coefficients.size(), z.data(), pz.data(), pz.size()));

    assert_coefficients(pz, expectedFunctionValues);
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
