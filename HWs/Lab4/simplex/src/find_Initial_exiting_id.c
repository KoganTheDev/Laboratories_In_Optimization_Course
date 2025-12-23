// find_exiting_id.c

#include <stdio.h>
#include "simplex.h"

// Assuming y = B-1D, x = B-1b
int find_Initial_exiting_id(double y[][N], double x[], int enter_id, int 
n, int 
m)
{

  int i,j,temp_min_index, init_flag, q;
  double temp_min, temp;

  for(i=0; i < Initial_n; i++)
    if (Initial_d[i] == enter_id)
        q = i;

  init_flag = 0;
  for(i=0; i < m; i++)
  {
   printf("y[%d][%d] = %lf, x[%d] = %lf %lf\n", i,q, y[i][q],i, x[i]);
   printf("init_flag = %d\n", init_flag);
   if (y[i][q] > 0.0)
   {
    temp = x[i]/y[i][q];
    printf("i = %d, temp = %lf\n", i, temp);
    if (init_flag == 0)
    {
     temp_min = temp;
     temp_min_index = i;
     init_flag = 1;
    } // if 
    else
      if (temp < temp_min)
      {
       temp_min = temp;
       temp_min_index = i;

      } // if 
  
   } // if
    printf("temp_min_index  = %d, temp_min  = %lf\n", temp_min_index , 
                                     temp_min );
  
  } // for
  
return temp_min_index;

} // find_exiting_id
