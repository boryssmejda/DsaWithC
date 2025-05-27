#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>

extern "C"
{
#include "dsa/numeric/polynomial_interpolation.h"
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

TEST_CASE("Interpolates quadratic function correctly", "[interpolation]") {
    double x[] = {0.0, 1.0, 2.0};
    double fx[] = {1.0, 4.0, 9.0}; // y = x^2 + 1
    double z[] = {0.5, 1.5};
    double expected[] = {1.25, 5.25};
    double pz[2];

    REQUIRE(dsa_interpolate(x, fx, 3, z, pz, 2) == true);
    for (size_t i = 0; i < 2; ++i)
    {
        REQUIRE(pz[i] == Approx(expected[i]).epsilon(1e-10));
    }
}

TEST_CASE("Rejects repeated x values", "[interpolation]") {
    double x[] = {1.0, 1.0};
    double fx[] = {2.0, 2.0};
    double z[] = {1.0};
    double pz[1];

    REQUIRE(dsa_interpolate(x, fx, 2, z, pz, 1) == false);
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
