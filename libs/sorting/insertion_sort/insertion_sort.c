#include "insertion_sort.h"

#include <stdlib.h>
#include <string.h>

int dsa_issort(
    void* data,
    const size_t size,
    const size_t esize,
    int (*compare)(const void* key1, const void* key2))
{
    if (!data || !compare)
    {
        return -1;
    }

    char* arr = data;

    // Allocate storage for the key element.
    void* key = malloc(esize);

    if (!key)
    {
        return -1;
    }

    // Repeatedly insert a key element among the sorted elements.
    for (size_t j = 1; j < size; j++)
    {
        memcpy(key, &arr[j * esize], esize);

        ptrdiff_t i = (ptrdiff_t) j - 1;

        // Determine the position at which to insert the key element.
        while (i >= 0 && compare(&arr[(size_t) i * esize], key) > 0)
        {
            void* source = &arr[(size_t) i * esize];
            void* dest = &arr[(size_t)(i + 1) * esize];

            // Shift element to the right
            memcpy(dest, source, esize);
            --i;
        }

        // Insert the key at the correct position
        memcpy(&arr[(size_t)(i + 1) * esize], key, esize);
    }

    free(key);
    return 0;
}
