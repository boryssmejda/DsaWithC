#pragma once

#include "dsa/common/error_codes.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Finds the index of the maximum element in a generic array.
 *
 * This function scans an array and determines the index of the element
 * considered largest according to the user-provided comparison function.
 * If multiple elements are equal to the maximum, the index of the first
 * such element is returned.
 *
 * @param arr Pointer to the first element of the array. Must not be NULL.
 * @param size Number of elements in the array. Must be greater than 0.
 * @param elem_size Size in bytes of a single element. Must be greater than 0.
 * @param compare Pointer to a comparison function. The function must return:
 *        - A negative value if (a < b),
 *        - Zero if (a == b),
 *        - A positive value if (a > b).
 * @param[out] max_element_index Pointer to store the resulting index of the maximum element.
 *                Must not be NULL. Set to @p size if input is invalid.
 *
 * @retval DSA_SUCCESS If the operation completed successfully.
 * @retval DSA_INVALID_INPUT If any of the input parameters are invalid.
 *
 * @note The caller is responsible for ensuring that @p arr points to valid
 *       memory containing at least @p size elements of size @p elem_size.
 *
 * @note If the array contains multiple maximum elements, the first (lowest index)
 *       is returned.
 *
 * @complexity O(n), where n is the number of elements in the array.
 */
dsa_error_code_t dsa_max_element_index(
    const void* arr,
    const size_t size,
    const size_t elem_size,
    int (*compare)(const void* a, const void* b),
    size_t* max_element_index);

#ifdef __cplusplus
}
#endif
