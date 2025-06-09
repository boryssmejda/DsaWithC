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
 * @param[in]  x      Array of known x-values (size n).
 * @param[in]  fx     Array of known function values (size n).
 * @param[out] coeffs Output array of divided difference coefficients (size n).
 * @param[in]  n      Number of data points.
 * @return true if successful, false if inputs are invalid or x values are not distinct.
 */
bool dsa_interpolation_find_newton_coefficients(
    const double * restrict x,
    const double * restrict fx,
    double * restrict coeffs,
    const size_t n);


/**
 * @brief Evaluates a Newton interpolating polynomial at specified points.
 *
 * @param[in]  x       Array of base x-values used to compute coefficients (size n).
 * @param[in]  coeffs  Array of Newton coefficients (size n).
 * @param[in]  n       Number of coefficients (data points).
 * @param[in]  z       Array of x-values where the polynomial should be evaluated (size m).
 * @param[out] pz      Output array for computed values at z (size m).
 * @param[in]  m       Number of evaluation points.
 * @return true if successful, false otherwise (e.g., invalid parameters).
 */
bool dsa_interpolation_evaluate_newton_polynomial(
    const double * restrict x,
    const double * restrict coefficients,
    const size_t coefficientsSize,
    const double * restrict z,
    double * restrict pz,
    const size_t pzSize);

#ifdef __cplusplus
} // extern "C"
#endif
