#include "dsa/list/slist.h"

#include <stdlib.h>

typedef struct slist_node_t
{
    void* data;
    struct slist_node_t* next;
}slist_node_t;

struct slist_t
{
    slist_node_t* head;
    slist_node_t* tail;
    size_t size;
    slist_destroy_element_func destroy_func;
};

dsa_error_code_t dsa_slist_create(slist_t* handle, slist_destroy_element_func func)
{
    if (!handle)
    {
        return DSA_INVALID_INPUT;
    }

    *handle = malloc(sizeof(slist_t));

    if (!(*handle))
    {
        return DSA_ALLOC_FAILURE;
    }

    (*handle)->head = NULL;
    (*handle)->tail = NULL;
    (*handle)->size = 0;
    (*handle)->destroy_func = func;

    return DSA_SUCCESS;
}

dsa_error_code_t dsa_slist_get_head(slist_t handle, void** head)
{
    if (!handle || !head)
    {
        return DSA_INVALID_INPUT;
    }

    *head = handle->head ? handle->head->data : NULL;
    return DSA_SUCCESS;
}

dsa_error_code_t dsa_slist_get_tail(slist_t handle, void** tail)
{
    if (!handle || !tail)
    {
        return DSA_INVALID_INPUT;
    }

    *tail = handle->tail;

    return DSA_SUCCESS;
}

dsa_error_code_t dsa_slist_get_size(slist_t handle, size_t* size)
{
    if (!handle || !size)
    {
        return DSA_INVALID_INPUT;
    }

    return handle->size;
}

dsa_error_code_t dsa_slist_is_empty(slist_t handle, bool* is_empty)
{
    if (!handle || !is_empty)
    {
        return DSA_INVALID_INPUT;
    }

    *is_empty = (handle->size == 0);
    return DSA_SUCCESS;
}

dsa_error_code_t dsa_slist_push_front(slist_t handle, void* data)
{
    if (!handle)
    {
        return DSA_INVALID_INPUT;
    }

    slist_node_t* new_node = malloc(sizeof(slist_node_t));
    if (!new_node)
    {
        return DSA_ALLOC_FAILURE;
    }

    new_node->data = data;

    new_node->next = handle->head;
    handle->head = new_node;

    if (handle->size == 0)
    {
        handle->tail = new_node;
    }

    ++handle->size;
    return DSA_SUCCESS;
}

dsa_error_code_t dsa_slist_push_back(slist_t handle, void* data)
{
    if (!handle)
    {
        return DSA_INVALID_INPUT;
    }

    slist_node_t* new_node = malloc(sizeof(slist_node_t));
    if (!new_node)
    {
        return DSA_ALLOC_FAILURE;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (handle->size == 0)
    {
        handle->head = new_node;
    }
    else
    {
        handle->tail->next = new_node;
    }

    handle->tail = new_node;
    ++handle->size;

    return DSA_SUCCESS;
}

dsa_error_code_t dsa_slist_pop_front(slist_t handle);

dsa_error_code_t dsa_slist_pop_back(slist_t handle);

void dsa_slist_destroy(slist_t handle)
{
    if (!handle)
    {
        return;
    }

    slist_node_t* current = handle->head;
    while (current)
    {
        slist_node_t* next = current->next;
        if (handle->destroy_func)
        {
            handle->destroy_func(current->data);
        }

        free(current);
        current = next;
    }

    free(handle);
}
