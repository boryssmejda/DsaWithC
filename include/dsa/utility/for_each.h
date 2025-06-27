#pragma once

#include "dsa/common/error_codes.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Function type for operations on a single element (no context).
 *
 * @param elem Pointer to the element to operate on.
 */
typedef void (*dsa_operation_no_context)(void* elem);

/**
 * @brief Function type for operations on a single element with context.
 *
 * @param elem Pointer to the element to operate on.
 * @param ctx Pointer to a user-provided context object.
 */
typedef void (*dsa_operation_with_context)(void* elem, void* ctx);

/**
 * @brief Applies a user-provided operation to each element of an array.
 *
 * This function iterates over all elements in a generic array and applies
 * the given operation function to each one. The operation is performed in-place.
 *
 * @param arr Pointer to the first element of the array.
 * @param count Number of elements in the array.
 * @param elem_size Size (in bytes) of each element.
 * @param operation A function that operates on a single element.
 *
 * @return @ref DSA_SUCCESS on success,
 *         @ref DSA_ERROR_INVALID_ARGUMENT if any pointer is NULL or count is zero.
 *
 * @note The operation is applied in order from index 0 to count - 1.
 * @note The memory pointed to by @p arr must be valid and mutable.
 *
 * @complexity O(n), where n is the number of elements.
 */
dsa_error_code_t dsa_for_each(void* arr, const size_t count, const size_t elem_size, dsa_operation_no_context operation);

/**
 * @brief Applies a user-provided operation with context to each element of an array.
 *
 * This function is similar to @ref dsa_for_each but allows the user to pass
 * an additional context pointer to the operation function.
 *
 * @param arr Pointer to the first element of the array.
 * @param count Number of elements in the array.
 * @param elem_size Size (in bytes) of each element.
 * @param operation A function that operates on a single element with context.
 * @param ctx Pointer to user-defined context data (can be NULL).
 *
 * @return @ref DSA_SUCCESS on success,
 *         @ref DSA_ERROR_INVALID_ARGUMENT if @p arr or @p operation is NULL, or @p count is zero.
 *
 * @note The operation is applied in order from index 0 to count - 1.
 * @note The memory pointed to by @p arr must be valid and mutable.
 *
 * @complexity O(n), where n is the number of elements.
 */
dsa_error_code_t dsa_for_each_ctx(void* arr, const size_t count, const size_t elem_size, dsa_operation_with_context operation, void* ctx);

#ifdef __cplusplus
}
#endif
