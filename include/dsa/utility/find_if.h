#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Find the index of the first element in an array that matches a predicate.
 *
 * Iterates over an array and applies the given predicate function to each element.
 * Returns the index of the first element for which the predicate returns true.
 *
 * @param data Pointer to the start of the array.
 * @param count Number of elements in the array.
 * @param esize Size of each element in bytes.
 * @param compare Pointer to a function that takes an element pointer and returns true if it matches.
 * @return Index of the matching element in the range [0, count), or count if no match is found or input is invalid.
 *
 * @note Time complexity: O(n) in the worst case, O(1) in the best case.
 */
size_t dsa_find_if(
    const void* data,
    const size_t count,
    const size_t esize,
    bool (*compare)(const void* arg));

/**
 * @brief Find the index of the first element in an array that matches a predicate with context.
 *
 * Iterates over an array and applies the given predicate function (with context) to each element.
 * Returns the index of the first element for which the predicate returns true.
 *
 * @param data Pointer to the start of the array.
 * @param count Number of elements in the array.
 * @param esize Size of each element in bytes.
 * @param compare Pointer to a function that takes an element pointer and a non-NULL context pointer,
 *                and returns true if it matches.
 * @param ctx Pointer to user-defined context data passed to the compare function. Must not be NULL.
 * @return Index of the matching element in the range [0, count), or count if no match is found or input is invalid.
 *
 * @note Time complexity: O(n) in the worst case, O(1) in the best case.
 */
size_t dsa_find_if_ctx(
    const void* data,
    const size_t count,
    const size_t esize,
    bool (*compare)(const void* arg, const void* ctx),
    const void* ctx);

#ifdef __cplusplus
}
#endif
