#include <catch2/catch_test_macros.hpp>

#include "dsa/common/error_codes.h"

#include <cstring>

TEST_CASE("dsa_strerror returns correct messages", "[dsa_strerror]")
{
    SECTION("DSA_SUCCESS")
    {
        REQUIRE(std::strcmp(dsa_strerror(DSA_SUCCESS), "Success") == 0);
    }

    SECTION("DSA_INVALID_INPUT")
    {
        REQUIRE(std::strcmp(dsa_strerror(DSA_INVALID_INPUT), "Invalid input") == 0);
    }

    SECTION("DSA_ALLOC_FAILURE")
    {
        REQUIRE(std::strcmp(dsa_strerror(DSA_ALLOC_FAILURE), "Allocation failure") == 0);
    }

    SECTION("DSA_EMPTY_LIST")
    {
        REQUIRE(std::strcmp(dsa_strerror(DSA_EMPTY_LIST), "Empty List") == 0);
    }

    SECTION("Unknown error code returns fallback string")
    {
        const dsa_error_code_t unknown = (dsa_error_code_t)999;
        REQUIRE(std::strcmp(dsa_strerror(unknown), "Unknown error") == 0);
    }
}
