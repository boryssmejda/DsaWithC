#include "dsa/search/binary_search.h"

dsa_error_code_t dsa_binary_search_index(
    const void *target,
    const void *sorted,
    const size_t size,
    const size_t elem_size,
    int (*compare)(const void *key1, const void *key2),
    size_t* found_index)
{
    if (!target || !sorted || size == 0 || elem_size == 0 || !compare || !found_index)
    {
        return DSA_INVALID_INPUT;
    }

    size_t left = 0;
    size_t right = size;
    const char* buffer = sorted;

    while (left < right)
    {
        const size_t middle = left + (right - left) / 2;

        const int comparison_result = compare(target, &buffer[middle * elem_size]);
        if (comparison_result < 0)
        {
            left = middle + 1;
        }
        else if (comparison_result > 0)
        {
            right = middle;
        }
        else
        {
            *found_index = middle;
            return DSA_SUCCESS;
        }
    }

    *found_index = size;
    return DSA_SUCCESS;
}
