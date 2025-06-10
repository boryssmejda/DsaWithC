#include "dsa/numeric/polynomial_interpolation.h"

#include <math.h>

bool dsa_interpolation_find_newton_coefficients(
    const double * restrict x,
    const double * restrict fx,
    double * restrict coefficients,
    size_t n)
{
    if (!x || !fx || !coefficients || n < 1)
    {
        return false;
    }

    for (size_t i = 0; i < n; i++)
    {
        coefficients[i] = fx[i];
    }

    static const double epsilon = 1e-6;

    for (size_t start = 1; start <= n; start++)
    {
        for (size_t end = n - 1; end >= start; end--)
        {
            const double numerator = (coefficients[end] - coefficients[end - 1]);
            const double denominator = (x[end] - x[end - start]);
            if (fabs(denominator) < epsilon)
            {
                return false;
            }
            coefficients[end] = numerator / denominator;
        }
    }

    return true;
}

bool dsa_interpolation_evaluate_newton_polynomial(
    const double * restrict x,
    const double * restrict coefficients,
    const size_t n,
    const double * restrict z,
    double * restrict pz,
    const size_t m)
{
    if (!x || !coefficients || n < 1 || !z || !pz || m == 0)
    {
        return false;
    }

    for (size_t i = 0; i < m; i++)
    {
        pz[i] = coefficients[0];
        double product_term = 1.0;

        for (size_t j = 0; j < n - 1; j++)
        {
            product_term *= (z[i] - x[j]);
            pz[i] += (coefficients[j + 1] * product_term);
        }
    }

    return true;
}
