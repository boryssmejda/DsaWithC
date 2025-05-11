#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Computes the coefficients of the best-fit line y = ax + b using least-squares estimation.
 *
 * @param[in] x Pointer to an array of x-coordinates.
 * @param[in] y Pointer to an array of y-coordinates.
 * @param[in] size Number of points (must be at least 2).
 * @param[out] a Pointer to where the slope of the best-fit line will be stored.
 * @param[out] b Pointer to where the intercept of the best-fit line will be stored.
 *
 * @return true if the coefficients were computed successfully;
 *      false if any input pointers are nullptr, if size < 2,
 *      or if the computation fails due to a degenerate dataset (e.g., all x values equal).
 *
 * @pre x, y, a, and b must be non-nullptr. size must be >= 2.
 * @post If true is returned, *a and *b contain the slope and intercept of the regression line.
 *
 * @complexity Time complexity: O(n), where n is the number of points used in determining a and b.
 */

bool dsa_lsqe(const double *x, const double *y, const size_t size, double *a, double *b);
