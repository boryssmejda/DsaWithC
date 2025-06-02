#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <algorithm>
#include <cstring>
#include <vector>

#include "dsa/search/binary_search.h"

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

int compare_strings_ascending(const void* a, const void* b)
{
    const char *lhs = *static_cast<const char* const*>(a);
    const char *rhs = *static_cast<const char* const*>(b);
    const int result = std::strcmp(lhs, rhs);

    return (result > 0) - (result < 0);
}

int compare_strings_descending(const void* a, const void* b)
{
    const char *lhs = *static_cast<const char* const*>(a);
    const char *rhs = *static_cast<const char* const*>(b);
    const int result = std::strcmp(lhs, rhs);

    return (result < 0) - (result > 0);
}

TEMPLATE_TEST_CASE("Binary search test", "[BinarySearch][template]",
    int8_t, int16_t, int32_t, int64_t,
    uint8_t, uint16_t, uint32_t, uint64_t,
    float, double)
{
    using T = TestType;
    std::vector<T> arr;
    const int esize = sizeof(T);

    SECTION("Empty array")
    {
        REQUIRE(arr.data() == nullptr);

        const T target = 10;
        const auto result = dsa_binary_search(
            arr.data(), &target, arr.size(), esize, ascending_compare<T>);

        REQUIRE(result == arr.size());
    }

    SECTION("No target value")
    {
        const auto result = dsa_binary_search(
            arr.data(), nullptr, arr.size(), esize, ascending_compare<T>);
        REQUIRE(result == arr.size());
    }

    arr.push_back(1);

    SECTION("Mismatch in array size")
    {
        REQUIRE(arr.size() == 1);

        const T target = 0;
        const size_t mismatchedSize = 0;
        const auto result = dsa_binary_search(
            arr.data(), &target, mismatchedSize, esize, ascending_compare<T>
        );
        REQUIRE(result == mismatchedSize);
    }

    SECTION("Element size equal 0")
    {
        REQUIRE(arr.data() != nullptr);

        const T target = 0;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), 0, ascending_compare<T>);

        REQUIRE(result == arr.size());
    }

    SECTION("Empty comparison function")
    {
        const T target = 0;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, nullptr);

        REQUIRE(result == arr.size());
    }

    SECTION("Array with one element equal to target")
    {
        REQUIRE(arr.size() == 1);

        const T target = 1;
        const auto result = dsa_binary_search(
            arr.data(), &target, arr.size(), esize, ascending_compare<T>
        );

        REQUIRE(result == 0);
    }

    SECTION("Array with one element and target value is different")
    {
        REQUIRE(arr.size() == 1);

        const T target = 10;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, ascending_compare<T>);

        REQUIRE(result == arr.size());
    }

    arr.insert(arr.end(), {T{2}, T{4}, T{6}, T{8}, T{10}});

    SECTION("Array is sorted in increasing order and target value is in array")
    {
        const T target = 6;
        const size_t expectedIndex = 3;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, ascending_compare<T>);

        REQUIRE(result == expectedIndex);
    }

    SECTION("Array contains duplicates in ascending order")
    {
        arr.insert(arr.end(), {T{20}, T{20}, T{20}});
        const T target = 20;
        const size_t expectedLowIndex = arr.size() - 3;
        const size_t expectedHighIndex = arr.size() - 1;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, ascending_compare<T>);

        // Allow any index between expectedLowIndex and expectedHighIndex (inclusive)
        REQUIRE((result >= expectedLowIndex && result <= expectedHighIndex));
    }

    SECTION("Array is sorted in ascending order and target value is not in array")
    {
        const T target = 3;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, ascending_compare<T>);

        REQUIRE(result == arr.size());
    }

    std::ranges::reverse(arr);

    SECTION("Array is sorted in decreasing order and target value is in array")
    {
        const T target = 2;
        const size_t expectedIndex = arr.size() - 2;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, descending_compare<T>);

        REQUIRE(expectedIndex == result);
    }

    SECTION("Array contains duplicates in descending order")
    {
        arr.insert(arr.end(), {0, 0, 0, 0});

        const T target = 0;
        const size_t expectedLowIndex = arr.size() - 4;
        const size_t expectedHighIndex = arr.size() - 1;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, descending_compare<T>);

        // Allow any index between expectedLowIndex and expectedHighIndex (inclusive)
        REQUIRE((result >= expectedLowIndex && result <= expectedHighIndex));
    }

    SECTION("Array is sorted in decreasing order and target value is not in array")
    {
        const T target = 20;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, descending_compare<T>);

        REQUIRE(result == arr.size());
    }

    SECTION("Array with all elements equal to target")
    {
        arr.assign(10, T{7});
        const T target = 7;
        const auto result = dsa_binary_search(arr.data(), &target, arr.size(), esize, ascending_compare<T>);

        REQUIRE(result < arr.size());
        if constexpr (std::is_floating_point_v<T>)
        {
            REQUIRE_THAT(arr[result], Catch::Matchers::WithinAbs(target, 0.1));
        }
        else
        {
            REQUIRE(arr[result] == target);
        }
    }
}

TEST_CASE("Binary search with const char*", "[BinarySearch][CString]")
{
    std::vector<const char*> sorted{
        "apple", "banana", "cherry", "date", "fig", "grape", "kiwi"
    };

    const size_t size = sorted.size();
    const size_t esize = sizeof(const char*);

    SECTION("Target found in array sorted in ascending order")
    {
        const char* target = "cherry";
        const size_t expectedIndex = 2;

        const auto result = dsa_binary_search(
            sorted.data(), &target, size, esize, compare_strings_ascending);

        REQUIRE(result == expectedIndex);
    }

    SECTION("Target found in array sorted in descending order")
    {
        std::ranges::reverse(sorted);
        const char* target = "banana";
        const size_t expectedIndex = 5;
        const size_t result = dsa_binary_search(sorted.data(), &target, size, esize, compare_strings_descending);

        REQUIRE(result == expectedIndex);
    }

    SECTION("Target not found")
    {
        const char* target = "blueberry";

        const auto result = dsa_binary_search(
            sorted.data(), &target, size, esize, compare_strings_ascending);

        REQUIRE(result == size);
    }

    SECTION("All elements are the same")
    {
        const std::vector<const char*> repeated{"hello", "hello", "hello", "hello"};
        const size_t repeatedSize = repeated.size();
        const char* target = "hello";

        const auto result = dsa_binary_search(
            repeated.data(), &target, repeatedSize, esize, compare_strings_ascending);

        REQUIRE(result < repeatedSize);
        REQUIRE(std::strcmp(repeated[result], target) == 0);
    }
}
