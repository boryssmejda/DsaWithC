#pragma once

#include "dsa/common/error_codes.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Finds the index of the minimum element in a generic array.
 *
 * This function searches a generic array for the minimum element, using
 * a user-provided comparison function. The index of the first occurrence
 * of the minimum element is returned via the @p min_element_index output parameter.
 *
 * @param arr Pointer to the first element of the array.
 * @param size Number of elements in the array.
 * @param elem_size Size of each element in bytes.
 * @param compare Pointer to a comparison function. It must return:
 *        - a negative value if a < b,
 *        - zero if a == b,
 *        - a positive value if a > b.
 * @param min_element_index Pointer to a variable where the result (index of the minimum element) will be stored.
 * @return DSA_SUCCESS on success;
 *         DSA_INVALID_INPUT if any input is invalid (e.g., null pointers, zero size, or invalid compare function).
 *
 * @note The caller must ensure that the memory pointed to by @p arr is valid
 *       and contains at least @p size elements of @p elem_size bytes each.
 *
 * @note If multiple elements are equal to the minimum, the index of the first such
 *       element (i.e., with the lowest index) is returned.
 *
 * @complexity O(n), where n is the number of elements in the array.
 */
dsa_error_code_t dsa_min_element_index(
    const void* arr,
    const size_t size,
    const size_t elem_size,
    int (*compare)(const void* a, const void* b),
    size_t* min_element_index);

#ifdef __cplusplus
}
#endif
