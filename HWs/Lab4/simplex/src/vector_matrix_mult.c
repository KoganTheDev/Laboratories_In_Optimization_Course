// matrix_vector_mult.c

#include "simplex.h"

void vector_matrix_mult(double c[], double b[], double A[][N],   int n, 
int m)
{
  int i, j, k;
  double sum;

 for(i=0; i <m; i++)
   {
       sum = 0.0;
       for(k=0; k <n; k++)
               sum = sum + A[k][i] * b[k];
     c[i] = sum; 
   } // for

} // matrix_vector_mult
  
