// simplex_algorithm.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simplex.h"

#define MAX_ITERATIONS 10000 // Safety limit

void simplex_algorithm()
{
    int i, j, k, optimal_flag, enter_id, exiting_id;
    double min_value;
    int count = 1;

    // Steepest Edge variables
    double min_steepest_val;
    int best_k_index;
    double current_norm_sq, current_norm, current_ratio;

    optimal_flag = 0;

    printf(" m = %d, n = %d\n", m, n);

    printf("\nbasis1:\n");
    for(i = 0; i < m; i++)
        printf(" %d ", basis[i]);
    printf("\n");

    printf("A:\n");
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++)
            printf(" %6.2lf ", A[i][j]);
        printf("\n");
    }

    while(optimal_flag == 0)
    {
        if (count > MAX_ITERATIONS) {
            printf("\n!!! STOPPED: Max iterations reached !!!\n");
            break;
        }

        printf("count = %d\n", count);
        count++;

        bublesort(basis, m);

        printf("\nbasis2:\n");
        for(i = 0; i < m; i++)
            printf(" %d ", basis[i]);
        printf("\n");

        set_d(); 

        printf("\nd:\n");
        for(i = 0; i < n; i++)
            printf(" %d ", d[i]);
        printf("\n");

        set_A_aux();

        copy_submatrix(B, A_aux, 0, m, 0, m); 

        inv_gaussian(BI, B, m); 

        erase_epsilons_matrix(BI, m, m);

        matrix_mult(BIA_aux, BI, A_aux, m, m, n);
        erase_epsilons_matrix(BIA_aux, m, n);

        printf("\nBIA_aux (I, B-1*D):\n");
        for(i = 0; i < m; i++) {
            for(j = 0; j < n; j++)
                printf(" %6.2lf ", BIA_aux[i][j]);
            printf("\n");
        }

        matrix_vector_mult(BIb, BI, b, m, m);
        erase_epsilons_vector(BIb, m);

        copy_submatrix(D, A_aux, 0, m, m, n - m); 

        compute_cb_cd();

        vector_matrix_mult(cbBI, cb, BI, m, m);
        erase_epsilons_vector(cbBI, m);

        vector_matrix_mult(cbBID, cbBI, D, m, n - m);
        erase_epsilons_vector(cbBID, n - m);

        vector_subtract(rd, cd, cbBID, n - m);
        erase_epsilons_vector(rd, n - m);

        printf("\nrd( cd - cbBID ):\n");
        for(i = 0; i < (n - m); i++)
            printf(" %6.2lf ", rd[i]);
        printf("\n\n");

        min_value = find_min_value(rd, n - m);
        
        if (min_value >= -0.000000001) {
            optimal_flag = 1;
        }
        else
        {
            // --- Steepest Edge Algorithm ---
            
            best_k_index = -1;
            min_steepest_val = 1e30; 

            for (k = 0; k < (n - m); k++) {
                
                // Check only improving variables
                if (rd[k] < -0.000000001) {
                    
                    current_norm_sq = 0.0;
                    // Calculate norm of column vector (d_k)
                    for (i = 0; i < m; i++) {
                        double val = BIA_aux[i][m + k];
                        current_norm_sq += val * val;
                    }
                    
                    current_norm = sqrt(current_norm_sq); 
                    if (current_norm < 1e-9) current_norm = 1e-9;

                    // Steepest Edge Rule: rd / ||d||
                    current_ratio = rd[k] / current_norm;

                    if (current_ratio < min_steepest_val) {
                        min_steepest_val = current_ratio;
                        best_k_index = k;
                    }
                }
            }

            if (best_k_index != -1) {
                // Map local index to global variable ID
                enter_id = d[m + best_k_index];
            } else {
                enter_id = find_most_negative();
            }
            
            // --- End Algorithm ---

            exiting_id = find_exiting_id(BIA_aux, BIb, enter_id, n, m);
            
            int exiting_val = (exiting_id >= 0 && exiting_id < m) ? basis[exiting_id] : -1;

            printf("\nenter_id  = %d,  exiting_id = %d,"
                   " d[exiting_id] = %d\n", 
                   enter_id, exiting_id, exiting_val);

            printf("pivot: enter_id = %d, exiting_id = %d\n", enter_id, exiting_val);

            basis[exiting_id] = enter_id;
            
            printf("\nbasis3:\n");
            for(i = 0; i < m; i++)
                printf(" %d ", basis[i]);
            printf("\n");

        } // else
    } // while
} // simplex_algorithm