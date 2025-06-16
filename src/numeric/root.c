#include "dsa/numeric/root.h"

#include <math.h>

dsa_root_status dsa_find_root_newton(
    double (*f)(double x),
    double (*g)(double x),
    double *x,
    size_t *n,
    const double delta)
{
    if (!f || !g || !x || !n || *n < 2 || delta <= 0.0)
    {
        return DSA_ROOT_INVALID_ARGUMENT;
    }

    static const double epsilon = 1e-12;

    size_t index = 0;
    while (index + 1 < *n)
    {
        const double fx = f(x[index]);
        const double gx = g(x[index]);

        if (fabs(gx) < epsilon)
        {
            return DSA_ROOT_NUMERICAL_ERROR;
        }

        x[index + 1] = x[index] - (fx / gx);

        if (!isfinite(x[index + 1]))
        {
            return DSA_ROOT_NUMERICAL_ERROR;
        }

        if (fabs(x[index + 1] - x[index]) < delta)
        {
            *n = index + 2;
            return DSA_ROOT_SUCCESS;
        }

        ++index;
    }

    *n = index + 1;
    return DSA_ROOT_MAX_ITERATIONS;
}
