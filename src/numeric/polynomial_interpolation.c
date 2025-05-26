#include "dsa/numeric/polynomial_interpolation.h"

static double calculate_divided_difference(
    const double *x,
    const double *fx,
    const size_t start,
    const size_t end)
{
    if (start == end)
    {
        return fx[start];
    }

    const double first = calculate_divided_difference(x, fx, start + 1, end);
    const double second = calculate_divided_difference(x, fx, start, end - 1);

    const double numerator = first - second;
    const double denominator = x[end] - x[start];

    return numerator / denominator;
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

    for (int i = 0; i < m; i++)
    {
        pz[i] = calculate_divided_difference(x, fx, 0, 0);
        double previous = 1;

        for (int j = 0; j < n - 1; j++)
        {
            const double divided_difference = calculate_divided_difference(x, fx, 0, j + 1);
            previous *= (z[i] - x[j]);
            pz[i] += (divided_difference * previous);
        }
    }

    return true;
}
