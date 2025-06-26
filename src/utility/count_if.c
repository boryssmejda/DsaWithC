#include "dsa/utility/count_if.h"

size_t dsa_count_if(
    const void* data,
    const size_t size,
    const size_t esize,
    bool (*compare)(const void* arg))
{
    size_t count = 0;
    if (!data || size == 0 || esize == 0 || !compare)
    {
        return count;
    }

    for (size_t i = 0; i < size; i++)
    {
        const unsigned char* element = (const unsigned char*)data + esize * i;
        if (compare(element))
        {
            ++count;
        }
    }
    return count;
}

size_t dsa_count_if_ctx(
    const void* data,
    const size_t size,
    const size_t esize,
    bool (*compare)(const void* arg, const void* ctx),
    const void* ctx)
{
    size_t count = 0;
    if (!data || size == 0 || esize == 0 || !compare || !ctx)
    {
        return count;
    }

    for (size_t i = 0; i < size; i++)
    {
        const unsigned char* element = (const unsigned char*)data + esize * i;
        if (compare(element, ctx))
        {
            ++count;
        }
    }
    return count;
}
