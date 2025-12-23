// matrix_vector_mult.c

#include "simplex.h"

void matrix_vector_mult(double c[], double A[][N], double b[],  int n, 
int m)
{
  int i, j, k;
  double sum;

 for(i=0; i <n; i++)
   {
       sum = 0.0;
       for(k=0; k <m; k++)
          sum = sum + A[i][k] * b[k];
     c[i] = sum; 
   } // for

} // matrix_vector_mult
  
