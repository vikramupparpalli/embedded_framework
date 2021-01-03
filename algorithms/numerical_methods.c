/*!
 * @file
 * @brief
 *
 * Absolutely Non-Confidential - No rights reserved.
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "numerical_methods.h"

int numerical_methods_root(uint64_t (*f)(uint64_t x), uint64_t (*g)(uint64_t x), uint64_t *x, int *n, uint64_t delta)
{
   uint16_t satisfied, i;

   i = 0;
   satisfied = 0;

   while(!satisfied && i + 1 < *n)
   {
      x[i + 1] = x[i] - (f(x[i]) / g(x[i]));

      if(fabs(x[i + 1] - x[i]) < delta)
         satisfied = 1;
      i++;
   }

   if(i == 0)
      *n = 1;
   else
      *n = i + 1;

   if(satisfied)
      return 0;
   else
      return -1;

}

void numerical_methods_lsqe(const uint64_t *x, const uint64_t *y, uint16_t n, uint64_t *b1, uint64_t *b0)
{
   uint64_t sumx, sumy, sumx2, sumxy;
   uint16_t i;

   sumx = 0.0;
   sumy = 0.0;
   sumx2 = 0.0;
   sumxy = 0.0;

   for(i = 0; i < n; i++)
   {
      sumx = sumx + x[i];
      sumy = sumy + y[i];
      sumx2 = sumx2 + pow(x[i], 2.0);
      sumxy = sumxy + (x[i] * y[i]);
   }

   *b1 = (sumxy - ((sumx * sumy) / (uint64_t)n)) / (sumx2 - (pow(sumx, 2.0) / (uint64_t)n));
   *b0 = (sumy - ((*b1) * sumx)) / (uint64_t)n;

   return;
}

int numerical_methods_interpol(const uint64_t *x, const uint64_t *fx, uint16_t n, uint64_t *z, uint64_t *pz, uint16_t m)
{
   uint64_t term, *table, *coeff;
   uint16_t i, j, k;

   if((table = (uint64_t *)malloc(sizeof(uint64_t) * n)) == NULL)
      return -1;

   if((coeff = (uint64_t *)malloc(sizeof(uint64_t) * n)) == NULL)
   {
      free(table);
      return -1;
   }

   memcpy(table, fx, sizeof(uint64_t) * n);

   coeff[0] = table[0];
   for(k = 1; k < n; k++)
   {
      for(i = 0; i < n - k; i++)
      {
         j = i + k;
         table[i] = (table[i + 1] - table[i]) / (x[j] - x[i]);
      }
      coeff[k] = table[0];
   }

   free(table);
   for(k = 0; k < m; k++)
   {
      pz[k] = coeff[0];
      for(j = 1; j < n; j++)
      {
         term = coeff[j];
         for(i = 0; i < j; i++)
            term = term * (z[k] - x[i]);
         pz[k] = pz[k] + term;
      }
   }

   free(coeff);
   return 0;
}
