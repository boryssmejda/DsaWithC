#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "dsa/utility/min_element.h"

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

TEST_CASE("dsa_min_element_index finds min element", "[dsa_min_element_index]")
{
    SECTION("min element in int array")
    {
        constexpr std::array<int, 5> arr{1, 5, 3, 4, 2};
        size_t min_index{};
        dsa_error_code_t code = dsa_min_element_index(arr.data(), arr.size(), sizeof(int), compare_int, &min_index);

        REQUIRE(code == DSA_SUCCESS);
        REQUIRE(min_index == 0);
        REQUIRE(arr[min_index] == 1);
    }

    SECTION("min element in double array")
    {
        constexpr std::array<double, 4> arr{1.1, 3.3, 2.2, 0.0};
        const double expected_min_value{0.0};
        size_t min_index{};
        dsa_error_code_t code = dsa_min_element_index(arr.data(), arr.size(), sizeof(double), compare_double, &min_index);

        REQUIRE(code == DSA_SUCCESS);
        REQUIRE(min_index == 3);
        constexpr double tolerance{0.0001};
        REQUIRE_THAT(arr[min_index], Catch::Matchers::WithinAbs(expected_min_value, tolerance));
    }

    SECTION("min element in array of Points by x coordinate")
    {
        constexpr Point expected_point{1, 2};
        constexpr std::array<Point, 3> arr{{{1, 2}, {5, 1}, {3, 4}}};
        size_t min_index{};
        dsa_error_code_t code = dsa_min_element_index(arr.data(), arr.size(), sizeof(Point), compare_point_x, &min_index);

        REQUIRE(code == DSA_SUCCESS);
        REQUIRE(min_index == 0);
        REQUIRE(arr[min_index] == expected_point);
    }

    SECTION("min element in single-element array")
    {
        constexpr std::array<int, 1> arr{42};
        size_t min_index{};
        dsa_error_code_t code = dsa_min_element_index(arr.data(), arr.size(), sizeof(int), compare_int, &min_index);

        REQUIRE(code == DSA_SUCCESS);
        REQUIRE(min_index == 0);
        REQUIRE(arr[min_index] == 42);
    }

    SECTION("min element with all equal elements returns index of the first min element")
    {
        constexpr std::array<int, 3> arr{7, 7, 7};
        size_t min_index{};
        dsa_error_code_t code = dsa_min_element_index(arr.data(), arr.size(), sizeof(int), compare_int, &min_index);

        REQUIRE(code == DSA_SUCCESS);
        REQUIRE(min_index == 0);
        REQUIRE(arr[min_index] == 7);
    }

    SECTION("min element in array with negative integers")
    {
        constexpr std::array<int, 5> arr{-10, -20, -5, -30, -1};
        size_t min_index{};
        dsa_error_code_t code = dsa_min_element_index(arr.data(), arr.size(), sizeof(int), compare_int, &min_index);

        REQUIRE(code == DSA_SUCCESS);
        REQUIRE(min_index == 3);
        REQUIRE(arr[min_index] == -30);
    }
}

TEST_CASE("dsa_min_element_index with invalid input parameters", "[dsa_min_element_index]")
{
    SECTION("Handling null input array")
    {
        size_t min_index{};
        dsa_error_code_t code = dsa_min_element_index(nullptr, 10, sizeof(int), compare_int, &min_index);
        REQUIRE(code == DSA_INVALID_INPUT);
    }

    SECTION("Handling array size equal 0")
    {
        constexpr std::array<double, 3> arr{1.0, 2.0, 3.0};
        size_t min_index{};
        dsa_error_code_t code = dsa_min_element_index(arr.data(), 0, sizeof(double), compare_double, &min_index);
        REQUIRE(code == DSA_INVALID_INPUT);
    }

    SECTION("Handling invalid element size equal 0")
    {
        constexpr std::array<double, 3> arr{1.0, 2.0, 3.0};
        size_t min_index{};
        dsa_error_code_t code = dsa_min_element_index(arr.data(), arr.size(), 0, compare_double, &min_index);
        REQUIRE(code == DSA_INVALID_INPUT);
    }

    SECTION("Handling null compare function")
    {
        std::array<int, 3> arr{3, 7, 10};
        size_t min_index{};
        dsa_error_code_t code = dsa_min_element_index(arr.data(), arr.size(), sizeof(int), nullptr, &min_index);
        REQUIRE(code == DSA_INVALID_INPUT);
    }

    SECTION("Handling null output index pointer")
    {
        std::array<int, 3> arr{1, 2, 3};
        dsa_error_code_t code = dsa_min_element_index(arr.data(), arr.size(), sizeof(int), compare_int, nullptr);
        REQUIRE(code == DSA_INVALID_INPUT);
    }
}
