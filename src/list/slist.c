#include "dsa/list/slist.h"

#include <stdlib.h>

typedef struct _slist_node_t
{
    void* data;
    struct _slist_node_t* next;
}_slist_node_t;

struct slist
{
    _slist_node_t* head;
    _slist_node_t* tail;
    size_t size;
    slist_destroy_element_func destroy_func;
};

static _slist_node_t* _create_node(void* data, _slist_node_t* next)
{
    _slist_node_t* new_node = malloc(sizeof(*new_node));
    if (!new_node)
    {
        return NULL;
    }

    new_node->data = data;
    new_node->next = next;

    return new_node;
}

static void _delete_node(_slist_node_t* node, slist_destroy_element_func func)
{
    if (!node)
    {
        return;
    }

    if (func)
    {
        func(node->data);
    }

    node->data = NULL;
    free(node);
}

dsa_error_code_t dsa_slist_create(slist_t* handle, slist_destroy_element_func func)
{
    if (!handle)
    {
        return DSA_INVALID_INPUT;
    }

    *handle = malloc(sizeof(**handle));

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

    *tail = handle->tail ? handle->tail->data : NULL;

    return DSA_SUCCESS;
}

dsa_error_code_t dsa_slist_get_size(const slist_t handle, size_t* size)
{
    if (!handle || !size)
    {
        return DSA_INVALID_INPUT;
    }

    *size = handle->size;

    return DSA_SUCCESS;
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
    if (!handle || !data)
    {
        return DSA_INVALID_INPUT;
    }

    _slist_node_t* new_node = _create_node(data, handle->head);
    if (!new_node)
    {
        return DSA_ALLOC_FAILURE;
    }

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
    if (!handle || !data)
    {
        return DSA_INVALID_INPUT;
    }

    _slist_node_t* new_node = _create_node(data, NULL);
    if (!new_node)
    {
        return DSA_ALLOC_FAILURE;
    }

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

dsa_error_code_t dsa_slist_pop_front(slist_t handle)
{
    if (!handle)
    {
        return DSA_INVALID_INPUT;
    }

    if (handle->size == 0)
    {
        return DSA_EMPTY_LIST;
    }

    _slist_node_t* node = handle->head;
    handle->head = node->next;

    _delete_node(node, handle->destroy_func);

    --handle->size;

    if (handle->size == 0)
    {
        handle->tail = NULL;
    }

    return DSA_SUCCESS;
}

dsa_error_code_t dsa_slist_pop_back(slist_t handle)
{
    if (!handle)
    {
        return DSA_INVALID_INPUT;
    }

    if (handle->size == 0)
    {
        return DSA_EMPTY_LIST;
    }

    if (handle->size == 1)
    {
        _slist_node_t* node = handle->head;
        _delete_node(node, handle->destroy_func);
        handle->head = NULL;
        handle->tail = NULL;
        --handle->size;
        return DSA_SUCCESS;
    }

    _slist_node_t* current = handle->head;

    while (current->next != handle->tail)
    {
        current = current->next;
    }

    _slist_node_t* node = current->next;
    current->next = NULL;
    _delete_node(node, handle->destroy_func);

    --handle->size;

    handle->tail = current;

    return DSA_SUCCESS;
}

dsa_error_code_t dsa_slist_clear(slist_t handle)
{
    if (!handle)
    {
        return DSA_INVALID_INPUT;
    }

    if (handle->size == 0)
    {
        return DSA_SUCCESS;
    }

    _slist_node_t* current = handle->head;
    while (current)
    {
        _slist_node_t* next = current->next;
        _delete_node(current, handle->destroy_func);
        current = next;
    }

    handle->head = NULL;
    handle->tail = NULL;
    handle->size = 0;
    return DSA_SUCCESS;
}

dsa_error_code_t dsa_slist_reverse(slist_t handle)
{
    if (!handle)
    {
        return DSA_INVALID_INPUT;
    }

    handle->tail = handle->head;
    _slist_node_t* current = handle->head;
    _slist_node_t* prev = NULL;
    while (current)
    {
        _slist_node_t* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    handle->head = prev;

    return DSA_SUCCESS;
}

void dsa_slist_destroy(slist_t handle)
{
    if (!handle)
    {
        return;
    }

    _slist_node_t* current = handle->head;
    while (current)
    {
        _slist_node_t* next = current->next;
        _delete_node(current, handle->destroy_func);
        current = next;
    }

    free(handle);
}
