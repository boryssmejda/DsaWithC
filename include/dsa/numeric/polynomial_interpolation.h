#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
    #define restrict
#endif


/**
 * @brief Interpolates values of a function using Newton polynomial interpolation.
 *
 * Determines the value of a function at specified points using polynomial interpolation.
 * Known data points are provided in arrays @p x (input values) and
 * @p fx (corresponding function values). The function computes interpolated values
 * at the points specified in @p z and stores the results in @p pz.
 *
 * It is the caller's responsibility to ensure that:
 * - All arrays (@p x, @p fx, @p z, @p pz) are allocated with sufficient size.
 * - The values in @p x are distinct (i.e., all @p x[i] are different).
 *
 * @param[in]  x     Array of known x-values (size n).
 * @param[in]  fx    Array of known function values corresponding to x (size n).
 * @param[in]  n     Number of known data points.
 * @param[in]  z     Array of x-values at which to interpolate (size m).
 * @param[out] pz    Output array for interpolated values at points in z (size m).
 * @param[in]  m     Number of points to interpolate.
 *
 * @pre
 * - `x`, `fx`, `z`, and `pz` pointers must not be `nullptr` if their corresponding sizes (`n` or `m`) are greater than 0.
 * - `n` (number of known data points) must be at least 1.
 * - The values in `x` must be distinct.
 * - Arrays `x`, `fx`, `z`, and `pz` must be allocated with sufficient size (`n` for `x` and `fx`, `m` for `z` and `pz`).
 *
 * @post
 * - If the function returns `true`, the `pz` array will contain the interpolated values corresponding to the points in `z`.
 * - If the function returns `false`, an error occurred (e.g., invalid input parameters or preconditions not met), and the contents of `pz` are undefined.
 * - The input arrays `x`, `fx`, and `z` remain unchanged.
 *
 * @return true if interpolation is successful, false if an error occurs (e.g., invalid input).
 *
 * @note
 * The interpolation uses Newton’s divided difference method.
 * The computed polynomial is not returned explicitly;
 * only the evaluated values at @p z are returned in @p pz.
 *
 * @complexity
 * Time complexity: \f$ O(m \cdot n^2) \f$, where \f$ n \f$ is the number of known data points and
 * \f$ m \f$ is the number of points at which to compute the interpolated values.
 * This includes \f$ O(n^2) \f$ to build the divided differences and \f$ O(n) \f$ for each evaluation at a point in @p z.
 */
bool dsa_interpolate(
    const double * restrict x,
    const double * restrict fx,
    const size_t n,
    const double *restrict z,
    double * restrict pz,
    const size_t m);
