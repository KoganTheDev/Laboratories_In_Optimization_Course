/*  simplex_main.c - Partial pivoting */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "simplex.h"
#include "debug.h"
 

// Global Variables

#define N 128
#define M 64


 double  A[N][N];
 double B[N][N];
 double C[N];
 double D[N][N];
 double c[N];
 double b[N];
 double b_aux[N];
 double cb[N];
 double cbBI[N];
 double cbBID[M];
 double cd[N];
 double rd[N];
 double BID[N][N];
 double W[N][N];
 double BI[N][N];
 double BIA_aux[N][N];

double A_aux[N][N];
double BIb[N];
double epsilon;
  
 int d[N];
 int d_aux[N];
 int basis[N];
 int n;
 int m;
 FILE *fp;


  int Initial_n;
   double Initial_W[N][N];
  double Initial_cb[N];
 double Initial_cd[N];
 double Initial_A[N][N];
 double Initial_A_aux[N][N];
 double Initial_c[N];
  double Initial_c_aux[N];
 int Initial_basis[N];
 double Initial_D[N][N];
 int Initial_d[N];
  double Initial_B[N][N];
 double Initial_BIb[N];

  double Initial_C[N][N];
  double Initial_b[N];
  double Initial_b_aux[N];
  double Initial_rd[N];
  double Initial_BID[N][N];
  double Initial_BI[N][N];
  double Initial_cbBI[N];
  double Initial_cbBID[N];
  double Initial_BIA_aux[N][N];




int main(int argc, char *argv[])
{

 int i, j, p, n_p_m, itemp;
 char str[80]; 


 if (argc < 2)
  {
   fprintf(stderr, "Usage: a.exe filename\n");
   return 0;
  } /* if */

 fp = fopen(argv[1], "rt");
 fgets(str, 80, fp);  // "m, n"
 printf("str = %s\n", str);
 fscanf(fp, "%d %d", &m, &n);
  printf("n = %d, m = %d\n", n, m); 

 Initial_n = n + m;

 fgets(str, 80, fp);  // 

  printf("str = %s\n", str);



  n_p_m = n+m;
  
  read_file(); // A, A_aux, c, b initialized

  printf("\nepsilon = %6.2lf\n", epsilon);

  printf(" A: \n"); 
  print_original_system(A, n,m);


  copy_to_initial_matrix();

  printf("Initial_A:\n");
  for(i=0; i < m; i++)
   {
     for(j=0; j < n_p_m; j++)
       printf(" %6.2lf ", Initial_A[i][j]);
     printf("\n");
   } // for



  for(i=0; i < m; i++)
    Initial_basis[i] = i+n;
  for(i=0; i < n; i++)
     Initial_c[i] = 0.0;
  for(i=n; i < Initial_n; i++)
     Initial_c[i] = 1.0;
  for(i=0; i < m; i++)
     Initial_b[i] = b[i];
  for(i=0; i < m; i++)
     Initial_b_aux[i] = b[i];

  printf("\nInitial_basis:\n");
  for(i=0; i < m; i++)
      printf(" %d ", Initial_basis[i]);
  printf("\n");

  printf("\nInitial_c:\n");
  for(i=0; i < Initial_n; i++)
      printf(" %6.2lf ", Initial_c[i]);
  printf("\n");


  printf("\nInitial_b:\n");
  for(i=0; i < m; i++)
      printf(" %6.2lf ", Initial_b[i]);
  printf("\n");

      
  Initial_simplex_algorithm();

  
  for(i=0; i < m; i++)
   {
    itemp = Initial_basis[i];
    basis[i] = itemp;
    if (itemp >= n)
      {
        print_no_solution();
        exit(0);
      } // if

   } // for

     print_initial_solution();      



  simplex_algorithm();



  bublesort_d(basis, BIb, m);

  print_solution();


 return 0;

} /* main */
