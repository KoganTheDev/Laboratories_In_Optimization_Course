// erase_epsilons_vector.c


#include "simplex.h"
#include <math.h>

void erase_epsilons_vector(double darray[], int n)
{
  int i;

  for(i=0; i < n; i++)
    if ( fabs(darray[i]) < epsilon )
        darray[i] = 0.0;


} // erase_epsilons_vector
