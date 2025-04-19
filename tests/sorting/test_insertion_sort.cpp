#include <catch2/catch_test_macros.hpp>

#include <array>

extern "C"
{
#include "insertion_sort.h"
}

int compare_ints_ascending(const void* first, const void* second)
{
    const int a = *(const int*)first;
    const int b = *(const int*)second;

    return (a > b) - (a < b);
}

int compare_ints_descending(const void* first, const void* second)
{
    const int a = *(const int*)first;
    const int b = *(const int*)second;

    return (b > a) - (b < a);
}

TEST_CASE("Insertion sort handles nullptr array", "[InsertionSort]")
{
    void* arrData = nullptr;
    const size_t size = 0;
    const size_t esize = 0;
    int (*compare)(const void*, const void*) = nullptr;

    REQUIRE(dsa_issort(arrData, size, esize, compare) == -1);
}

TEST_CASE("Insertion sort handles size 0", "[InsertionSort]")
{
    std::array<int, 3> intArr{1, 2, 3};
    const size_t size = 0;
    const size_t esize = sizeof(intArr[0]);
    int (*compare)(const void*, const void*) = nullptr;

    REQUIRE(dsa_issort(static_cast<void*>(intArr.data()), size, esize, compare) == -1);
}

TEST_CASE("Insertion sort handles element size 0", "[InsertionSort]")
{
    std::array<int, 3> intArr{1, 2, 3};
    const size_t size = intArr.size();
    const size_t esize = 0;
    int (*compare)(const void*, const void*) = nullptr;

    REQUIRE(dsa_issort(static_cast<void*>(intArr.data()), size, esize, compare) == -1);
}

TEST_CASE("Insertion sort handles nullptr compare function", "[InsertionSort]")
{
    std::array<int, 3> intArr{1, 2, 3};
    const size_t size = intArr.size();
    const size_t esize = sizeof(intArr[0]);
    int (*compare)(const void*, const void*) = nullptr;

    REQUIRE(dsa_issort(static_cast<void*>(intArr.data()), size, esize, compare) == -1);
}

TEST_CASE("Insertion sort sorts int array in ascending order", "[InsertionSort]")
{
    std::array<int, 5> intArr{5, 2, 4, 1, 3};
    const size_t size = intArr.size();
    const size_t esize = sizeof(intArr[0]);
    int (*compare)(const void*, const void*) = compare_ints_ascending;

    REQUIRE(dsa_issort(static_cast<void*>(intArr.data()), size, esize, compare) == 0);

    std::array<int, 5> expectedArray{1, 2, 3, 4, 5};
    REQUIRE(intArr == expectedArray);
}

TEST_CASE("Insertion sort sorts int array in descending order", "[InsertionSort]")
{
    std::array<int, 5> intArr{5, 2, 4, 1, 3};
    const size_t size = intArr.size();
    const size_t esize = sizeof(intArr[0]);
    int (*compare)(const void*, const void*) = compare_ints_descending;

    REQUIRE(dsa_issort(static_cast<void*>(intArr.data()), size, esize, compare) == 0);

    std::array<int, 5> expectedArray{5, 4, 3, 2, 1};
    REQUIRE(intArr == expectedArray);
}

TEST_CASE("Insertion sort does not change sorted array in ascending order", "[InsertionSort]")
{
    std::array<int, 5> intArr{1, 2, 3, 4, 5};
    const size_t size = intArr.size();
    const size_t esize = sizeof(intArr[0]);
    int (*compare)(const void*, const void*) = compare_ints_ascending;

    REQUIRE(dsa_issort(static_cast<void*>(intArr.data()), size, esize, compare) == 0);

    std::array<int, 5> expectedArray{1, 2, 3, 4, 5};
    REQUIRE(intArr == expectedArray);
}

TEST_CASE("Insertion sort does not change sorted array in descending order", "[InsertionSort]")
{
    std::array<int, 5> intArr{5, 4, 3, 2, 1};
    const size_t size = intArr.size();
    const size_t esize = sizeof(intArr[0]);
    int (*compare)(const void*, const void*) = compare_ints_descending;

    REQUIRE(dsa_issort(static_cast<void*>(intArr.data()), size, esize, compare) == 0);

    std::array<int, 5> expectedArray{5, 4, 3, 2, 1};
    REQUIRE(intArr == expectedArray);
}

// test that algorithm is stable.
