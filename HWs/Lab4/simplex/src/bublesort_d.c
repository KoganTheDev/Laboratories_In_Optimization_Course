// bublesort.c

#include "simplex.h"

void bublesort_d(int array[], double darr[],  int n)
{
  int i, j, limit, flag, temp;
  double dtemp;

  flag = 1;
  for(i=0;( i < n) && (flag == 1); i++)
  {
    flag = 0;
    limit = n - i - 1;
        for(j = 0;  j < limit; j++)
           if (array[j] > array[j+1])
             {
                 flag = 1;
                 dtemp = darr[j];
                 darr[j] = darr[j+1];
                 darr[j+1] = dtemp;
                 temp = array[j];
                 array[j] = array[j+1];
                 array[j+1] = temp;
             } // if
  } // for

} // bublesort

