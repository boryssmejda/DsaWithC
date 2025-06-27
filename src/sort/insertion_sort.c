#include "dsa/sort/insertion_sort.h"

#include <stdlib.h>
#include <string.h>

dsa_error_code_t dsa_insertion_sort(
    void* const data,
    const size_t size,
    const size_t elem_size,
    int (*compare)(const void* key1, const void* key2))
{
    if (!data || !compare || elem_size == 0)
    {
        return DSA_INVALID_INPUT;
    }

    char* arr = data;

    // Allocate storage for the key element.
    void* key = malloc(elem_size);

    if (!key)
    {
        return DSA_ALLOC_FAILURE;
    }

    // Repeatedly insert a key element among the sorted elements.
    for (size_t current_position = 1; current_position < size; current_position++)
    {
        memcpy(key, &arr[current_position * elem_size], elem_size);

        ptrdiff_t insert_position = (ptrdiff_t) current_position - 1;

        // Determine the position at which to insert the key element.
        while (insert_position >= 0 && compare(&arr[(size_t) insert_position * elem_size], key) > 0)
        {
            void* source = &arr[(size_t) insert_position * elem_size];
            void* destination = &arr[(size_t)(insert_position + 1) * elem_size];

            // Shift element to the right
            memcpy(destination, source, elem_size);
            --insert_position;
        }

        // Insert the key at the correct position
        memcpy(&arr[(size_t)(insert_position + 1) * elem_size], key, elem_size);
    }

    free(key);
    return DSA_SUCCESS;
}
