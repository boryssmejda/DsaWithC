#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Count the number of elements in an array that match a predicate.
 *
 * Iterates over an array and applies the given predicate function to each element.
 * Returns the number of elements for which the predicate returns true.
 *
 * @param data Pointer to a contiguous block of memory representing the array elements.
 * @param size Number of elements in the array.
 * @param esize Size of each element in bytes.
 * @param compare Predicate function that takes an element pointer and returns true if it matches.
 * @return Number of matching elements. Returns 0 if no matches are found or if input is invalid.
 *
 * @note Time complexity: O(n)
 */
size_t dsa_count_if(
    const void* data,
    const size_t size,
    const size_t esize,
    bool (*compare)(const void* arg));

/**
 * @brief Count the number of elements in an array that match a predicate with context.
 *
 * Iterates over an array and applies the given predicate function (with context) to each element.
 * Returns the number of elements for which the predicate returns true.
 *
 * @param data Pointer to a contiguous block of memory representing the array elements.
 * @param size Number of elements in the array.
 * @param esize Size of each element in bytes.
 * @param compare Predicate function that takes an element pointer and a non-NULL context pointer,
 *                and returns true if it matches.
 * @param ctx Pointer to user-defined context data passed to the compare function. Must not be NULL.
 * @return Number of matching elements. Returns 0 if no matches are found or if input is invalid.
 *
 * @note Time complexity: O(n)
 */
size_t dsa_count_if_ctx(
    const void* data,
    const size_t size,
    const size_t esize,
    bool (*compare)(const void* arg, const void* ctx),
    const void* ctx);

#ifdef __cplusplus
}
#endif
