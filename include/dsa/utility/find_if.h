#pragma once

#include <stdbool.h>
#include <stddef.h>

size_t dsa_find_if(
    const void* data,
    const size_t count,
    const size_t esize,
    bool (*compare)(const void* arg));

size_t dsa_find_if_ctx(
    const void* data,
    const size_t count,
    const size_t esize,
    bool (*compare)(const void* arg, const void* ctx),
    const void* ctx);
