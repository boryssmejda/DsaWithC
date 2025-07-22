#include "dsa/list/slist.h"

#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <cstring>

namespace
{
void destroy_string(void* data)
{
    delete[] static_cast<char*>(data);
}
} // namespace

TEST_CASE("Create and destroy slist")
{
    slist_t list = nullptr;
    REQUIRE(dsa_slist_create(&list, nullptr) == DSA_SUCCESS);
    REQUIRE(list != nullptr);
    dsa_slist_destroy(list);
}

TEST_CASE("Push front and back, get head and tail")
{
    slist_t list = nullptr;
    REQUIRE(dsa_slist_create(&list, nullptr) == DSA_SUCCESS);
    REQUIRE(list != nullptr);

    const char* val1 = "first";
    const char* val2 = "second";

    REQUIRE(dsa_slist_push_front(list, (void*)val1) == DSA_SUCCESS);
    REQUIRE(dsa_slist_push_back(list, (void*)val2) == DSA_SUCCESS);

    std::size_t size = 0;
    REQUIRE(dsa_slist_get_size(list, &size) == DSA_SUCCESS);
    REQUIRE(size == 2);

    void* head = nullptr;
    void* tail = nullptr;
    REQUIRE(dsa_slist_get_head(list, &head) == DSA_SUCCESS);
    REQUIRE(dsa_slist_get_tail(list, &tail) == DSA_SUCCESS);

    REQUIRE(strcmp(static_cast<const char*>(head), val1) == 0);
    REQUIRE(strcmp(static_cast<const char*>(tail), val2) == 0);

    dsa_slist_destroy(list);
}

TEST_CASE("Pushing NULL data pointer is an error")
{
    slist_t list = nullptr;
    REQUIRE(dsa_slist_create(&list, nullptr) == DSA_SUCCESS);

    REQUIRE(dsa_slist_push_front(list, NULL) == DSA_INVALID_INPUT);
    REQUIRE(dsa_slist_push_back(list, NULL) == DSA_INVALID_INPUT);

    dsa_slist_destroy(list);
}

TEST_CASE("Check size and is_empty")
{
    slist_t list = nullptr;
    REQUIRE(dsa_slist_create(&list, nullptr) == DSA_SUCCESS);

    bool empty;
    size_t size;

    REQUIRE(dsa_slist_is_empty(list, &empty) == DSA_SUCCESS);
    REQUIRE(empty == true);

    REQUIRE(dsa_slist_push_back(list, (void*)"abc") == DSA_SUCCESS);

    REQUIRE(dsa_slist_get_size(list, &size) == DSA_SUCCESS);
    REQUIRE(size == 1);

    REQUIRE(dsa_slist_is_empty(list, &empty) == DSA_SUCCESS);
    REQUIRE(empty == false);

    dsa_slist_destroy(list);
}

TEST_CASE("Pop front and back")
{
    slist_t list = nullptr;
    REQUIRE(dsa_slist_create(&list, nullptr) == DSA_SUCCESS);

    REQUIRE(dsa_slist_push_back(list, (void*)"one") == DSA_SUCCESS);
    REQUIRE(dsa_slist_push_back(list, (void*)"two") == DSA_SUCCESS);

    REQUIRE(dsa_slist_pop_front(list) == DSA_SUCCESS);

    void* head = nullptr;
    REQUIRE(dsa_slist_get_head(list, &head) == DSA_SUCCESS);
    REQUIRE(strcmp(static_cast<const char*>(head), "two") == 0);

    REQUIRE(dsa_slist_pop_back(list) == DSA_SUCCESS);

    bool empty;
    REQUIRE(dsa_slist_is_empty(list, &empty) == DSA_SUCCESS);
    REQUIRE(empty == true);

    dsa_slist_destroy(list);
}

TEST_CASE("Clear list")
{
    slist_t list = nullptr;
    REQUIRE(dsa_slist_create(&list, nullptr) == DSA_SUCCESS);

    REQUIRE(dsa_slist_push_back(list, (void*)"one") == DSA_SUCCESS);
    REQUIRE(dsa_slist_push_back(list, (void*)"two") == DSA_SUCCESS);

    REQUIRE(dsa_slist_clear(list) == DSA_SUCCESS);

    bool empty;
    size_t size;
    REQUIRE(dsa_slist_is_empty(list, &empty) == DSA_SUCCESS);
    REQUIRE(dsa_slist_get_size(list, &size) == DSA_SUCCESS);

    REQUIRE(empty == true);
    REQUIRE(size == 0);

    dsa_slist_destroy(list);
}

TEST_CASE("Reverse list")
{
    slist_t list = nullptr;
    REQUIRE(dsa_slist_create(&list, nullptr) == DSA_SUCCESS);

    REQUIRE(dsa_slist_push_back(list, (void*)"A") == DSA_SUCCESS);
    REQUIRE(dsa_slist_push_back(list, (void*)"B") == DSA_SUCCESS);
    REQUIRE(dsa_slist_push_back(list, (void*)"C") == DSA_SUCCESS);

    REQUIRE(dsa_slist_reverse(list) == DSA_SUCCESS);

    void* head = nullptr;
    void* tail = nullptr;
    REQUIRE(dsa_slist_get_head(list, &head) == DSA_SUCCESS);
    REQUIRE(dsa_slist_get_tail(list, &tail) == DSA_SUCCESS);

    REQUIRE(strcmp(static_cast<const char*>(head), "C") == 0);
    REQUIRE(strcmp(static_cast<const char*>(tail), "A") == 0);

    dsa_slist_destroy(list);
}

TEST_CASE("Destroy list with custom destroy callback")
{
    slist_t list = nullptr;
    REQUIRE(dsa_slist_create(&list, destroy_string) == DSA_SUCCESS);

    char* str1 = new char[6];
    char* str2 = new char[6];
    std::strcpy(str1, "hello");
    std::strcpy(str2, "world");

    REQUIRE(dsa_slist_push_back(list, str1) == DSA_SUCCESS);
    REQUIRE(dsa_slist_push_back(list, str2) == DSA_SUCCESS);

    dsa_slist_destroy(list);
}
