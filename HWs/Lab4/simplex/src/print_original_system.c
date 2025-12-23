//  print_original_system.c


#include <stdio.h>
#include "simplex.h"


void print_original_system()
{
 int i, j;

 printf("Original System:\n");

 for(i=0; i < m; i++)
 {

   for(j=0; j < n; j++)
     printf("%10.3lf", A[i][j]);
   printf("\n");
 } /* for */

} /* print_original_system */



