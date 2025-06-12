#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum {
    DSA_SUCCESS = 0,
    DSA_INVALID_INPUT = 1,
    DSA_ALLOC_FAILURE = 2
} dsa_error_code;

const char* dsa_strerror(const dsa_error_code code);

#ifdef __cplusplus
}
#endif
