//  print_result.c

#include <stdio.h>
#include "simplex.h"


void print_result()
{
 int i, j, k;
 double sum;

 printf("Optimal Basis:\n");
 for(i=0; i < m; i++)
   printf(" %d ", basis[i]);
 printf("/n");
   

 printf("Optimal Solution:\n");
 for(i=0; i < m; i++)
   printf(" X%d = %lf ", basis[i], BIb[i]);
 printf("/n");
   


} /* print_result */
