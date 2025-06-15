#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "dsa/utility/reverse.h"

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
} // namespace

TEST_CASE("dsa_reverse handles valid input", "[dsa_reverse]")
{
    SECTION("Reverse int array of size 4")
    {
        std::array<int, 4> input{1, 2, 3, 4};
        std::array<int, 4> expected{4, 3, 2, 1};

        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(int)) == DSA_SUCCESS);
        REQUIRE(input == expected);
    }

    SECTION("Reverse descending array")
    {
        std::array<int, 3> input{3, 2, 1};
        std::array<int, 3> expected{1, 2, 3};

        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(int)) == DSA_SUCCESS);
        REQUIRE(input == expected);
    }

    SECTION("Reverse int array of size 1")
    {
        std::array<int, 1> input{42};
        std::array<int, 1> expected{42};

        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(int)) == DSA_SUCCESS);
        REQUIRE(input == expected);
    }

    SECTION("Reverse char array")
    {
        std::array<char, 4> input{'a', 'b', 'c', 'd'};
        std::array<char, 4> expected{'d', 'c', 'b', 'a'};

        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(char)) == DSA_SUCCESS);
        REQUIRE(input == expected);
    }

    SECTION("Reverse array of structs")
    {
        std::array<Point, 3> input{{{1, 2}, {3, 4}, {5, 6}}};
        std::array<Point, 3> expected{{{5, 6}, {3, 4}, {1, 2}}};

        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(Point)) == DSA_SUCCESS);
        REQUIRE(input == expected);
    }

    SECTION("Reverse odd-sized array of Points")
    {
        std::array<Point, 5> input{{{1,1}, {2,2}, {3,3}, {4,4}, {5,5}}};
        std::array<Point, 5> expected{{{5,5}, {4,4}, {3,3}, {2,2}, {1,1}}};

        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(Point)) == DSA_SUCCESS);
        REQUIRE(input == expected);
    }

    SECTION("Reverse symmetric array")
    {
        std::array<int, 3> input{1, 2, 1};
        std::array<int, 3> expected{1, 2, 1};

        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(int)) == DSA_SUCCESS);
        REQUIRE(input == expected);
    }

    SECTION("Reverse large int array")
    {
        std::array<int, 1000> input{};
        std::array<int, 1000> expected{};

        for (size_t i = 0; i < input.size(); ++i)
        {
            input[i] = static_cast<int>(i);
            expected[i] = static_cast<int>(input.size() - 1 - i);
        }

        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(int)) == DSA_SUCCESS);
        REQUIRE(input == expected);
    }

    SECTION("Reverse double array")
    {
        std::array<double, 3> input{1.1, 2.2, 3.3};
        std::array<double, 3> expected{3.3, 2.2, 1.1};

        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(double)) == DSA_SUCCESS);

        for (size_t i = 0; i < input.size(); i++)
        {
            constexpr double tolerance{0.0001};
            REQUIRE_THAT(input[i], Catch::Matchers::WithinAbs(expected[i], tolerance));
        }
    }

    SECTION("dsa_reverse reverses only a subrange of an array")
    {
        std::array<int, 6> input{1, 2, 3, 4, 5, 6};
        std::array<int, 6> expected{1, 5, 4, 3, 2, 6};

        // Reverse elements from index 1 to 4 (elements 2, 3, 4, 5)
        REQUIRE(dsa_reverse(input.data() + 1, 4, sizeof(int)) == DSA_SUCCESS);

        REQUIRE(input == expected);
    }

    SECTION("dsa_reverse reversing twice restores original array")
    {
        std::array<int, 6> original{1, 2, 3, 4, 5, 6};
        std::array<int, 6> input = original;

        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(int)) == DSA_SUCCESS);
        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(int)) == DSA_SUCCESS);

        REQUIRE(input == original); // after reversing twice array should look like the original
    }
}

TEST_CASE("dsa_reverse handles invalid input", "[dsa_reverse][error]")
{
    SECTION("Null pointer input")
    {
        REQUIRE(dsa_reverse(nullptr, 4, sizeof(int)) == DSA_INVALID_INPUT);
    }

    SECTION("Zero element size")
    {
        std::array<int, 3> input{1, 2, 3};
        REQUIRE(dsa_reverse(input.data(), input.size(), 0) == DSA_INVALID_INPUT);
    }

    SECTION("Zero count")
    {
        std::array<int, 3> input = {1, 2, 3};
        REQUIRE(dsa_reverse(input.data(), 0, sizeof(int)) == DSA_INVALID_INPUT);
    }

    SECTION("Empty array")
    {
        std::array<int, 0> input{};
        REQUIRE(dsa_reverse(input.data(), input.size(), sizeof(int)) == DSA_INVALID_INPUT);
    }
}

TEST_CASE("reverse works with std::max_align_t", "[dsa_reverse]")
{
    long long a = 1, b = 2, c = 3;
    std::array<std::max_align_t, 3> buffer;
    std::memcpy(&buffer[0], &a, sizeof(a));
    std::memcpy(&buffer[1], &b, sizeof(b));
    std::memcpy(&buffer[2], &c, sizeof(c));

    dsa_reverse(buffer.data(), buffer.size(), sizeof(std::max_align_t));  // Your function

    long long out0, out1, out2;
    std::memcpy(&out0, &buffer[0], sizeof(out0));
    std::memcpy(&out1, &buffer[1], sizeof(out1));
    std::memcpy(&out2, &buffer[2], sizeof(out2));

    REQUIRE(out0 == 3);
    REQUIRE(out1 == 2);
    REQUIRE(out2 == 1);
}
