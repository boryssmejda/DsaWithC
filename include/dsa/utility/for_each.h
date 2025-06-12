#pragma once

#include "dsa/common/error_codes.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

dsa_error_code dsa_for_each(void* arr, const size_t count, const size_t elem_size, void (*operation)(void* arg));

#ifdef __cplusplus
}
#endif
