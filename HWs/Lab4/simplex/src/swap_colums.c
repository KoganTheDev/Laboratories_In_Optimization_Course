// swap_colums.c

#include "simplex.h"

void swap_colums(double A[][N], int i, int j, int m, int n)
{
  int k;
  double temp;

  for(k=0; k < m; k++)
  {
     temp = A[k][i];
     A[k][i] = A[k][j];
     A[k][j] = temp;
  } // for
  

} // swap_colums
