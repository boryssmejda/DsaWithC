#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @enum dsa_error_code
 * @brief Error codes returned by DSA functions.
 */
typedef enum
{
    /**
     * @brief Operation completed successfully.
     */
    DSA_SUCCESS = 0,

    /**
     * @brief The input provided to a function was invalid.
     */
    DSA_INVALID_INPUT = 1,

    /**
     * @brief Memory allocation failed during operation.
     */
    DSA_ALLOC_FAILURE = 2
} dsa_error_code_t;

/**
 * @brief Returns a human-readable string for a given error code.
 *
 * @param code The error code to describe.
 * @return A constant, statically-allocated string describing the error.
 *         The returned string is not allocated on the heap and must not be freed by the caller.
 */
const char* dsa_strerror(const dsa_error_code_t code);

#ifdef __cplusplus
}
#endif
