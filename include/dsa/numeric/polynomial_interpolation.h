#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
    #define restrict
#endif

/**
 * @brief Computes Newton divided difference coefficients for polynomial interpolation.
 *
 * Given arrays of x-values and their corresponding function values,
 * computes the coefficients of the Newton interpolating polynomial
 * using the divided differences method.
 *
 * @param[in]  x           Array of known x-values (size n).
 * @param[in]  fx          Array of known function values (size n).
 * @param[out] coefficients Output array for divided difference coefficients (size n).
 * @param[in]  n           Number of data points.
 *
 * @return true if successful; false if inputs are invalid or x-values are not distinct enough.
 *
 * @note Time complexity: O(n^2) due to nested loops computing divided differences.
 */
bool dsa_interpolation_find_newton_coefficients(
    const double * restrict x,
    const double * restrict fx,
    double * restrict coefficients,
    const size_t n);


/**
 * @brief Evaluates a Newton interpolating polynomial at specified points.
 *
 * Given the base x-values and Newton polynomial coefficients,
 * evaluates the polynomial at each point in the z array using Horner's-like scheme.
 *
 * @param[in]  x              Array of base x-values used to compute coefficients (size n).
 * @param[in]  coefficients   Array of Newton coefficients (size n).
 * @param[in]  n              Number of coefficients (and size of x array).
 * @param[in]  z              Array of x-values where the polynomial should be evaluated (size m).
 * @param[out] pz             Output array for computed polynomial values at points in z (size m).
 * @param[in]  m              Number of evaluation points.
 *
 * @return true if successful; false if any input parameters are invalid.
 *
 * @note Time complexity: O(m * n) where @p m is the number of evaluation points,
 *       and @p n is the degree + 1 of the interpolating polynomial.
 */
bool dsa_interpolation_evaluate_newton_polynomial(
    const double * restrict x,
    const double * restrict coefficients,
    const size_t n,
    const double * restrict z,
    double * restrict pz,
    const size_t m);

#ifdef __cplusplus
} // extern "C"
#endif
