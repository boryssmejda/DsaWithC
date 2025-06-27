#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "dsa/common/error_codes.h"

#include <stddef.h>

/**
 * @brief Performs a binary search on a sorted array to find the index of a target element.
 *
 * Searches for the element pointed to by @p target in the sorted array @p sorted using binary search.
 * The array must contain @p size elements, each of size @p elem_size bytes.
 * The comparison is performed using the user-provided @p compare function.
 *
 * The comparison function must have the following signature:
 * @code
 * int compare(const void* key1, const void* key2);
 * @endcode
 * and return:
 * - a **positive value** if @p key1 is greater than @p key2
 * - `0` if @p key1 is equal to @p key2
 * - a **negative value** if @p key1 is less than @p key2
 *
 * The array must be sorted consistently with the behavior of the @p compare function:
 * - For an ascending-sorted array, @p compare should return positive when @p key1 > @p key2,
 *   negative when @p key1 < @p key2.
 * - For a descending-sorted array, @p compare should return positive when @p key1 < @p key2,
 *   negative when @p key1 > @p key2.
 *
 * @param[in] target Pointer to the element to search for.
 * @param[in] sorted Pointer to the base of the sorted array.
 * @param[in] size Number of elements in the array.
 * @param[in] elem_size Size in bytes of each element in the array.
 * @param[in] compare Comparison function used to determine the order.
 * @param[out] found_index Pointer to a variable where the index of the found element will be stored.
 *                         If the element is not found, @p *found_index will be set to @p size.
 *
 * @retval DSA_SUCCESS If the operation completed successfully.
 * @retval DSA_INVALID_INPUT If any of the input parameters are invalid.
 *
 * @note Time complexity: O(log n), where n is the number of elements in the array.
 */

dsa_error_code_t dsa_binary_search_index(
    const void *target,
    const void *sorted,
    const size_t size,
    const size_t elem_size,
    int (*compare)(const void *key1, const void *key2),
    size_t* found_index);

#ifdef __cplusplus
} // extern "C"
#endif
