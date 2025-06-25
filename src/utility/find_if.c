#include "dsa/utility/find_if.h"

size_t dsa_find_if(
    const void* data,
    const size_t count,
    const size_t esize,
    bool (*compare)(const void* arg))
{
    if (!data || count == 0 || esize == 0 || !compare)
    {
        return count;
    }

    for (int i = 0; i < count; i++)
    {
        const unsigned char* element = data + esize * i;
        if (compare(element))
        {
            return i;
        }
    }
    return count;
}

size_t dsa_find_if_ctx(
    const void* data,
    const size_t count,
    const size_t esize,
    bool (*compare)(const void* arg, const void* ctx),
    const void* ctx)
{
    if (!data || count == 0 || esize == 0 || !compare || !ctx)
    {
        return count;
    }

    for (int i = 0; i < count; i++)
    {
        const unsigned char* element = data + esize * i;
        if (compare(element, ctx))
        {
            return i;
        }
    }
    return count;
}
