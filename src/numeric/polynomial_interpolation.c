#include "dsa/numeric/polynomial_interpolation.h"

#include <math.h>

// todo - obejrzyj o restrict keyword

static bool calculate_divided_difference(
    const double *x,
    const double *fx,
    const size_t start,
    const size_t end,
    double* result)
{
    if (!result)
    {
        return false;
    }

    if (start == end)
    {
        *result = fx[start];
        return true;
    }

    double first = 0.0;
    double second = 0.0;

    const bool isFirstCorrect = calculate_divided_difference(x, fx, start + 1, end, &first);
    const bool isSecondCorrect = calculate_divided_difference(x, fx, start, end - 1, &second);

    if (!isFirstCorrect || !isSecondCorrect)
    {
        return false;
    }

    const double numerator = first - second;
    const double denominator = x[end] - x[start];

    static const double epsilon = 1e-6;
    if (fabs(denominator) < epsilon)
    {
        return false;
    }

    *result = numerator / denominator;
    return true;
}

bool dsa_interpolate(
    const double * restrict x,
    const double * restrict fx,
    const size_t n,
    const double *restrict z,
    double * restrict pz,
    const size_t m)
{
    if (!x || !fx || n < 2 || !z || !pz || m == 0)
    {
        return false;
    }

    double first_term_value = 0.0;
    const bool is_first_term_valid = calculate_divided_difference(x, fx, 0, 0, &first_term_value);

    if (!is_first_term_valid)
    {
        return false;
    }

    for (size_t i = 0; i < m; i++)
    {
        pz[i] = first_term_value;
        double product_term = 1;

        for (size_t j = 0; j < n - 1; j++)
        {
            double divided_difference = 0.0;
            const bool is_valid = calculate_divided_difference(x, fx, 0, j + 1, &divided_difference);
            if (!is_valid)
            {
                return false;
            }

            product_term *= (z[i] - x[j]);
            pz[i] += (divided_difference * product_term);
        }
    }

    return true;
}
