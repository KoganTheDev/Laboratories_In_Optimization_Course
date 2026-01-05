// simplex_algorithm.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simplex.h"

void simplex_algorithm()
{
    int i, j, k, optimal_flag, enter_id, exiting_id, itemp, basis_i;
    double dtemp, min_value;
    int count = 1;

    double min_score, current_score, norm_sq;
    int best_k, col_idx;

    optimal_flag = 0;

    printf(" m = %d, n = %d\n", m, n);

    printf("\nbasis1:\n");
    for (i = 0; i < m; i++)
        printf(" %d ", basis[i]);
    printf("\n");


    printf("A:\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            printf(" %6.2lf ", A[i][j]);
        printf("\n");
    } // for



    while (optimal_flag == 0)
    {

        printf("count = %d\n", count);
        count++;

        bublesort(basis, m);

        printf("\nbasis2:\n");
        for (i = 0; i < m; i++)
            printf(" %d ", basis[i]);
        printf("\n");


        set_d();


        printf("\nd:\n");
        for (i = 0; i < n; i++)
            printf(" %d ", d[i]);
        printf("\n");


        set_A_aux();

        printf("\nA_aux (B, D):\n");
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
                printf(" %6.2lf ", A_aux[i][j]);
            printf("\n");
        } // for


        copy_submatrix(B, A_aux, 0, m, 0, m); // Set B

        printf("\nB:\n");
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < m; j++)
                printf(" %6.2lf ", B[i][j]);
            printf("\n");
        } // for  


        inv_gaussian(BI, B, m); // BI = B-1  

        erase_epsilons_matrix(BI, m, m);

        printf("\nBI:\n");
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < m; j++)
                printf(" %6.2lf ", BI[i][j]);
            printf("\n");
        } // for  


        matrix_mult(BIA_aux, BI, A_aux,
            m, m, n);
        erase_epsilons_matrix(BIA_aux, m, n);

        printf("\nBIA_aux (I, B-1*D):\n");
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
                printf(" %6.2lf ", BIA_aux[i][j]);
            printf("\n");
        } 

        printf("\nA_aux (B,D):\n");
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
                printf(" %6.2lf ", A_aux[i][j]);
            printf("\n");
        }


        printf("b:\n");
        for (i = 0; i < m; i++)
            printf(" %6.2lf ", b[i]);



        matrix_vector_mult(BIb, BI, b, m, m);
        erase_epsilons_vector(BIb, m);

        printf("\nBIb:\n");
        for (i = 0; i < m; i++)
            printf(" %6.2lf ", BIb[i]);
        printf("\n");


        copy_submatrix(D, A_aux,
            0, m, m, n - m);

        printf("D:\n");
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n - m; j++)
                printf(" %6.2lf ", D[i][j]);
            printf("\n");
        }


        compute_cb_cd();

        printf("\ncb:\n");
        for (i = 0; i < m; i++)
            printf(" %6.2lf ", cb[i]);
        printf("\n");

        printf("\ncd:\n");
        for (i = 0; i < (n - m); i++)
            printf(" %6.2lf ", cd[i]);
        printf("\n");


        vector_matrix_mult(cbBI, cb, BI, m, m);
        erase_epsilons_vector(cbBI, m);

        printf("\ncbBI:\n");
        for (i = 0; i < m; i++)
            printf(" %6.2lf ", cbBI[i]);
        printf("\n");


        vector_matrix_mult(cbBID, cbBI, D,
            m, n - m);
        erase_epsilons_vector(cbBID, n - m);


        printf("\ncbBID:\n");
        for (i = 0; i < (n - m); i++)
            printf(" %6.2lf ", cbBID[i]);
        printf("\n");



        vector_subtract(rd, cd, cbBID,
            n - m);
        erase_epsilons_vector(rd, n - m);

        printf("\nrd( cd - cbBID ):\n");
        for (i = 0; i < (n - m); i++)
            printf(" %6.2lf ", rd[i]);
        printf("\n\n");


        min_value = find_min_value(rd, n - m);
        if (min_value >= -1e-9) // בדיקה עם אפסילון ליתר ביטחון 
            optimal_flag = 1;
        else
        {


            best_k = -1;
            min_score = 0.0;

            for (k = 0; k < (n - m); k++) {

                if (rd[k] < -1e-9) {

                    // חישוב הנורמה בריבוע של העמודה המתאימה d_k
                    // העמודה d_k נמצאת במטריצה BIA_aux החל מעמודה m
                    col_idx = m + k;
                    norm_sq = 0.0;

                    for (i = 0; i < m; i++) {
                        double val = BIA_aux[i][col_idx];
                        norm_sq += val * val;
                    }

                    if (norm_sq < 1e-9) norm_sq = 1e-9;

                    current_score = rd[k] / norm_sq;

                    if (best_k == -1 || current_score < min_score) {
                        min_score = current_score;
                        best_k = k;
                    }
                }
            }

            if (best_k != -1) {
                enter_id = d[best_k];
            }
            else {
                optimal_flag = 1;
            }


            exiting_id =
                find_exiting_id(BIA_aux, BIb,
                    enter_id, n, m);
            printf("\nenter_id  = %d,  exiting_id = %d,"
                " d[exiting_id] = %d\n",
                enter_id, exiting_id,
                d[exiting_id]);

            printf("pivot: enter_id = %d, exiting_id = %d\n", enter_id,
                d[exiting_id]);




            basis[exiting_id] = enter_id;
            printf("\nbasis3:\n");
            for (i = 0; i < m; i++)
                printf(" %d ", basis[i]);
            printf("\n");

        }

    }

}