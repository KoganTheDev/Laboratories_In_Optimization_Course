// compute_cb_cd.c

#include "simplex.h"

void compute_cb_cd()
{
 
  int i;

 

  for(i=0; i < m; i++)
   cb[i] = c[d[i]];
   
  for(i=m; i < n; i++)
   cd[i-m] = c[d[i]];

  printf("d:\n");
  for(i=0; i < n; i++)
   printf(" %d ", d[i]);    
  printf("\n");

  printf("cb:\n");
  for(i=0; i < m; i++)
   printf(" %lf ", cb[i]);    
  printf("\n");

  printf("cd:\n");
  for(i=0; i < n; i++)
   printf(" %lf ", cd[i]);    
  printf("\n");


} // compute_cb_cd()
