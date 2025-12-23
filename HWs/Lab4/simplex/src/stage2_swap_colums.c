// Initial_swap_colums.c

#include "simplex.h"

void stage2_swap_colums(int i, int j)
{
  int k;
  double temp;



  for(k=0; k < m; k++)
  {
     A_aux[k][i] = A[k][j];
     A_aux[k][j] = A[k][i];
  } // for
  

} // swap_colums
