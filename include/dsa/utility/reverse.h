#pragma once

#include "dsa/common/error_codes.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Reverses the elements of a generic array in place.
 *
 * This function reverses an array of arbitrary element type and size.
 * It operates on raw memory, swapping elements from both ends of the array
 * until the entire array is reversed.
 *
 * @param arr Pointer to the first element of the array to reverse.
 * @param count Number of elements in the array.
 * @param elem_size Size of each element in bytes.
 * @return @ref DSA_SUCCESS on success,
 *         @ref DSA_INVALID_INPUT if the input is invalid (e.g., null pointer or zero count),
 *         @ref DSA_ALLOC_FAILURE if temporary memory allocation fails.
 *
 * @note The memory pointed to by @p arr must be writable and large enough
 *       to hold @p count elements of size @p elem_size.
 *
 * @note The operation is performed in place, using temporary memory only
 *       for swapping a single element.
 *
 * @complexity O(n), where n is the number of elements in the array.
 *
 * @details Performs ⌊n / 2⌋ swaps of entire elements (each of size @p elem_size).
 */
dsa_error_code_t dsa_reverse(void* arr, const size_t count, const size_t elem_size);

#ifdef __cplusplus
}
#endif
