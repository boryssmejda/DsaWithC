#include "dsa/utility/for_each.h"

typedef struct
{
    void (*operation)(void*);
} dsa_op_wrapper;

static void dsa_forward_operation(void* elem, void* ctx)
{
    dsa_op_wrapper* wrapper = (dsa_op_wrapper*)ctx;
    wrapper->operation(elem);
}

dsa_error_code_t dsa_for_each_ctx(void* arr, const size_t count, const size_t elem_size, dsa_operation_with_context operation, void* ctx)
{
    if (!arr || count == 0 || elem_size == 0 || !operation || !ctx)
    {
        return DSA_INVALID_INPUT;
    }

    unsigned char* buffer = arr;

    for (size_t i = 0; i < count; i++)
    {
        unsigned char* current = buffer + i * elem_size;
        operation(current, ctx);
    }

    return DSA_SUCCESS;
}

dsa_error_code_t dsa_for_each(void* arr, const size_t count, const size_t elem_size, dsa_operation_no_context operation)
{
    if (!operation)
    {
        return DSA_INVALID_INPUT;
    }

    dsa_op_wrapper wrapper = { .operation = operation };

    return dsa_for_each_ctx(arr, count, elem_size, dsa_forward_operation, &wrapper);
}
