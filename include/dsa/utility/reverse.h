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
 * It operates on raw memory, so the caller must ensure the input is valid.
 *
 * @param arr Pointer to the first element of the array to reverse.
 * @param count Number of elements in the array.
 * @param elem_size Size of each element in bytes.
 * @return DSA_SUCCESS on success,
 *         DSA_INVALID_INPUT if the input is invalid,
 *         DSA_ALLOC_FAILURE if temporary memory allocation fails.
 *
 * @note The memory pointed to by @p arr must be writable and large enough
 *       to hold @p count elements of size @p elem_size.
 */
dsa_error_code dsa_reverse(void* arr, const size_t count, const size_t elem_size);

#ifdef __cplusplus
}
#endif
