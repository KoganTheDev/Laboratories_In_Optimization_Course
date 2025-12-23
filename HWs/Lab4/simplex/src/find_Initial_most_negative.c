// find_most_negative.c

#include "simplex.h"


int find_Initial_most_negative()
{
// Assumptions: d[i] is original index, rd orderred by i=0,.., n-1 
//                                                  d[0] ... d[n-1]

  int most_index, i;
  double temp_value;

  most_index = Initial_d[m];
  temp_value = Initial_rd[0];
  for(i=0; i < (Initial_n - m); i++)
    if ( Initial_rd[i] <  temp_value)
     {
       most_index = Initial_d[m+i];
       temp_value = Initial_rd[i];
     } // if

 return most_index;
} // find_most_negative
