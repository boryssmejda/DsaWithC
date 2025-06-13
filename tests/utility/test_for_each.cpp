#include <catch2/catch_test_macros.hpp>

#include "dsa/utility/for_each.h"

#include <array>

namespace
{

void increment_int(void* element)
{
    int* val = static_cast<int*>(element);
    (*val)++;
}

void scale_int_with_factor(void* element, void* context)
{
    int* val = static_cast<int*>(element);
    int factor = *static_cast<int*>(context);
    (*val) *= factor;
}

} // namespace

TEST_CASE("dsa_for_each handles invalid input", "[dsa_for_each]")
{
    constexpr int factor = 3;

    SECTION("Null array returns DSA_INVALID_INPUT")
    {
        REQUIRE(dsa_for_each(nullptr, 3, sizeof(int), increment_int) == DSA_INVALID_INPUT);
        REQUIRE(dsa_for_each_ctx(nullptr, 3, sizeof(int), scale_int_with_factor, &factor) == DSA_INVALID_INPUT);
    }

    SECTION("Zero count returns DSA_INVALID_INPUT")
    {
        std::array<int, 1> arr{42};
        REQUIRE(dsa_for_each(arr.data(), 0, sizeof(int), increment_int) == DSA_INVALID_INPUT);
        REQUIRE(dsa_for_each(arr.data(), 0, sizeof(int), scale_int_with_factor, &factor) == DSA_INVALID_INPUT);
    }

    SECTION("Zero element size returns DSA_INVALID_INPUT")
    {
        std::array<int, 1> arr{42};
        REQUIRE(dsa_for_each(arr.data(), arr.size(), 0, increment_int) == DSA_INVALID_INPUT);
        REQUIRE(dsa_for_each(arr.data(), arr.size(), 0, scale_int_with_factor, &factor) == DSA_INVALID_INPUT);
    }

    SECTION("Null operation function returns DSA_INVALID_INPUT")
    {
        std::array<int, 3> arr{1, 2, 3};
        REQUIRE(dsa_for_each(arr.data(), arr.size(), sizeof(int), nullptr) == DSA_INVALID_INPUT);
        REQUIRE(dsa_for_each(arr.data(), arr.size(), sizeof(int), nullptr, &factor) == DSA_INVALID_INPUT);
    }

    SECTION("Null context returns DSA_INVALID_INPUT")
    {
        std::array<int, 5> arr{2, 4, 6, 8, 10};
        REQUIRE(dsa_for_each(arr.data(), arr.size(), sizeof(int), scale_int_with_factor, nullptr) == DSA_INVALID_INPUT);
    }
}

TEST_CASE("dsa_for_each applies operation to each element", "[dsa_for_each]")
{
    SECTION("Increment elements of an array")
    {
        std::array<int, 4> arr{1, 2, 3, 4};
        constexpr std::array<int, 4> expected{2, 3, 4, 5};

        dsa_error_code code = dsa_for_each(arr.data(), arr.size(), sizeof(int), increment_int);
        REQUIRE(code == DSA_SUCCESS);
        REQUIRE(arr == expected);
    }
}

TEST_CASE("dsa_for_each_ctx applies context-aware operation", "[dsa_for_each]")
{
    SECTION("Multiply each element by context-provided factor")
    {
        std::array<int, 4> arr{1, 2, 3, 4};
        const std::array<int, 4> expected{10, 20, 30, 40};
        constexpr int factor = 10;

        dsa_error_code code = dsa_for_each_ctx(arr.data(), arr.size(), sizeof(int), scale_int_with_factor, &factor);
        REQUIRE(code == DSA_SUCCESS);
        REQUIRE(arr == expected);
    }
}
