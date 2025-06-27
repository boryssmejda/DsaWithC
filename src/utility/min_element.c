#include "dsa/utility/min_element.h"

dsa_error_code_t dsa_min_element_index(
    const void* arr,
    const size_t size,
    const size_t elem_size,
    int (*compare)(const void* a, const void* b),
    size_t* min_element_index)
{
    if (!arr || size == 0 || elem_size == 0 || !compare || !min_element_index)
    {
        return DSA_INVALID_INPUT;
    }

    const unsigned char* const buffer = arr;

    *min_element_index = 0;
    for (size_t i = 1; i < size; i++)
    {
        const unsigned char* current = buffer + i * elem_size;
        const unsigned char* min_element = buffer + *min_element_index* elem_size;
        if (compare(current, min_element) < 0)
        {
            *min_element_index = i;
        }
    }

    return DSA_SUCCESS;
}
