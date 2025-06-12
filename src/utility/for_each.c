#include "dsa/utility/for_each.h"

dsa_error_code dsa_for_each(void* arr, const size_t count, const size_t elem_size, void (*operation)(void* arg))
{
    if (!arr || count == 0 || elem_size == 0 || !operation)
    {
        return DSA_INVALID_INPUT;
    }

    unsigned char* buffer = arr;

    for (size_t i = 0; i < count; i++)
    {
        unsigned char* current = buffer + i * elem_size;
        operation(current);
    }

    return DSA_SUCCESS;
}
