// Initial_swap_colums.c

#include "simplex.h"

void Initial_swap_colums(int i, int j)
{
  int k;
  double temp;



  for(k=0; k < m; k++)
  {
     Initial_A_aux[k][i] = Initial_A[k][j];
     Initial_A_aux[k][j] = Initial_A[k][i];
  } // for
  

} // swap_colums
