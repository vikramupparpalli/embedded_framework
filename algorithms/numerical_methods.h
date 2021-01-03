/*!
 * @file
 * @brief Numerical Methods
 *
 * Absolutely Non-Confidential - No rights reserved.
 */

#ifndef NUMERICAL_METHODS_H
#define NUMERICAL_METHODS_H

#include "cltypes.h"

int numerical_methods_interpol(const uint64_t *x, const uint64_t *fx, uint16_t n, uint64_t *z, uint64_t *pz, uint16_t m);

void numerical_methods_lsqe(const uint64_t *x, const uint64_t *y, uint16_t n, uint64_t *b1, uint64_t *b0);

int numerical_methods_root(uint64_t (*f)(uint64_t x), uint64_t (*g)(uint64_t x), uint64_t *x, int *n, uint64_t delta);

#endif
