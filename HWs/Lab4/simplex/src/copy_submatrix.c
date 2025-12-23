// copy_submatrix.c

#include "simplex.h"

void copy_submatrix(double Dest[][N], double Source[][N],  int istart, 
   int depth, int jstart, int length)
{
  int i, j, k;

  for(i=istart; i < depth; i++)
    for(j=jstart; j < (jstart+length); j++)
      Dest[i-istart][j-jstart] = Source[i][j];


} // copy_submatrix 
