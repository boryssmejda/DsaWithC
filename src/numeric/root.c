#include "dsa/numeric/root.h"

#include <math.h>

bool root_newton(
    double (*f)(double x),
    double (*g)(double x),
    double *x,
    size_t *n,
    const double delta)
{
    if (!f || !g || !x || !n || *n < 2 || delta <= 0.0)
    {
        return false;
    }

    const double epsilon = 1e-12;

    bool isSatisfied = false;
    size_t index = 0;
    while (!isSatisfied && index + 1 < *n)
    {
        const double fx = f(x[index]);
        const double gx = g(x[index]);

        if (fabs(gx) < epsilon)
        {
            return false;
        }

        x[index + 1] = x[index] - (fx / gx);

        if (!isfinite(x[index + 1]))
        {
            return false; // Check for NaN or Inf
        }

        if (fabs(x[index + 1] - x[index]) < delta)
        {
            isSatisfied = true;
        }

        ++index;
    }

    *n = index + 1;

    return isSatisfied;
}
