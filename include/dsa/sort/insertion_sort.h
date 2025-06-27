#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "dsa/common/error_codes.h"

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
 * @return @ref DSA_SUCCESS on success,
 *         @ref DSA_INVALID_INPUT if the input is invalid (e.g., null pointer or zero count),
 *         @ref DSA_ALLOC_FAILURE if temporary memory allocation fails.
 *
 * When the function returns, @p data contains the sorted elements.
 *
 * @note This function performs a stable sort: equal elements retain their original order.
 *       The array is sorted in-place.
 *
 * @complexity
 * Time: O(n) best case (already sorted), O(n²) average and worst case.
 * Space: O(1) — in-place sort using constant auxiliary memory.
 */

dsa_error_code_t dsa_insertion_sort(
    void *data,
    const size_t size,
    const size_t esize,
    int (*compare)(const void *key1, const void *key2));

#ifdef __cplusplus
} // extern "C"
#endif
