#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <vector>

extern "C"
{
#include "dsa/search/binary_search.h"
}

template <typename T>
int ascending_compare(const void* a, const void* b)
{
    const T* lhs = static_cast<const T*>(a);
    const T* rhs = static_cast<const T*>(b);

    return (*lhs > *rhs) - (*lhs < *rhs);
}

template <typename T>
int descending_compare(const void* a, const void* b)
{
    const T* lhs = static_cast<const T*>(a);
    const T* rhs = static_cast<const T*>(b);

    return (*rhs > *lhs) - (*rhs < *lhs);
}

TEST_CASE("Binary search test", "[BinarySearch]")
{
    std::vector<int> arr;
    const int esize = sizeof(int);

    SECTION("Empty array")
    {
        REQUIRE(arr.data() == nullptr);

        const int target = 10;
        const auto result = dsa_binary_search(
            arr.data(), &target, arr.size(), esize, ascending_compare<int>);

        REQUIRE(result == arr.size());
    }

    SECTION("No target value")
    {
        const auto result = dsa_binary_search(
            arr.data(), nullptr, arr.size(), esize, ascending_compare<int>);
        REQUIRE(result == arr.size());
    }

    arr.push_back(0);

    SECTION("Mismatch in array size")
    {
        REQUIRE(arr.size() == 1);

        const int target = 0;
        const auto mismatchedSize = 0zu;
        const auto result = dsa_binary_search(
            arr.data(), &target, mismatchedSize, esize, ascending_compare<int>
        );
        REQUIRE(result == mismatchedSize);
    }

    SECTION("Element size equal 0")
    {
        REQUIRE(arr.data() != nullptr);

        const int target = 0;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), 0, ascending_compare<int>);

        REQUIRE(result == arr.size());
    }

    SECTION("Empty comparison function")
    {
        const int target = 0;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, nullptr);

        REQUIRE(result == arr.size());
    }

    SECTION("Array with one element equal to target")
    {
        REQUIRE(arr.size() == 1);

        const int target = 0;
        const auto result = dsa_binary_search(
            arr.data(), &target, arr.size(), esize, ascending_compare<int>
        );

        REQUIRE(result == 0);
    }

    SECTION("Array with one element and target value is different")
    {
        REQUIRE(arr.size() == 1);

        const int target = 10;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, ascending_compare<int>);

        REQUIRE(result == arr.size());
    }

    arr.insert(arr.end(), {2, 4, 6, 8, 10});

    SECTION("Array is sorted in increasing order and target value is in array")
    {
        const int target = 6;
        const auto expectedIndex = 3uz;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, ascending_compare<int>);

        REQUIRE(result == expectedIndex);
    }

    SECTION("Array is sorted in increasing order and target value is not in array")
    {
        const int target = 3;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, ascending_compare<int>);

        REQUIRE(result == arr.size());
    }

    std::ranges::reverse(arr);

    SECTION("Array is sorted in decreasing order and target value is in array")
    {
        const int target = 0;
        const size_t expectedIndex = arr.size() - 1;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, descending_compare<int>);

        REQUIRE(expectedIndex == result);
    }

    SECTION("Array is sorted in decreasing order and target value is not in array")
    {
        const int target = 20;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, descending_compare<int>);

        REQUIRE(result == arr.size());
    }
}
