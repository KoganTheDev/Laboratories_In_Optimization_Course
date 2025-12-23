// compute_cb_cd.c

#include "simplex.h"

void compute_Initial_cb_Initial_cd()
{
 
  int i;

 

  for(i=0; i < m; i++)
   Initial_cb[i] = Initial_c[Initial_d[i]];
   
  for(i=m; i < Initial_n; i++)
   Initial_cd[i-m] = Initial_c[Initial_d[i]];

  printf("Initial_d:\n");
  for(i=0; i < Initial_n; i++)
   printf(" %d ", Initial_d[i]);    
  printf("\n");

  printf("Initial_cb:\n");
  for(i=0; i < m; i++)
   printf(" %lf ", Initial_cb[i]);    
  printf("\n");

  printf("Initial_cd:\n");
  for(i=0; i < (Initial_n-m); i++)
   printf(" %lf ", Initial_cd[i]);    
  printf("\n");


} // compute_cb_cd()
