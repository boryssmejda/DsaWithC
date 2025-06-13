#pragma once

#include "dsa/common/error_codes.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef void (*dsa_operation_no_context)(void* elem);
typedef void (*dsa_operation_with_context)(void* elem, void* ctx);

dsa_error_code dsa_for_each(void* arr, const size_t count, const size_t elem_size, dsa_operation_no_context operation);
dsa_error_code dsa_for_each_ctx(void* arr, const size_t count, const size_t elem_size, dsa_operation_with_context operation, void* ctx);

#ifdef __cplusplus
}
#endif
