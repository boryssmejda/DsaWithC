#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>

#include "dsa/numeric/polynomial_interpolation.h"

TEST_CASE("Newton coefficients for linear function", "[interpolation][newton_coefficients]")
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
}

TEST_CASE("Newton coefficients for quadratic function", "[interpolation][newton_coefficients]")
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
}

TEST_CASE("Newton coefficients for cubic function", "[interpolation][newton_coefficients]")
{
    const std::array<double, 5> x{-3.0, -1.0, 0.0, 1.0, 4.0};
    const std::array<double, 5> fx{-7.0, 5.0, 5.0, 9.0, 105.0}; // f(x) = x^3 + 2x^2 + x + 5
    const std::array<double, 5> expectedValues{};

    std::array<double, 5> coefficients{};

    REQUIRE(dsa_interpolation_find_newton_coefficients(
        x.data(), fx.data(), coefficients.data(), x.size()));

    for (size_t i = 0; i < expectedValues.size(); ++i)
    {
        std::printf("%lf\n", coefficients[i]);
        //REQUIRE_THAT(coefficients[i], Catch::Matchers::WithinAbs(expectedValues[i], 0.0001));
    }
}

TEST_CASE("Interpolates linear function correctly", "[interpolation]")
{
    const std::array<double, 2> x{1.0, 2.0};
    const std::array<double, 2> fx{2.0, 4.0}; // f(x) = 2x
    const std::array<double, 2> z{1.5, 3.0};
    const std::array<double, 2> expectedValues{3.0, 6.0};
    std::array<double, 2> pz{};

    REQUIRE(dsa_interpolate(x.data(), fx.data(), fx.size(), z.data(), pz.data(), pz.size()));

    for (size_t i = 0; i < expectedValues.size(); ++i)
    {
        REQUIRE_THAT(pz[i], Catch::Matchers::WithinAbs(expectedValues[i], 0.0001));
    }
}

TEST_CASE("Interpolates quadratic function correctly", "[interpolation]")
{
    constexpr std::array<double, 3> x{0.0, 1.0, 2.0};
    constexpr std::array<double, 3> fx{1.0, 2.0, 5.0}; // y = x^2 + 1
    constexpr std::array<double, 2> z{0.5, 1.5};
    constexpr std::array<double, 2> expectedValues{1.25, 3.25};
    std::array<double, 2> pz{};

    REQUIRE(dsa_interpolate(x.data(), fx.data(), x.size(), z.data(), pz.data(), z.size()));
    for (size_t i = 0; i < expectedValues.size(); ++i)
    {
        REQUIRE_THAT(pz[i], Catch::Matchers::WithinAbs(expectedValues[i], 0.0001));
    }
}

TEST_CASE("Interpolates cubic function correctly", "[interpolation]")
{
    const std::array<double, 5> x{-3.0, -1.0, 0.0, 1.0, 4.0};
    const std::array<double, 5> fx{-7.0, 5.0, 5.0, 9.0, 105.0}; // f(x) = x^3 + 2x^2 + x + 5
    const std::array<double, 2> z{2.0, -2.0};
    std::array<double, 2> pz{};
    const std::array<double, 2> expectedValues{23.0, 3.0};

    REQUIRE(dsa_interpolate(x.data(), fx.data(), x.size(), z.data(), pz.data(), z.size()));
    for (size_t i = 0; i < expectedValues.size(); ++i)
    {
        REQUIRE_THAT(pz[i], Catch::Matchers::WithinAbs(expectedValues[i], 0.0001));
    }
}

TEST_CASE("Rejects repeated x values", "[interpolation]")
{
    constexpr std::array<double, 2> x{1.0, 1.0};
    constexpr std::array<double, 2> fx{2.0, 2.0};
    constexpr std::array<double, 1> z{1.0};
    std::array<double, 1> pz{};

    REQUIRE_FALSE(dsa_interpolate(x.data(), fx.data(), x.size(), z.data(), pz.data(), z.size()));
}

TEST_CASE("Handle invalid input values", "[interpolation]")
{
    constexpr std::array<double, 2> x{0.0, 1.0};
    constexpr std::array<double, 2> fx{1.0, 2.0};
    constexpr std::array<double, 1> z{0.5};
    std::array<double, 1> pz{};

    REQUIRE(x.size() == 2);
    REQUIRE(fx.size() == 2);
    REQUIRE(z.size() == 1);
    REQUIRE(pz.size() == 1);

    SECTION("x array is nullptr")
    {
        REQUIRE_FALSE(dsa_interpolate(nullptr, fx.data(), x.size(), z.data(), pz.data(), z.size()));
    }

    SECTION("fx array is nullptr")
    {
        REQUIRE_FALSE(dsa_interpolate(x.data(), nullptr, x.size(), z.data(), pz.data(), z.size()));
    }

    SECTION("z array is nullptr")
    {
        REQUIRE_FALSE(dsa_interpolate(x.data(), fx.data(), x.size(), nullptr, pz.data(), pz.size()));
    }

    SECTION("pz array is nullptr")
    {
        REQUIRE_FALSE(dsa_interpolate(x.data(), fx.data(), x.size(), z.data(), nullptr, z.size()));
    }

    SECTION("Incorrect size for x array")
    {
        REQUIRE_FALSE(dsa_interpolate(x.data(), fx.data(), 0, z.data(), pz.data(), 1));
        REQUIRE_FALSE(dsa_interpolate(x.data(), fx.data(), 1, z.data(), pz.data(), 1));
    }

    SECTION("Incorrect size for pz array")
    {
        REQUIRE_FALSE(dsa_interpolate(x.data(), fx.data(), x.size(), z.data(), pz.data(), 0));
    }

    SECTION("All incorrect parameters")
    {
        REQUIRE_FALSE(dsa_interpolate(nullptr, nullptr, 0, nullptr, nullptr, 0));
    }
}
