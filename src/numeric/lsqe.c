#include "dsa/numeric/lsqe.h"

#include <math.h>

bool dsa_lsqe(const double *x, const double *y, const size_t size, double *a, double *b)
{
    if (!x || !y || size < 2 || !a || !b)
    {
        return false;
    }

    double sumxy = 0.0;
    double sumx = 0.0;
    double sumx2 = 0.0;
    double sumy = 0.0;

    for (size_t i = 0; i < size; i++)
    {
        sumx += x[i];
        sumx2 += (x[i] * x[i]);
        sumxy += (x[i] * y[i]);
        sumy += y[i];
    }

    const double epsilon = 0.0001;
    const double denominator = ((double)size * sumx2 - sumx * sumx);

    if (fabs(denominator) < epsilon)
    {
        return false;
    }

    *a = ((double)size * sumxy - (sumx * sumy)) / denominator;
    *b = (sumy - *a * sumx) / (double)size;

    return true;
}
