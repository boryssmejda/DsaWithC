#include "dsa/numeric/polynomial_interpolation.h"

#include <math.h>

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

    if (fabs(denominator) < 1e-6)
    {
        return false;
    }

    *result = numerator / denominator;
    return true;
}

bool dsa_interpolate(
    const double *x,
    const double *fx,
    const size_t n,
    const double *z,
    double *pz,
    const size_t m)
{
    if (!x || !fx || n < 2 || !z || !pz || m == 0)
    {
        return false;
    }

    double firstTermValue = 0.0;
    const bool isFirstTermValid = calculate_divided_difference(x, fx, 0, 0, &firstTermValue);

    if (!isFirstTermValid)
    {
        return false;
    }

    for (size_t i = 0; i < m; i++)
    {
        pz[i] = firstTermValue;
        double previous = 1;

        for (size_t j = 0; j < n - 1; j++)
        {
            double divided_difference = 0.0;
            const bool isValid = calculate_divided_difference(x, fx, 0, j + 1, &divided_difference);
            if (!isValid)
            {
                return false;
            }

            previous *= (z[i] - x[j]);
            pz[i] += (divided_difference * previous);
        }
    }

    return true;
}
