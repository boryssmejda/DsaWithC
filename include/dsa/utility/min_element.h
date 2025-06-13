#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

size_t dsa_min_element(const void* arr, const size_t count, const size_t elem_size, int (*compare)(const void* a, const void* b));

#ifdef __cplusplus
}
#endif
