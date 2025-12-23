// print_solution.c

#include <stdio.h>
#include "simplex.h"

void print_solution()
{

  int i;
  double sum, temp;

  printf("\nbasis:\n");
  for(i=0; i < m; i++)
    printf(" %d ", basis[i]);
  printf("\n");

  printf("\nBasic Solution:\n");
  for(i=0; i < m; i++)
    printf(" X%d = %lf ", basis[i]+1, BIb[i]);
  printf("\n");

  printf("\nSolution value:\n");

  temp = c[basis[0]]* BIb[0];
  sum = temp;
  printf(" %lf * %lf ", c[basis[0]], BIb[0]); 

  for(i=1; i < m; i++)
   {
     temp = c[basis[i]]* BIb[i];
     sum = sum + temp;
     printf(" +  %lf * %lf ", c[basis[i]], BIb[i]); 
     //printf(" +  %lf ", temp); 
   } // for

  printf(" = %lf\n", sum);

} // print_solution
