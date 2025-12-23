//  print_result.c

#include <stdio.h>
#include "simplex.h"



void read_file()
{
  int i, j, k;
  char str[80];

   fgets(str, 80, fp);   // "c:"
   printf("str = %s\n", str);
  for(i=0; i < n; i++)
       fscanf(fp,"%lf", &c[i]);
  for(i=0; i < n; i++)
       printf("c[%d] = %lf\n", i, c[i]);

  fgets(str, 80, fp);   // 
  printf(" str = %s\n", str);
   fgets(str, 80, fp);   // "A:"
  printf("A: str = %s\n", str);

  for(i=0; i < m; i++)
  {
    for(j=0; j < n; j++)
     fscanf(fp, "%lf", &A[i][j]);
  } // for

  for(i=0; i < m; i++)
    {
     for(j=0; j < n; j++)
        printf(" %lf ", A[i][j]);
     printf("\n");
    } // for


  fgets(str, 80, fp);   // 
  printf(" str = %s\n", str);

  fgets(str, 80, fp);   // "b:"
  printf(" b: str = %s\n", str);


  for(i=0; i < m; i++)
       fscanf(fp,"%lf", &b[i]);

  fgets(str, 80, fp);   // 
  fgets(str, 80, fp);   // "epsilon:"
  printf(" str = %s\n", str);
  fscanf(fp, "%lf", &epsilon);
  

  printf("b:\n");
  for(i=0; i < m; i++)
       printf(" %lf ", b[i]);
  printf("\n");

 copy_matrix(A_aux, A, n, m);

} /* read_file */

