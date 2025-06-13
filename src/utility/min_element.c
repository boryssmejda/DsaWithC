#include "dsa/utility/min_element.h"

size_t dsa_min_element(
    const void* const arr,
    const size_t count,
    const size_t elem_size,
    int (*compare)(const void* a, const void* b))
{
    if (!arr || count == 0 || elem_size == 0 || !compare)
    {
        return count;
    }

    const unsigned char* const buffer = arr;

    size_t min_index = 0;
    for (size_t i = 1; i < count; i++)
    {
        const unsigned char* current = buffer + i * elem_size;
        const unsigned char* min_element = buffer + min_index * elem_size;
        if (compare(current, min_element) < 0)
        {
            min_index = i;
        }
    }

    return min_index;
}
