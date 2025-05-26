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
    for (size_t i = 0; i < 2; ++i) {
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

TEST_CASE("Handles null pointers safely", "[interpolation]") {
    double x[] = {0.0, 1.0};
    double fx[] = {1.0, 2.0};
    double z[] = {0.5};
    double pz[1];

    REQUIRE(dsa_interpolate(nullptr, fx, 2, z, pz, 1) == false);
    REQUIRE(dsa_interpolate(x, nullptr, 2, z, pz, 1) == false);
    REQUIRE(dsa_interpolate(x, fx, 2, nullptr, pz, 1) == false);
    REQUIRE(dsa_interpolate(x, fx, 2, z, nullptr, 1) == false);
}

TEST_CASE("Handles empty input safely", "[interpolation]") {
    REQUIRE(dsa_interpolate(nullptr, nullptr, 0, nullptr, nullptr, 0) == false);
}
