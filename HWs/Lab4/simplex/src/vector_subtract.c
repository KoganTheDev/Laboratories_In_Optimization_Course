// vector_subtract.c 

void vector_subtract(double result_v[], double v1[], double v2[], int n)
{

  int i;

  for(i=0; i < n; i++)
   result_v[i] = v1[i] - v2[i];

} // vector_subtract
