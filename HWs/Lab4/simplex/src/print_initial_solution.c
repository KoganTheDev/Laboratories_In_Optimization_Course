// print_initial_solution.c

#include <stdio.h>
#include "simplex.h"

void print_initial_solution()
{

  int i;

  printf("\nInitial basis:\n");
  for(i=0; i < m; i++)
    printf(" %d ", Initial_basis[i]);
  printf("\n");

  printf("\nBasic Solution:\n");
  for(i=0; i < m; i++)
    printf(" X%d = %lf ", Initial_basis[i], Initial_BIb[i]);
  printf("\n");

} // print_initial_solution
