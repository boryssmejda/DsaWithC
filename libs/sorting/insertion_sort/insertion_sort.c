#include "insertion_sort.h"

#include <stdlib.h>
#include <string.h>

int dsa_issort(
    void* data,
    const size_t size,
    const size_t esize,
    int (*compare)(const void* key1, const void* key2))
{
    if (!data || !compare || esize == 0)
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
    for (size_t current_position = 1; current_position < size; current_position++)
    {
        memcpy(key, &arr[current_position * esize], esize);

        ptrdiff_t insert_position = (ptrdiff_t) current_position - 1;

        // Determine the position at which to insert the key element.
        while (insert_position >= 0 && compare(&arr[(size_t) insert_position * esize], key) > 0)
        {
            void* source = &arr[(size_t) insert_position * esize];
            void* destination = &arr[(size_t)(insert_position + 1) * esize];

            // Shift element to the right
            memcpy(destination, source, esize);
            --insert_position;
        }

        // Insert the key at the correct position
        memcpy(&arr[(size_t)(insert_position + 1) * esize], key, esize);
    }

    free(key);
    return 0;
}
