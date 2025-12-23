// Initial_set_d.c

#include "simplex.h"

void Initial_set_d()
{
 
 int i, j, pos, flag;

 for(i=0; i < m; i++)
   Initial_d[i] = Initial_basis[i];

 pos = m;
 for(i=0; i< Initial_n; i++)
 {
  flag = 1;
  for(j=0; (j < m) && (flag == 1); j++)
   if ( i == Initial_basis[j])
     flag =0;
  if (flag == 1)
    Initial_d[pos++] = i;
 } // for 



} // Initial_set_d
