// find_min_value.c

#include "simplex.h"


double find_min_value(double rd[], int n)
{
// Assumptions: d[i] is original index, rd orderred by i=0,.., n-1 
//                                                  d[0] ... d[n-1]

  int most_index, i;
  double temp_value;

  most_index = d[0];
  temp_value = rd[0];
  for(i=0; i < n; i++)
    if ( rd[i] <  temp_value)
     {
       most_index = d[i];
       temp_value = rd[i];
     } // if

 return temp_value;
} // find_min_value
