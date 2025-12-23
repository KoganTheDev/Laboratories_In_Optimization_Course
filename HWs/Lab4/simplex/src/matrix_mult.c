// matrix_mult.c

#include "simplex.h"

void matrix_mult(double C[][N], double A[][N], double B[][N], int n, 
int m, int p)
{
  int i, j, k;
  double sum;

 for(i=0; i <n; i++)
   for(j=0; j <p; j++)
   {
       sum = 0.0;
       for(k=0; k <m; k++)
          sum = sum + A[i][k] * B[k][j];
     C[i][j] = sum; 
   } // for

} // matrix_mult
  
