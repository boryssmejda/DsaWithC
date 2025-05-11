#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief  Computes the root of f to which Newton’s method
 * converges given an initial iteration point.
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
