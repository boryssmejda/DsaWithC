#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>
#include <vector>

#include "dsa/numeric/lsqe.h"

TEST_CASE("Least square estimation method for incorrect input values", "[lsqe]")
{
    std::vector<double> x;
    std::vector<double> y;
    double a{0.0};
    double b{0.0};

    SECTION("Empty x values")
    {
        REQUIRE_FALSE(dsa_lsqe(nullptr, y.data(), x.size(), &a, &b));
    }

    x.push_back(-4.0);

    SECTION("Empty y values")
    {
        REQUIRE_FALSE(x.empty());
        REQUIRE_FALSE(dsa_lsqe(x.data(), nullptr, x.size(), &a, &b));
    }

    y.push_back(0.0);

    SECTION("Size is smaller than 2")
    {
        REQUIRE((x.size() == 1 && y.size() == 1));
        REQUIRE_FALSE(dsa_lsqe(x.data(), y.data(), x.size(), &a, &b));
    }

    x.push_back(-4.0);
    y.push_back(1.0);

    SECTION("a is nullptr")
    {
        REQUIRE((x.size() == 2 && y.size() == 2));
        REQUIRE_FALSE(dsa_lsqe(x.data(), y.data(), x.size(), nullptr, &b));
    }

    SECTION("b is nullptr")
    {
        REQUIRE((x.size() == 2 && y.size() == 2));
        REQUIRE_FALSE(dsa_lsqe(x.data(), y.data(), x.size(), &a, nullptr));
    }

    x.insert(x.end(), {-4.0, -4.0, -4.0});
    y.insert(y.end(), {2.0, 3.0, 4.0});

    SECTION("All x values are the same")
    {
        REQUIRE((x.size() == y.size() && x.size() > 2));
        REQUIRE_FALSE(dsa_lsqe(x.data(), y.data(), x.size(), &a, &b));
    }
}

TEST_CASE("Least square estimation method for correct input", "[lsqe]")
{
    constexpr std::array<double, 9> x{-4.0, -3.0, -2.0, -1.5, -0.5, 1.0, 2.0, 3.5, 4.0};
    constexpr std::array<double, 9> y{-3.0, -1.0, -2.0, -0.5, 1.0, 0.0, 1.5, 1.0, 2.5};

    double a{0.0};
    double b{0.0};

    REQUIRE((x.size() == y.size() && x.size() > 2));
    REQUIRE(dsa_lsqe(x.data(), y.data(), x.size(), &a, &b));

    REQUIRE_THAT(a, Catch::Matchers::WithinAbs(0.5519, 0.0001));
    REQUIRE_THAT(b, Catch::Matchers::WithinAbs(-0.0249, 0.0001));
}

TEST_CASE("Least square estimation method on unsorted x values", "[lsqe]")
{
    constexpr std::array<double, 9> x{2.0, 3.5, 1.0, -3.0, -2.0, -1.5, -0.5, 4.0, -4.0};
    constexpr std::array<double, 9> y{1.5, 1.0, 0.0, -1.0, -2.0, -0.5, 1.0, 2.5, -3.0};

    double a{0.0};
    double b{0.0};

    REQUIRE((x.size() == y.size() && x.size() > 2));
    REQUIRE(dsa_lsqe(x.data(), y.data(), x.size(), &a, &b));

    REQUIRE_THAT(a, Catch::Matchers::WithinAbs(0.5519, 0.0001));
    REQUIRE_THAT(b, Catch::Matchers::WithinAbs(-0.0249, 0.0001));
}

TEST_CASE("Least square estimation with perfectly linear values", "[lsqe]")
{
    SECTION("Positive Slope")
    {
        constexpr std::array<double, 3> x{0.0, 1.0, 2.0};
        constexpr std::array<double, 3> y{1.0, 3.0, 5.0};

        double a{0.0};
        double b{0.0};

        REQUIRE((x.size() == y.size() && x.size() > 2));
        REQUIRE(dsa_lsqe(x.data(), y.data(), x.size(), &a, &b));

        REQUIRE_THAT(a, Catch::Matchers::WithinAbs(2.0, 0.0001));
        REQUIRE_THAT(b, Catch::Matchers::WithinAbs(1.0, 0.0001));
    }

    SECTION("Negative Slope")
    {
        constexpr std::array<double, 3> x{1.0, 2.0, 3.0};
        constexpr std::array<double, 3> y{6.0, 4.0, 2.0};

        double a{0.0};
        double b{0.0};

        REQUIRE((x.size() == y.size() && x.size() > 2));
        REQUIRE(dsa_lsqe(x.data(), y.data(), x.size(), &a, &b));

        REQUIRE_THAT(a, Catch::Matchers::WithinAbs(-2.0, 0.0001));
        REQUIRE_THAT(b, Catch::Matchers::WithinAbs(8.0, 0.0001));
    }
}

TEST_CASE("Least square estimation with large input", "[lsqe]")
{
    std::vector<double> x(10000), y(10000);
    for (size_t i = 0; i < x.size(); ++i) {
        x[i] = static_cast<double>(i);
        y[i] = 3.0 * x[i] + 1.0;
    }

    double a{0.0}, b{0.0};
    REQUIRE(dsa_lsqe(x.data(), y.data(), x.size(), &a, &b));
    REQUIRE_THAT(a, Catch::Matchers::WithinAbs(3.0, 0.0001));
    REQUIRE_THAT(b, Catch::Matchers::WithinAbs(1.0, 0.0001));
}
