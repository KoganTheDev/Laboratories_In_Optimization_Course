// find_exiting_id.c

#include <stdio.h>
#include <stdlib.h>

#include "simplex.h"

// Assuming y = B-1D, x = B-1b
int find_exiting_id(double y[][N], double x[], int enter_id, 
int n, int m)
{

  int i,j,temp_min_index, init_flag, q, unbounded_flag;
  double temp_min, temp;
 

  for(i=0; i < n; i++)
    if (d[i] == enter_id)
        q = i;
// CHANGE
  init_flag = 0;
// END OF CHANGE

  unbounded_flag = 1;
  for(i=0; i < m; i++)
  {
   printf("y[%d][%d] = %lf, x[%d] = %lf %lf\n", i,q, y[i][q],i, x[i]);
   printf("init_flag = %d\n", init_flag);
   if (y[i][q] > 0.0)
   {
// CHANGE
   unbounded_flag = 0;
// END OF CHANGE

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
 
    printf("2: i = %d\n", i);
  
   } // if

  } // for

  printf("unbounded flag = %d\n", unbounded_flag);

// CHANGE
  if( unbounded_flag == 1)
  {
   fprintf(stderr, "Unbounded linear program!\n");
   exit(0);
  } // if
// END OF CHANGE

    printf("temp_min_index  = %d, temp_min  = %lf\n", temp_min_index , 
                                     temp_min ); 
  
return temp_min_index;

} // find_exiting_id
