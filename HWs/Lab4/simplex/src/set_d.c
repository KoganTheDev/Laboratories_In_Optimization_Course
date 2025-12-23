// set_d.c

#include "simplex.h"

void set_d()
{
 
 int i, j, pos, flag;

 for(i=0; i < m; i++)
   d[i] = basis[i];

 pos = m;
 for(i=0; i< n; i++)
 {
  flag = 1;
  for(j=0; (j < m) && (flag == 1); j++)
   if ( i == basis[j])
     flag =0;
  if (flag == 1)
    d[pos++] = i;
 } // for 



} // set_d
