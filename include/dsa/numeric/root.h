#pragma once

#include <stdbool.h>
#include <stddef.h>

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
 * @param[in,out] n Pointer to the number of iterations:
 *                  - On input: max number of iterations allowed.
 *                  - On output: number of iterations actually performed.
 * @param[in] delta Threshold to stop when |x[i+1] - x[i]| < delta.
 *
 * @return true if a root was found within the given tolerance and iterations, false otherwise.
 *
 * @note The caller must ensure that the array @p x has at least @p *n elements allocated.
 *
 * @complexity O(n), where n is the maximum number of iterations.
 */

bool dsa_find_root_newton(
    double (*f)(double x),
    double (*g)(double x),
    double *x,
    size_t *n,
    const double delta);
