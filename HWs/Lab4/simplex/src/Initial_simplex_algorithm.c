// Initial_simplex_algorithm.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simplex.h"

void Initial_simplex_algorithm()
{
   int i, j,k, optimal_flag, enter_id,  exiting_id, itemp, basis_i;
   double dtemp, min_value;
   int count=0;

  optimal_flag = 0;

  printf(" m = %d, Initial_n = %d\n", m, Initial_n);

  printf("\nInitial_basis:\n");
  for(i=0; i < m; i++)
    printf(" %d ", Initial_basis[i]);
  printf("\n");


  printf("Initial_A:\n");
  for(i=0; i < m; i++)
   {
     for(j=0; j < Initial_n; j++)
       printf(" %6.2lf ", Initial_A[i][j]);
     printf("\n");
   } // for


  
 while(optimal_flag == 0)
 {


  bublesort(Initial_basis, m);

  printf("\nInitial_basis:\n");
  for(i=0; i < m; i++)
    printf(" %d ", Initial_basis[i]);
  printf("\n");

 
  Initial_set_d();


   printf("\nInitial_d:\n");
   for(i=0; i < Initial_n; i++)
     printf(" %d ", Initial_d[i]);
   printf("\n");


   set_Initial_A_aux();

  printf("\nInitial_A_aux (B, D):\n");
  for(i=0; i < m; i++)
   {
     for(j=0; j < Initial_n; j++)
       printf(" %6.2lf ", Initial_A_aux[i][j]);
     printf("\n");
   } // for


   copy_submatrix(Initial_B, Initial_A_aux,  0, m, 0, m); // Set B

  printf("\nInitial_B:\n");
  for(i=0; i < m; i++)
   {
     for(j=0; j < m; j++)
        printf(" %6.2lf ", Initial_B[i][j]);
     printf("\n");
   } // for  


   inv_gaussian(Initial_BI, Initial_B,  m); // BI = B-1  

   erase_epsilons_matrix(Initial_BI, m, m);

   printf("\nInitial_BI:\n");
   for(i=0; i < m; i++)
    {
      for(j=0; j < m; j++)
         printf(" %6.2lf ", Initial_BI[i][j]);
      printf("\n");
    } // for  


   matrix_mult(Initial_BIA_aux, Initial_BI, Initial_A_aux, 
            m, m, Initial_n);

   erase_epsilons_matrix(Initial_BIA_aux, m, Initial_n);
   
  printf("\nInitial_BIA_aux (I, B-1*D):\n");
  for(i=0; i < m; i++)
   {
     for(j=0; j < Initial_n; j++)
        printf(" %6.2lf ", Initial_BIA_aux[i][j]);
     printf("\n");
   } // for  

  printf("\nInitial_A_aux (B,D):\n");
  for(i=0; i < m; i++)
   {
     for(j=0; j < Initial_n; j++)
        printf(" %6.2lf ", Initial_A_aux[i][j]);
     printf("\n");
   } // for  


   printf("Initial_b:\n");
   for(i=0; i < m; i++)
     printf(" %6.2lf ", Initial_b[i]);



   matrix_vector_mult(Initial_BIb, Initial_BI, Initial_b,  m, m);
   erase_epsilons_vector(Initial_BIb, m);

   printf("\nInitial_BIb:\n");

   for(i=0; i < m; i++)
     printf(" %6.2lf ", Initial_BIb[i]);
   printf("\n");


   copy_submatrix(Initial_D, Initial_A_aux,  
         0, m, m, Initial_n-m); // Set Initial_D

  printf("Initial_D:\n");
  for(i=0; i < m; i++)
   {
     for(j=0; j < Initial_n-m; j++)
        printf(" %6.2lf ", Initial_D[i][j]);
     printf("\n");
   } // for  

// END OF FOR DEBUG ONLY

   compute_Initial_cb_Initial_cd();

   printf("\nInitial_cb:\n");
   for(i=0; i < m; i++)
     printf(" %6.2lf ", Initial_cb[i]);
   printf("\n");

   printf("\nInitial_cd:\n");
   for(i=0; i < (Initial_n-m); i++)
     printf(" %6.2lf ", Initial_cd[i]);
   printf("\n");


// cbBI = cb * B-1

   vector_matrix_mult(Initial_cbBI, Initial_cb, Initial_BI,  m, m); 
   erase_epsilons_vector(Initial_cbBI, m);

   printf("\nInitial_cbBI:\n");
   for(i=0; i < m; i++)
     printf(" %6.2lf ", Initial_cbBI[i]);
   printf("\n");


    vector_matrix_mult(Initial_cbBID, Initial_cbBI, Initial_D, 
   m, Initial_n - m); 
   erase_epsilons_vector(Initial_cbBID, Initial_n - m);


  printf("\nInitial_cbBID:\n");
  for(i=0; i < (Initial_n - m); i++)
        printf(" %6.2lf ", Initial_cbBID[i]);
   printf("\n");



    vector_subtract(Initial_rd, Initial_cd,  Initial_cbBID, 
     Initial_n-m);
    erase_epsilons_vector(Initial_rd, Initial_n - m);

   printf("\nInitial_rd( cd - cbBID ):\n");
   for(i=0; i < (Initial_n-m); i++)
     printf(" %6.2lf ", Initial_rd[i]);
   printf("\n\n");


    min_value = find_min_value(Initial_rd, Initial_n - m);
    if (min_value >= 0.0) 
       optimal_flag = 1;
    else
    {
        enter_id = find_Initial_most_negative();
        exiting_id = 
      find_Initial_exiting_id(Initial_BIA_aux,Initial_BIb,
           enter_id, Initial_n, m);
     printf("\nenter_id  = %d,  exiting_id = %d," 
              " Initial_d[exiting_id] = %d\n", 
                                  enter_id, exiting_id, 
                                  Initial_d[exiting_id]);

   Initial_basis[exiting_id] =   enter_id;
   printf("\nInitial_basis:\n");
   for(i=0; i < m; i++)
     printf(" %d ", Initial_basis[i]);
   printf("\n");

    } // else 

 } // while

} //Initial_simplex_algorithm
         
