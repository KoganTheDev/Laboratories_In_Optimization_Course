// print_simplex_params.c

#include <stdio.h>
#include <stdlib.h>

#include "simplex.h"

void print_simplex_params(double A[][N],  double A_aux[][N],
double c[], double b[], int n,
int m, double B[][N], double BID[][N],
double D[][N],  int basis[], int d[], double cb[], double cd[])
{
  int i, j;
  static int count = 0;

  printf(" m = %d, n = %d\n", m, n);

  printf("A:\n");
  for(i=0; i < m; i++)
   {
     for(j=0; j < n; j++)  
       printf(" %lf ", A[i][j]);      
     printf("\n");
   } // for


  printf("c:\n");
  for(i=0; i < n; i++)
     printf(" %lf ", c[i]);
  printf("\n");
  

  printf("b:\n");
  for(i=0; i < m; i++)
     printf(" %lf ", b[i]);
  printf("\n");
  


  printf("A_aux:\n");
  for(i=0; i < m; i++)
   {
     for(j=0; j < n; j++)  
       printf(" %lf ", A_aux[i][j]);      
     printf("\n");
   } // for
  



  printf("B:\n");
  for(i=0; i < m; i++)
   {
     for(j=0; j < m; j++)  
       printf(" %lf ", B[i][j]);      
     printf("\n");
   } // for

  printf("basis:\n");
  for(i=0; i < m; i++)
     printf(" %d ", basis[i]);
  printf("\n");
 
  count++;


  if (count >= 8)
    exit(0);

} // print_simplex_params
