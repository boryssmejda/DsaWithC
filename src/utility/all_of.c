#include "dsa/utility/all_of.h"

#include "dsa/utility/find_if_not.h"

dsa_error_code dsa_all_of(
    const void* data,
    const size_t size,
    const size_t esize,
    bool (*compare)(const void* arg),
    bool* const output_result)
{
    if (!data && size > 0)
    {
        return DSA_INVALID_INPUT;
    }

    if (esize == 0 || !compare || !output_result)
    {
        return DSA_INVALID_INPUT;
    }

    *output_result = (dsa_find_if_not(data, size, esize, compare) == size);
    return DSA_SUCCESS;
}


size_t dsa_all_of_ctx(
    const void* data,
    const size_t size,
    const size_t esize,
    bool (*compare)(const void* arg, const void* ctx),
    const void* ctx,
    bool* output_result)
{
    if (!data && size > 0)
    {
        return DSA_INVALID_INPUT;
    }

    if (esize == 0 || !compare || !ctx || !output_result)
    {
        return DSA_INVALID_INPUT;
    }
}