#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief  Computes the root of f to which Newton’s method
 * converges given an initial iteration point.
 *
 * Computes the root of f to which Newton’s method converges
 * given an initial iteration point. This point is specified in x[0].
 * The derivative of f is specified in g. The argument n is the maximum
 * number of iterations to perform. The argument delta is the difference
 * between successive approximations at which to stop iterating.
 * Upon return, successive values of x calculated during the
 * iteration process are returned in the x array.
 * Upon return, n contains the number of values in array x.
 * It is the responsibility of the caller to manage the storage associated with x.
 *
 * @param[in] f
 * @param[in] g Derivative of @p f
 * @param[in,out] x Solutions at steps
 * @param[in,out] n Maximum numbers of iterations to perform.
 * @param[in] delta Difference between successive approximations at which to stop iterating.
 *
 * @return true if a root is found, false otherwise.
 *
 * @complexity Time complexity: O(n), where n is the maximum number
 * of iterations the caller wishes to perform.
 */

bool root(
    double (*f)(double x),
    double (*g)(double x),
    double *x,
    size_t *n,
    const double delta);
