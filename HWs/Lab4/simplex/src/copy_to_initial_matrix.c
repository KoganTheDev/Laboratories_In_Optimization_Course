// copy_to_initial_matrix.c

#include "simplex.h"

void copy_to_initial_matrix()
{
  int i, j, k;

  for(i=0; i < m; i++)
    for(j=0; j < n; j++)
      Initial_A[i][j] = Initial_A_aux[i][j] = A[i][j];
//      Initial_A[i][j] = Initial_A_aux[i][j] = A[i][j-m];

  for(i=0; i < m; i++)
    for(j=n; j < n+m; j++)
     if ( i == (j-n) )
        Initial_A[i][j] = Initial_A_aux[i][j] = 1.0;
     else
        Initial_A[i][j] = Initial_A_aux[i][j] = 0.0; 

} // copy_to_initial_matrix
