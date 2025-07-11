#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <numeric>
#include <random>

#include "dsa/sort/insertion_sort.h"

struct CharWithIndex
{
    char ch;
    int index;
};

bool operator==(const CharWithIndex& lhs, const CharWithIndex& rhs)
{
    return lhs.ch == rhs.ch && lhs.index == rhs.index;
}

int compare_char_with_index_ascending(const void* first, const void* second)
{
    const CharWithIndex* lhs = static_cast<const CharWithIndex*>(first);
    const CharWithIndex* rhs = static_cast<const CharWithIndex*>(second);

    return (lhs->ch > rhs->ch) - (lhs->ch < rhs->ch);
}

TEST_CASE("Insertion sort preserves order of equal elements", "[InsertionSort][ComplexType]")
{
    const CharWithIndex a{.ch = 'a', .index = 2};
    const CharWithIndex b{.ch = 'b', .index = 2};
    const CharWithIndex c{.ch = 'c', .index = 2};

    const CharWithIndex aa{.ch = 'a', .index = 1};
    const CharWithIndex bb{.ch = 'b', .index = 1};
    const CharWithIndex cc{.ch = 'c', .index = 1};

    const CharWithIndex aaa{.ch = 'a', .index = 0};
    const CharWithIndex bbb{.ch = 'b', .index = 0};
    const CharWithIndex ccc{.ch = 'c', .index = 0};


    std::vector<CharWithIndex> inputArr{a, b, c, aa, bb, cc, aaa, bbb, ccc};
    const size_t size = inputArr.size();
    const size_t esize = sizeof(inputArr[0]);
    int (*compare)(const void*, const void*) = compare_char_with_index_ascending;
    std::vector<CharWithIndex> expectedArr{a, aa, aaa, b, bb, bbb, c, cc, ccc};

    const auto status = dsa_insertion_sort(inputArr.data(), size, esize, compare);
    REQUIRE(status == DSA_SUCCESS);
    REQUIRE(inputArr == expectedArr);
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

template <typename T>
int abs_compare(const void* a, const void* b)
{
    const T* lhs = static_cast<const T*>(a);
    const T* rhs = static_cast<const T*>(b);

    return (std::abs(*lhs) > std::abs(*rhs)) - (std::abs(*lhs) < std::abs(*rhs));
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

TEMPLATE_TEST_CASE("Insertion sort works for numeric signed types",
                    "[InsertionSort][template]",
                    int8_t, int16_t, int32_t, int64_t, float, double)
{
    using T = TestType;
    const size_t esize = sizeof(T);

    SECTION("Sort in ascending order")
    {
        std::vector<T> inputArr{-1, -3, 0, 1, -4, -5};
        const auto status = dsa_insertion_sort(inputArr.data(), inputArr.size(), esize, ascending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(inputArr));
    }

    SECTION("Sort in descending order")
    {
        std::vector<T> inputArr{-10, 0, 1, 4, -2, -7};
        const auto status = dsa_insertion_sort(static_cast<void*>(inputArr.data()), inputArr.size(), esize, descending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(inputArr, std::greater<>()));
    }

    SECTION("Sort using non-trivial comparator")
    {
        std::vector<T> numbers{-10, 4, 2, -1, -5, 0, 3, -2};
        const auto status = dsa_insertion_sort(numbers.data(), numbers.size(), esize, abs_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(numbers == std::vector<T>{0, -1, 2, -2, 3, 4, -5, -10});
    }

    SECTION("Sort extreme values")
    {
        std::vector<T> boundaryInput{std::numeric_limits<T>::max(), 0, std::numeric_limits<T>::min()};
        const auto status = dsa_insertion_sort(boundaryInput.data(), boundaryInput.size(), esize, ascending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(boundaryInput));
    }

    SECTION("Sort with duplicate values")
    {
        std::vector<T> inputArr{3, 1, 2, 1, 3, 0, 2};
        const auto status = dsa_insertion_sort(inputArr.data(), inputArr.size(), esize, descending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(inputArr, std::greater<>()));
    }
}

TEMPLATE_TEST_CASE("Insertion sort works for numeric unsigned types", "[InsertionSort][template]",
                    uint8_t, uint16_t, uint32_t, uint64_t)
{
    using T = TestType;
    const size_t esize = sizeof(T);

    SECTION("Nullptr data array returns DSA_INVALID_INPUT")
    {
        const auto status = dsa_insertion_sort(nullptr, 0, esize, ascending_compare<T>);
        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Zero size with non-null data returns DSA_SUCCESS")
    {
        std::vector<T> data{3};
        const auto status = dsa_insertion_sort(data.data(), 0, esize, ascending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
    }

    SECTION("Zero element size returns DSA_INVALID_INPUT")
    {
        std::vector<T> data{3, 3, 3};
        const auto status = dsa_insertion_sort(data.data(), data.size(), 0, ascending_compare<T>);
        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Null pointer and zero size returns DSA_INVALID_INPUT")
    {
        const auto status = dsa_insertion_sort(nullptr, 0, esize, ascending_compare<T>);
        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Null pointer compare function returns DSA_INVALID_INPUT")
    {
        std::vector<T> inputArr{1, 1, 1};

        const auto status = dsa_insertion_sort(inputArr.data(), inputArr.size(), esize, nullptr);
        REQUIRE(status == DSA_INVALID_INPUT);
    }

    SECTION("Handling array with single element")
    {
        std::vector<T> singleElementArr{3};
        REQUIRE(singleElementArr.size() == 1);
        const auto status = dsa_insertion_sort(singleElementArr.data(), singleElementArr.size(), esize, ascending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(singleElementArr.size() == 1);
    }

    SECTION("Five elements equal to 1")
    {
        std::vector<T> allSameElementsArr(5, 1);
        REQUIRE(allSameElementsArr.size() == 5);
        REQUIRE(std::ranges::all_of(allSameElementsArr, [](const auto num){ return num == 1; }));
        const auto status = dsa_insertion_sort(allSameElementsArr.data(), allSameElementsArr.size(), esize, ascending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(allSameElementsArr));
    }

    SECTION("Array already sorted")
    {
        std::vector<T> alreadySorted{0, 1, 2, 3, 4, 5};
        const auto status = dsa_insertion_sort(alreadySorted.data(), alreadySorted.size(), esize, ascending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(alreadySorted));
    }

    SECTION("Reverse sorting")
    {
        std::vector<T> reverseSortedArr{5, 4, 3, 2, 1, 0};

        const auto status = dsa_insertion_sort(reverseSortedArr.data(), reverseSortedArr.size(), esize, ascending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(reverseSortedArr));
    }

    SECTION("Sort in ascending order")
    {
        std::vector<T> inputArr{2, 1, 4, 5, 0};
        const auto status = dsa_insertion_sort(inputArr.data(), inputArr.size(), esize, ascending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(inputArr));
    }

    SECTION("Sort in descending order")
    {
        std::vector<T> inputArr{2, 1, 4, 5, 0};
        const auto status = dsa_insertion_sort(inputArr.data(), inputArr.size(), esize, descending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(inputArr, std::greater<>()));
    }

    SECTION("Sort with random input array")
    {
        std::vector<T> inputArr(100);
        std::iota(inputArr.begin(), inputArr.end(), 0);
        std::shuffle(inputArr.begin(), inputArr.end(), std::mt19937{std::random_device{}()});

        const auto status = dsa_insertion_sort(inputArr.data(), inputArr.size(), esize, ascending_compare<T>);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(inputArr));
    }
}

TEST_CASE("Insertion sort with const char*", "[InsertionSort][CString]")
{
    std::vector<const char*> input{"grape", "kiwi", "fig", "banana", "apple", "cherry", "date"};

    const size_t size = input.size();
    const size_t esize = sizeof(const char*);

    SECTION("Sort in ascending order")
    {
        const auto status = dsa_insertion_sort(input.data(), size, esize, compare_strings_ascending);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(input, [](const char* a, const char* b){
            return std::strcmp(a, b) < 0;
        }));
    }

    SECTION("Sort in descending order")
    {
        const auto status = dsa_insertion_sort(input.data(), size, esize, compare_strings_descending);
        REQUIRE(status == DSA_SUCCESS);
        REQUIRE(std::ranges::is_sorted(input, [](const char* a, const char* b){
            return std::strcmp(a, b) > 0;
        }));
    }
}
