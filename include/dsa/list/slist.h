/**
 * @file slist.h
 * @brief Singly linked list interface using an opaque handle.
 *
 * This module provides an abstract singly linked list implementation in C.
 * It supports optional ownership of elements via a destroy callback.
 */

#pragma once

#include "dsa/common/error_codes.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque struct representing a singly linked list.
 *
 * Users should treat this as an abstract handle and not access its fields directly.
 */
struct slist;

/**
 * @brief Handle to a singly linked list.
 */
typedef struct slist* slist_t;

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
 * @brief Retrieves the data stored in the tail node of the list.
 *
 * @param[in] handle List handle.
 * @param[out] tail Pointer to the tail data. Set to NULL if the list is empty.
 * @return `DSA_SUCCESS` on success, `DSA_INVALID_INPUT` if arguments are invalid.
 */
dsa_error_code_t dsa_slist_get_tail(slist_t handle, void** tail);

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
 * @brief Checks whether the list is empty.
 *
 * This operation runs in constant time (O(1)).
 *
 * @param[in] handle List handle.
 * @param[out] is_empty Pointer to a boolean that will be set to true if the list is empty, false otherwise.
 * @return `DSA_SUCCESS` on success, `DSA_INVALID_INPUT` if arguments are invalid.
 */
dsa_error_code_t dsa_slist_is_empty(slist_t handle, bool* is_empty);

/**
 * @brief Inserts a new element at the front of the list.
 *
 * This operation runs in constant time O(1).
 *
 * @param[in] handle List handle.
 * @param[in] data Pointer to the data to insert. Must not be NULL.
 * @return `DSA_SUCCESS` on success, `DSA_INVALID_INPUT` on bad arguments,
 *         or `DSA_ALLOC_FAILURE` if memory allocation fails.
 */
dsa_error_code_t dsa_slist_push_front(slist_t handle, void* data);

/**
 * @brief Inserts a new element at the back of the list.
 *
 * This operation runs in constant time O(1).
 *
 * @param[in] handle List handle.
 * @param[in] data Pointer to the data to insert. Must not be NULL.
 * @return `DSA_SUCCESS` on success, `DSA_INVALID_INPUT` on bad arguments,
 *         or `DSA_ALLOC_FAILURE` if memory allocation fails.
 */
dsa_error_code_t dsa_slist_push_back(slist_t handle, void* data);

/**
 * @brief Removes the element at the front of the list.
 *
 * This operation runs in constant time O(1).
 * If a destroy function was provided at list creation, it is called on the removed element's data.
 *
 * @param[in] handle List handle.
 * @return `DSA_SUCCESS` on success, `DSA_INVALID_INPUT` on bad arguments,
 *         or `DSA_EMPTY_LIST` if the list is empty.
 */
dsa_error_code_t dsa_slist_pop_front(slist_t handle);

/**
 * @brief Removes the element at the back of the list.
 *
 * This operation runs in linear time O(n), since the list must be traversed to find the second-last node.
 * If a destroy function was provided at list creation, it is called on the removed element's data.
 *
 * @param[in] handle List handle.
 * @return `DSA_SUCCESS` on success, `DSA_INVALID_INPUT` on bad arguments,
 *         or `DSA_EMPTY_LIST` if the list is empty.
 */
dsa_error_code_t dsa_slist_pop_back(slist_t handle);

/**
 * @brief Removes all elements from the list, calling the destroy function if set.
 *
 * This operation runs in linear time O(n).
 * After this call, the list is empty but still valid.
 *
 * @param[in] handle List handle.
 * @return `DSA_SUCCESS` on success, `DSA_INVALID_INPUT` if the handle is NULL.
 */
dsa_error_code_t dsa_slist_clear(slist_t handle);

/**
 * @brief Reverses the order of elements in the singly linked list.
 *
 * This operation runs in linear time O(n) and modifies the list in place.
 *
 * @param[in] handle List handle.
 * @return `DSA_SUCCESS` on success, `DSA_INVALID_INPUT` if the handle is NULL.
 */
dsa_error_code_t dsa_slist_reverse(slist_t handle);


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
