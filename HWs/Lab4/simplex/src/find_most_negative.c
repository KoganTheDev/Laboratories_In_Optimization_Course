// find_most_negative.c

#include "simplex.h"


int find_most_negative()
{
// Assumptions: d[i] is original index, rd orderred by i=0,.., n-1 
//                                                  d[0] ... d[n-1]

  int most_index, i;
  double temp_value;

  most_index = d[m];
  temp_value = rd[0];
  for(i=0; i < (n - m); i++)
    if ( rd[i] <  temp_value)
     {
       most_index = d[m+i];
       temp_value = rd[i];
     } // if

 return most_index;
} // find_most_negative
