#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "dsa/utility/max_element.h"

#include <array>
#include <cstddef>

namespace
{
struct Point
{
    int x;
    int y;

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};

int compare_int(const void* a, const void* b)
{
    int ia = *static_cast<const int*>(a);
    int ib = *static_cast<const int*>(b);
    return (ia > ib) - (ia < ib);
}

int compare_double(const void* a, const void* b)
{
    double da = *static_cast<const double*>(a);
    double db = *static_cast<const double*>(b);
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

int compare_point_x(const void* a, const void* b)
{
    const Point* pa = static_cast<const Point*>(a);
    const Point* pb = static_cast<const Point*>(b);
    return (pa->x > pb->x) - (pa->x < pb->x);
}
} // namespace

TEST_CASE("dsa_max_element finds max element", "[dsa_max_element]")
{
    SECTION("max element in int array")
    {
        constexpr std::array<int, 5> arr{1, 5, 3, 4, 2};

        const size_t max_index = dsa_max_element(arr.data(), arr.size(), sizeof(int), compare_int);

        REQUIRE(max_index == 1);
        REQUIRE(arr[max_index] == 5);
    }

    SECTION("max element in double array")
    {
        constexpr double expected_max_value{3.3};
        constexpr std::array<double, 4> arr{1.1, 3.3, 2.2, 0.0};

        const size_t max_index = dsa_max_element(arr.data(), arr.size(), sizeof(double), compare_double);

        REQUIRE(max_index == 1);
        constexpr double tolerance{0.0001};
        REQUIRE_THAT(arr[max_index], Catch::Matchers::WithinAbs(expected_max_value, tolerance));
    }

    SECTION("max element in array of Points by x coordinate")
    {
        constexpr Point expected_point{5, 1};
        constexpr std::array<Point, 3> arr{{{1, 2}, {5, 1}, {3, 4}}};
        const size_t max_index = dsa_max_element(arr.data(), arr.size(), sizeof(Point), compare_point_x);

        REQUIRE(max_index == 1);
        REQUIRE(arr[max_index] == expected_point);
    }

    SECTION("max element in single-element array")
    {
        constexpr std::array<int, 1> arr{42};
        const size_t max_index = dsa_max_element(arr.data(), arr.size(), sizeof(int), compare_int);
        REQUIRE(max_index == 0);
        REQUIRE(arr[max_index] == 42);
    }

    SECTION("max element with all equal elements returns index of the first max element")
    {
        constexpr std::array<int, 3> arr{7, 7, 7};
        const size_t max_index = dsa_max_element(arr.data(), arr.size(), sizeof(int), compare_int);
        REQUIRE(max_index == 0);
        REQUIRE(arr[max_index] == 7);
    }

    SECTION("max element in array with negative integers")
    {
        constexpr std::array<int, 5> arr{-10, -20, -5, -30, -1};
        const size_t max_index = dsa_max_element(arr.data(), arr.size(), sizeof(int), compare_int);
        REQUIRE(max_index == 4);
        REQUIRE(arr[max_index] == -1);
    }

    SECTION("max element in array with mixed positive and negative doubles")
    {
        constexpr std::array<double, 4> arr{-1.0, 0.0, 2.5, -3.5};
        constexpr double max_value{2.5};
        const size_t max_index = dsa_max_element(arr.data(), arr.size(), sizeof(double), compare_double);
        REQUIRE(max_index == 2);
        REQUIRE_THAT(arr[max_index], Catch::Matchers::WithinAbs(max_value, 0.0001));
    }
}

TEST_CASE("dsa_max_element with invalid input parameters", "[dsa_max_element]")
{
    SECTION("Handling empty input array")
    {
        const size_t count = 10;
        const size_t max_index = dsa_max_element(nullptr, count, sizeof(int), compare_int);
        REQUIRE(max_index == count);
    }

    SECTION("Handling array size equal 0")
    {
        constexpr std::array<double, 3> arr{1.0, 2.0, 3.0};
        const size_t max_index = dsa_max_element(arr.data(), 0, sizeof(double), compare_double);
        REQUIRE(max_index == 0);
    }

    SECTION("Handling invalid element size equal 0")
    {
        constexpr std::array<double, 3> arr{1.0, 2.0, 3.0};
        const size_t max_index = dsa_max_element(arr.data(), arr.size(), 0, compare_double);
        REQUIRE(max_index == arr.size());
    }

    SECTION("Handling invalid compare function")
    {
        std::array<int, 3> arr{3, 7, 10};
        const size_t max_index = dsa_max_element(arr.data(), arr.size(), sizeof(int), nullptr);
        REQUIRE(max_index == arr.size());
    }

    SECTION("Handling nullptr and size 0 together")
    {
        const size_t max_index = dsa_max_element(nullptr, 0, sizeof(int), compare_int);
        REQUIRE(max_index == 0);
    }
}
