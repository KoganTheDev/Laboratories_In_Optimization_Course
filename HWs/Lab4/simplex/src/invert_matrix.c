//  invert_matrix.c  

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <math.h>

#include "simplex.h"

void inv_gaussian(double B[][N], double A[][N], int n)
{
 
  int i, j, k, p, itemp;
  double MaxValue, RelativeValue;
  double temp;

  
  for(i=0; i < n; i++)
    for(j=0; j < n; j++)
      W[i][j] = A[i][j];

   for(i=0; i < n; i++)
    for(j=n; j < 2*n; j++)
      W[i][j] = 0.0;

   for(i=0; i < n; i++)
     W[i][n+i] = 1.0;

   printf("\nBefore loop W: \n");
   for(i=0; i < n; i++)
   {
     for(j=0; j < 2*n; j++)
         printf(" %8.2lf " ,W[i][j]);
    printf("\n");
   } // for


  for (k=0; k < n; k++)
  {
   printf("k = %d\n", k);
    p = k;
    MaxValue = fabs(W[k][k]);
    for(i=k+1; i < n; i++)
     if (fabs(W[i][k]) >  MaxValue)
     {
         p = i;
         MaxValue = fabs(W[i][k]);
     }// if

     printf("\np = %d, k = %d\n", p, k);
 
     if (p != k)
     {
       swap_rows(W, n, k, p);
     } // if
     RelativeValue = W[k][k];
    printf("RelativeValue = %8.2lf\n", RelativeValue);
     W[k][k] = 1.0;


     for(j=k+1; j < 2*n; j++)
      {
        temp = W[k][j]/RelativeValue;
        if (fabs(temp) < epsilon)
           W[k][j] = 0.0;
        else
            W[k][j] = temp;
      } // for

     for(i=0; i < n; i++)
     {
      if (i != k)
      {
         RelativeValue = W[i][k];
         W[i][k] = 0.0;
         for(j=k+1; j < 2*n; j++)
         {
           temp = W[i][j] - RelativeValue*W[k][j];    
           if (fabs(temp) < epsilon)
              W[i][j] = 0.0;
           else
              W[i][j] = temp;
         } // for
       } // if
     } // for


   printf(" W: \n");
   for(i=0; i < n; i++)
   {
     for(j=0; j < 2*n; j++)
         printf(" %8.2lf " ,W[i][j]);
    printf("\n");
   } // for


  } /* for */


   for(i=0; i < n; i++)
   {
     for(j=0; j < n; j++)
        B[j][i] = W[j][i+n];
   } // for

   printf("\nBI:\n");
   for(i=0; i < n; i++)
   {
     for(j=0; j < n; j++)
         printf(" %lf " ,B[i][j]);
     printf("\n");
   } // for


   printf("\nW:\n");
   for(i=0; i < n; i++)
   {
     for(j=0; j < 2*n; j++)
         printf(" %8.2lf " ,W[i][j]);
     printf("\n");
   } // for




} /*  gaussian */


