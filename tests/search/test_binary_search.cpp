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
    const size_t elem_size = sizeof(T);

    REQUIRE(elem_size != 0);

    SECTION("Empty array")
    {
        REQUIRE(arr.data() == nullptr);

        const T target = 10;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), elem_size, ascending_compare<T>, &found_index);

        REQUIRE(status == DSA_INVALID_INPUT);
    }

    arr.push_back(1);

    REQUIRE(arr.data() != nullptr);
    REQUIRE(arr.size() != 0);

    SECTION("Null target pointer")
    {
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            nullptr, arr.data(), arr.size(), elem_size, ascending_compare<T>, &found_index);

        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Zero array size")
    {
        const T target = 0;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), 0, elem_size, ascending_compare<T>, &found_index);

        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Zero element size")
    {
        const T target = 0;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), 0, ascending_compare<T>, &found_index);

        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Null compare function")
    {
        const T target = 0;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), elem_size, nullptr, &found_index);

        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Array with one element equal to target")
    {
        REQUIRE(arr.size() == 1);

        const T target = 1;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), elem_size, ascending_compare<T>, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(found_index == 0);
    }

    SECTION("Array with one element and target different")
    {
        REQUIRE(arr.size() == 1);

        const T target = 10;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), elem_size, ascending_compare<T>, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(found_index == arr.size());
    }

    arr.insert(arr.end(), {T{2}, T{4}, T{6}, T{8}, T{10}});

    SECTION("Array sorted ascending and target in array")
    {
        const T target = 6;
        const size_t expected_index = 3;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), elem_size, ascending_compare<T>, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(found_index == expected_index);
    }

    SECTION("Array contains duplicates ascending")
    {
        arr.insert(arr.end(), {T{20}, T{20}, T{20}});
        const T target = 20;
        const size_t expectedLowIndex = arr.size() - 3;
        const size_t expectedHighIndex = arr.size() - 1;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), elem_size, ascending_compare<T>, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE((found_index >= expectedLowIndex && found_index <= expectedHighIndex));
    }

    SECTION("Array sorted ascending and target not in array")
    {
        const T target = 3;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), elem_size, ascending_compare<T>, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(found_index == arr.size());
    }

    std::ranges::reverse(arr);

    SECTION("Array sorted descending and target in array")
    {
        const T target = 2;
        const size_t expected_index = arr.size() - 2;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), elem_size, descending_compare<T>, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(found_index == expected_index);
    }

    SECTION("Array contains duplicates descending")
    {
        arr.insert(arr.end(), {T{0}, T{0}, T{0}, T{0}});
        const T target = 0;
        const size_t expectedLowIndex = arr.size() - 4;
        const size_t expectedHighIndex = arr.size() - 1;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), elem_size, descending_compare<T>, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE((found_index >= expectedLowIndex && found_index <= expectedHighIndex));
    }

    SECTION("Array sorted descending and target not in array")
    {
        const T target = 20;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), elem_size, descending_compare<T>, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(found_index == arr.size());
    }

    SECTION("Array with all elements equal to target")
    {
        arr.assign(10, T{7});
        const T target = 7;
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, arr.data(), arr.size(), elem_size, ascending_compare<T>, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(found_index < arr.size());
        if constexpr (std::is_floating_point_v<T>)
        {
            REQUIRE_THAT(arr[found_index], Catch::Matchers::WithinAbs(target, 0.1));
        }
        else
        {
            REQUIRE(arr[found_index] == target);
        }
    }
}

TEST_CASE("Binary search with const char*", "[BinarySearch][CString]")
{
    std::vector<const char*> sorted{
        "apple", "banana", "cherry", "date", "fig", "grape", "kiwi"
    };

    const size_t size = sorted.size();
    const size_t elem_size = sizeof(const char*);

    SECTION("Target found in array sorted ascending")
    {
        const char* target = "date";
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, sorted.data(), size, elem_size, compare_strings_ascending, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(found_index == 3);
    }

    SECTION("Target not found in array sorted ascending")
    {
        const char* target = "mango";
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, sorted.data(), size, elem_size, compare_strings_ascending, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(found_index == size);
    }

    std::ranges::reverse(sorted);

    SECTION("Target found in array sorted descending")
    {
        const char* target = "date";
        size_t found_index = 0;
        const auto status = dsa_binary_search_index(
            &target, sorted.data(), size, elem_size, compare_strings_descending, &found_index);

        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(found_index == size - 4);
    }
}
