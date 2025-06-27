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

TEST_CASE("dsa_max_element_index finds max element", "[dsa_max_element_index]")
{
    SECTION("max element in int array")
    {
        constexpr std::array<int, 5> arr{1, 5, 3, 4, 2};
        size_t max_index = 0;

        const auto status = dsa_max_element_index(arr.data(), arr.size(), sizeof(int), compare_int, &max_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(max_index == 1);
        REQUIRE(arr[max_index] == 5);
    }

    SECTION("max element in double array")
    {
        constexpr std::array<double, 4> arr{1.1, 3.3, 2.2, 0.0};
        constexpr double expected_max_value{3.3};
        constexpr double tolerance{0.0001};

        size_t max_index = 0;
        const auto status = dsa_max_element_index(arr.data(), arr.size(), sizeof(double), compare_double, &max_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(max_index == 1);
        REQUIRE_THAT(arr[max_index], Catch::Matchers::WithinAbs(expected_max_value, tolerance));
    }

    SECTION("max element in array of Points by x coordinate")
    {
        constexpr std::array<Point, 3> arr{{{1, 2}, {5, 1}, {3, 4}}};
        constexpr Point expected_point{5, 1};

        size_t max_index = 0;
        const auto status = dsa_max_element_index(arr.data(), arr.size(), sizeof(Point), compare_point_x, &max_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(max_index == 1);
        REQUIRE(arr[max_index] == expected_point);
    }

    SECTION("max element in single-element array")
    {
        constexpr std::array<int, 1> arr{42};
        size_t max_index = 0;

        const auto status = dsa_max_element_index(arr.data(), arr.size(), sizeof(int), compare_int, &max_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(max_index == 0);
        REQUIRE(arr[max_index] == 42);
    }

    SECTION("max element with all equal elements returns index of the first max element")
    {
        constexpr std::array<int, 3> arr{7, 7, 7};
        size_t max_index = 0;

        const auto status = dsa_max_element_index(arr.data(), arr.size(), sizeof(int), compare_int, &max_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(max_index == 0);
        REQUIRE(arr[max_index] == 7);
    }

    SECTION("max element in array with negative integers")
    {
        constexpr std::array<int, 5> arr{-10, -20, -5, -30, -1};
        size_t max_index = 0;

        const auto status = dsa_max_element_index(arr.data(), arr.size(), sizeof(int), compare_int, &max_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(max_index == 4);
        REQUIRE(arr[max_index] == -1);
    }

    SECTION("max element in array with mixed positive and negative doubles")
    {
        constexpr std::array<double, 4> arr{-1.0, 0.0, 2.5, -3.5};
        constexpr double max_value{2.5};

        size_t max_index = 0;
        const auto status = dsa_max_element_index(arr.data(), arr.size(), sizeof(double), compare_double, &max_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(max_index == 2);
        REQUIRE_THAT(arr[max_index], Catch::Matchers::WithinAbs(max_value, 0.0001));
    }
}

TEST_CASE("dsa_max_element_index with invalid input parameters", "[dsa_max_element_index]")
{
    SECTION("Handling null array")
    {
        size_t max_index = 999;
        const auto status = dsa_max_element_index(nullptr, 10, sizeof(int), compare_int, &max_index);

        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Handling array size == 0")
    {
        constexpr std::array<int, 3> arr{1, 2, 3};
        size_t max_index = 999;

        const auto status = dsa_max_element_index(arr.data(), 0, sizeof(int), compare_int, &max_index);

        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Handling element size == 0")
    {
        constexpr std::array<double, 3> arr{1.0, 2.0, 3.0};
        size_t max_index = 999;

        const auto status = dsa_max_element_index(arr.data(), arr.size(), 0, compare_double, &max_index);

        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Handling invalid compare function")
    {
        constexpr std::array<int, 3> arr{3, 7, 10};
        size_t max_index = 999;

        const auto status = dsa_max_element_index(arr.data(), arr.size(), sizeof(int), nullptr, &max_index);

        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Handling null output index pointer")
    {
        constexpr std::array<int, 3> arr{10, 20, 30};

        const auto status = dsa_max_element_index(arr.data(), arr.size(), sizeof(int), compare_int, nullptr);

        REQUIRE(status == DSA_INVALID_INPUT);
    }
}
