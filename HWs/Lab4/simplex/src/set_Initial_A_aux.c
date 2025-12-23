// Initial_swap_colums.c

#include "simplex.h"

void set_Initial_A_aux()
{

  int i, j, k;


  for(i=0; i < Initial_n; i++)
  {
    k = Initial_d[i];
    for(j=0; j < m; j++)
    {
     Initial_A_aux[j][i] = Initial_A[j][k];
    } // for 2
  } // for1
 
  

} // swap_colums
