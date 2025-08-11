#pragma once

#include "dsa/common/error_codes.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif


dsa_error_code dsa_all_of(
    const void* data,
    const size_t size,
    const size_t esize,
    bool (*compare)(const void* arg),
    bool* output_result);


size_t dsa_all_of_ctx(
    const void* data,
    const size_t size,
    const size_t esize,
    bool (*compare)(const void* arg, const void* ctx),
    const void* ctx,
    dsa_error_code* code);

#ifdef __cplusplus
}
#endif
