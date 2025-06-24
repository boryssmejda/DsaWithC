#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Returns the index of the maximum element in a generic array.
 *
 * This function finds the index of the maximum element in an array using
 * a user-provided comparison function. If multiple elements are equal to
 * the maximum, the index of the first one is returned.
 *
 * @param arr Pointer to the first element of the array.
 * @param count Number of elements in the array.
 * @param elem_size Size of each element in bytes.
 * @param compare Pointer to a comparison function. It must return:
 *        - a negative value if a < b,
 *        - zero if a == b,
 *        - a positive value if a > b.
 * @return The index of the maximum element in the array,
 *         or @p count if the input is invalid (e.g., null pointer or count is zero).
 *
 * @note The caller must ensure that the memory pointed to by @p arr is valid
 *       and contains at least @p count elements of size @p elem_size.
 *
 * @note If there are multiple elements equal to the maximum, the first such
 *       element (i.e., with the lowest index) is returned.
 *
 * @complexity O(n), where n is the number of elements in the array.
 */
size_t dsa_max_element(const void* arr, const size_t count, const size_t elem_size, int (*compare)(const void* a, const void* b));

#ifdef __cplusplus
}
#endif
