#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Sorts an array of elements using insertion sort.
 *
 * Uses insertion sort to sort the array of elements in @p data.
 * The number of elements is specified by @p size.
 * The size of each element is given by @p esize.
 * The function pointer @p compare specifies a user-defined
 * function to compare elements.
 *
 * The comparison function must follow the signature:
 * @code
 * int compare(const void* key1, const void* key2);
 * @endcode
 * and return:
 * - `1` if @p key1 is greater than @p key2
 * - `0` if @p key1 is equal to @p key2
 * - `-1` if @p key1 is less than @p key2
 *
 * For a descending sort, @p compare should reverse the first and last cases:
 * - `1` if @p key1 is less than @p key2
 * - `0` if @p key1 is equal to @p key2
 * - `-1` if @p key1 is greater than @p key2
 *
 * @param[in,out] data Array of elements to sort.
 * @param[in] size Number of elements in @p data.
 * @param[in] esize Size of a single element, in bytes.
 * @param[in] compare Comparison function used to determine order.
 *
 * @return 0 on success, -1 on failure (e.g., invalid input).
 *
 * When the function returns, @p data contains the sorted elements.
 *
 * @note This is a stable sort: equal elements retain their original order.
 *
 * @complexity Time: Best case O(n); Average/Worst case O(n²).
 * Space: O(1) — sorting is done in-place using constant auxiliary memory.
 */

bool dsa_issort(
    void *data,
    const size_t size,
    const size_t esize,
    int (*compare)(const void *key1, const void *key2));
