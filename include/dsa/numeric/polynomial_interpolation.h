#pragma once

#include <stdbool.h>
#include <stddef.h>

bool dsa_interpolate(
    const double *x,
    const double *fx,
    const size_t n,
    double *z,
    double *pz,
    const size_t m);

