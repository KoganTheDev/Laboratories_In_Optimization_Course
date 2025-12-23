// swap_colums.c

#include "simplex.h"

void set_A_aux()
{

  int i, j, k;


  for(i=0; i < n; i++)
  {
    k = d[i];
    for(j=0; j < m; j++)
    {
     A_aux[j][i] = A[j][k];
    } // for 2
  } // for1
 
  

} // swap_colums
