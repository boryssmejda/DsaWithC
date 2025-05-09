#include "dsa/search/binary_search.h"

size_t dsa_binary_search(
    const void *sorted,
    const void *target,
    const size_t size,
    const size_t esize,
    int (*compare)(const void *key1, const void *key2))
{
    if (!sorted || !target || size == 0 || esize == 0 || !compare)
    {
        return size;
    }

    size_t left = 0;
    size_t right = size;
    const char* sortedArr = sorted;

    while (left < right)
    {
        const size_t middle = left + (right - left) / 2;

        switch(compare(&sortedArr[middle * esize], target))
        {
            case -1:
                left = middle + 1;
                break;
            case 1:
                right = middle;
                break;
            case 0:
                return middle;
        }
    }

    return size;
}
