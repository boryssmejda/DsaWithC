#include "dsa/utility/reverse.h"

#include <stdlib.h>
#include <string.h>

dsa_error_code dsa_reverse(void* const arr, const size_t count, const size_t elem_size)
{
    if (!arr || count == 0 || elem_size == 0)
    {
        return DSA_INVALID_INPUT;
    }

    unsigned char* buffer = arr;
    unsigned char* temp = malloc(elem_size);
    if (!temp)
    {
        return DSA_ALLOC_FAILURE;
    }

    size_t begin = 0;
    size_t end = count - 1;

    while (begin < end)
    {
        unsigned char* const begin_ptr = buffer + begin * elem_size;
        unsigned char* const end_ptr = buffer + end * elem_size;

        memcpy(temp, end_ptr, elem_size);
        memcpy(end_ptr, begin_ptr, elem_size);
        memcpy(begin_ptr, temp, elem_size);

        ++begin;
        --end;
    }

    free(temp);
    return DSA_SUCCESS;
}
