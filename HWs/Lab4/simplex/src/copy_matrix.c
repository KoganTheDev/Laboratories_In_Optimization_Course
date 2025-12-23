//  copy_matrix.c  

#include "simplex.h"

void copy_matrix(double Dest[][N], double Source[][N], int n, int m)
{
 int i, j;

  for(i=0; i < m; i++)
   for(j=0; j < n; j++)
      Dest[i][j] = Source[i][j];


} // copy_matrix
