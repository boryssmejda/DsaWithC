/**
 * @file slist.h
 * @brief Singly linked list interface using an opaque handle.
 *
 * This module provides an abstract singly linked list implementation in C.
 * It supports optional ownership of elements via a destroy callback.
 */

#pragma once

#include "dsa/common/error_codes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque struct representing a singly linked list.
 *
 * Users should treat this as an abstract handle and not access its fields directly.
 */
struct slist_t;

/**
 * @brief Handle to a singly linked list.
 */
typedef struct slist_t* slist_t;

/**
 * @brief Function pointer type for destroying list elements.
 *
 * This function is called on each element during list destruction
 * if provided to `dsa_slist_create()`.
 *
 * @param data Pointer to the element's data.
 */
typedef void (*slist_destroy_element_func)(void* data);

/**
 * @brief Creates a new singly linked list.
 *
 * @param[out] handle Pointer to a handle that will point to the created list.
 * @param[in] func Optional destructor function for list elements. Pass NULL if not needed.
 * @return `DSA_SUCCESS` on success, or an appropriate error code on failure.
 */
dsa_error_code_t dsa_slist_create(slist_t* handle, slist_destroy_element_func func);

/**
 * @brief Retrieves the data stored in the head node of the list.
 *
 * @param[in] handle List handle.
 * @param[out] head Pointer to the head data. Set to NULL if the list is empty.
 * @return `DSA_SUCCESS` on success, `DSA_INVALID_INPUT` if arguments are invalid.
 */
dsa_error_code_t dsa_slist_get_head(slist_t handle, void** head);

/**
 * @brief Gets the number of elements in the list.
 *
 * This operation runs in constant time O(1).
 *
 * @param[in] handle List handle.
 * @param[out] size Pointer to the variable that will receive the list size.
 * @return `DSA_SUCCESS` on success, `DSA_INVALID_INPUT` on bad arguments.
 */
dsa_error_code_t dsa_slist_get_size(slist_t handle, size_t* size);

/**
 * @brief Destroys the list and frees its memory.
 *
 * If a destroy function was provided at creation, it will be called for each element.
 *
 * @param[in] handle List handle to destroy. Safe to call with NULL.
 */
void dsa_slist_destroy(slist_t handle);

#ifdef __cplusplus
} // extern "C"
#endif
