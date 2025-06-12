#include <catch2/catch_test_macros.hpp>

#include "dsa/utility/max_element.h"

#include <array>

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
        std::array<int, 5> arr{1, 5, 3, 4, 2};

        const size_t max_index = dsa_max_element(arr.data(), arr.size(), sizeof(int), compare_int);

        REQUIRE(max_index == 1);
        REQUIRE(arr[max_index] == 5);
    }

    SECTION("max element in double array")
    {
        const double expected_max_value{3.3};
        std::array<double, 4> arr{1.1, 3.3, 2.2, 0.0};

        const size_t max_index = dsa_max_element(arr.data(), arr.size(), sizeof(double), compare_double);

        REQUIRE(max_index == 1);
        constexpr double tolerance{0.0001};
        REQUIRE_THAT(arr[max_index], Catch::Matchers::WithinAbs(expected_max_value, tolerance));
    }

    SECTION("max element in array of Points by x coordinate")
    {
        constexpr Point expected_point{5, 1};
        std::array<Point, 3> arr{{{1, 2}, {5, 1}, {3, 4}}};
        const size_t max_index = dsa_max_element(arr.data(), arr.size(), sizeof(Point), compare_point_x);

        REQUIRE(max_index == 1);
        REQUIRE(arr[max_index] == expected_point);
    }

    SECTION("max element in single-element array")
    {
        std::array<int, 1> arr{42};
        const int* max_elem = static_cast<const int*>(dsa_max_element(arr.data(), arr.size(), sizeof(int), compare_int));
        REQUIRE(max_elem != nullptr);
        REQUIRE(*max_elem == 42);
    }

    SECTION("max element with all equal elements")
    {
        std::array<int, 3> arr{7, 7, 7};
        const int* max_elem = static_cast<const int*>(dsa_max_element(arr.data(), arr.size(), sizeof(int), compare_int));
        REQUIRE(max_elem != nullptr);
        REQUIRE(*max_elem == 7);
    }

    SECTION("max element in empty array returns nullptr")
    {
        std::array<int, 0> arr{};
        REQUIRE(dsa_max_element(arr.data(), arr.size(), sizeof(int), compare_int) == nullptr);
    }

    SECTION("max element with null data pointer returns nullptr")
    {
        REQUIRE(dsa_max_element(nullptr, 5, sizeof(int), compare_int) == nullptr);
    }

    SECTION("max element in array with negative integers")
    {
        std::array<int, 5> arr{-10, -20, -5, -30, -1};
        const int* max_elem = static_cast<const int*>(dsa_max_element(arr.data(), arr.size(), sizeof(int), compare_int));
        REQUIRE(max_elem != nullptr);
        REQUIRE(*max_elem == -1);
    }
}
