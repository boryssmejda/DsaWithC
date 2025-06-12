#include "dsa/utility/max_element.h"

size_t dsa_max_element(
    const void* const arr,
    const size_t count,
    const size_t elem_size,
    bool (*compare)(const void* a, const void* b))
{
    if (!arr || count == 0 || elem_size == 0 || !compare)
    {
        return count;
    }

    const unsigned char* const buffer = arr;

    size_t max_index = 0;
    for (size_t i = 1; i < count; i++)
    {
        const unsigned char* current = buffer + i * elem_size;
        const unsigned char* max_element = buffer + max_index * elem_size;
        if (compare(current, max_element))
        {
            max_index = i;
        }
    }

    return max_index;
}
