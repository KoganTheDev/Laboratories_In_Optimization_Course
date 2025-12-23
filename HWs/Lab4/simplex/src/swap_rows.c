// swap_rows.c

#include "simplex.h"

void swap_rows(double W[][N], int n, int m1, int m2)
{
  int i;
  double temp;

  for(i=0; i <= 2*n; i++)
  {
    temp = W[m1][i];
    W[m1][i] = W[m2][i];
    W[m2][i] = temp;

  } /* for */

} /* swap_rows */


