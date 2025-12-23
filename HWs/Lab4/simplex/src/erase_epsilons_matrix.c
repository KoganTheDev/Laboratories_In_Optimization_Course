// erase_epsilons_matrix.c


#include "simplex.h"
#include <math.h>

void erase_epsilons_matrix(double dmat[][N], int m, int n)
{
  int i, j;

  for(i=0; i < m; i++)
    for(j=0; j < n; j++)
       if ( fabs(dmat[i][j]) < epsilon )
           dmat[i][j] = 0.0;


} // erase_epsilons_matrix
