#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>

/**
 * @brief Status codes returned by root-finding functions.
 *
 * These codes indicate the outcome of the root-finding process.
 */
typedef enum
{
    /** The method successfully converged to a root within the given tolerance. */
    DSA_ROOT_SUCCESS = 0,

    /** The method did not converge within the allowed number of iterations.
     *  The values in the output array @p x are still valid and show the iteration path.
     */
    DSA_ROOT_MAX_ITERATIONS,

    /** Invalid input was provided (e.g., null pointer, delta <= 0, or *n < 2). */
    DSA_ROOT_INVALID_ARGUMENT,

    /** A numerical error occurred (e.g., division by near-zero derivative, or NaN/Inf encountered). */
    DSA_ROOT_NUMERICAL_ERROR
} dsa_root_status;

/**
 * @brief Finds a root of the function @p f using Newton's method.
 *
 * Uses Newton's method to approximate a root of the function @p f,
 * starting from the initial guess stored in @p x[0]. The derivative
 * of @p f must be provided in @p g.
 *
 * The caller must allocate an array @p x of at least @p *n elements.
 * The function updates this array with successive approximations.
 * Iteration stops either when the difference between successive approximations
 * is less than @p delta, or when @p *n steps have been performed.
 *
 * On successful completion, @p x will contain the steps of the iteration
 * and @p *n will be updated to reflect the number of steps taken.
 *
 * @param[in] f Function whose root is to be found.
 * @param[in] g Derivative of @p f.
 * @param[in,out] x Array where x[0] is the initial guess; updated with iteration values.
 * @param[in,out] n Array of at least @p *n elements.
 *              @p x[0] must contain the initial guess.
 *              On output, contains the sequence of approximations.
 * @param[in] delta Threshold to stop when |x[i+1] - x[i]| < delta.
 *
 * @return A value from the #dsa_root_status enum:
 *         - ::DSA_ROOT_SUCCESS if the method converged within the tolerance.
 *         - ::DSA_ROOT_MAX_ITERATIONS if the method did not converge within the allowed steps.
 *         - ::DSA_ROOT_INVALID_ARGUMENT if inputs were invalid (e.g., null pointers or delta <= 0).
 *         - ::DSA_ROOT_NUMERICAL_ERROR if NaN or Inf was encountered during iteration.
 *
 * @note The caller must ensure that the array @p x has at least @p *n elements allocated.
 *
 * @complexity O(n), where n is the maximum number of iterations.
 */
dsa_root_status dsa_find_root_newton(
    double (*f)(double x),
    double (*g)(double x),
    double *x,
    size_t *n,
    const double delta);

#ifdef __cplusplus
} // extern "C"
#endif
