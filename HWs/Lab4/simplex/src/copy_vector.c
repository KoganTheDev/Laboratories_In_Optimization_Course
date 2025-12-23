//  copy_vector.c  

#include "simplex.h"

void copy_vector(double Dest[], double Source[],  int n)
{
 int i, j;

  for(i=0; i < n; i++)
      Dest[i] = Source[i];


} // copy_vector
