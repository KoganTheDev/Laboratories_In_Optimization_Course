#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simplex.h"

void simplex_algorithm() {
    int i, j, k, optimal_flag, enter_id, exiting_id, basis_i;
    double min_criteria, current_criteria, norm_sq, reduced_cost;
    int iteration = 1;

    optimal_flag = 0;

    // Main Simplex Loop
    while (!optimal_flag) {
        enter_id = -1;
        min_criteria = 0; // We look for the most negative value

        // 1. SELECT ENTERING VARIABLE (Steepest Edge Rule)
        for (j = 0; j < n; j++) {
            // Check if variable j is non-basic (Reduced cost is in the objective row, e.g., A[m][j])
            // In many implementations, reduced costs rd are in row 'm'
            reduced_cost = A[m][j]; 

            if (reduced_cost < -1e-9) { // Candidate for entering
                norm_sq = 0;
                // Calculate the squared norm of the direction vector: 1 + ||B^-1 * Ak||^2
                // The column A[i][j] for i=0..m-1 represents B^-1 * Ak in the tableau
                for (i = 0; i < m; i++) {
                    norm_sq += A[i][j] * A[i][j];
                }
                
                // steepest descent criteria: rd / sqrt(1 + sum(d_i^2))
                current_criteria = reduced_cost / sqrt(1 + norm_sq);

                if (enter_id == -1 || current_criteria < min_criteria) {
                    min_criteria = current_criteria;
                    enter_id = j;
                }
            }
        }

        // Check for optimality
        if (enter_id == -1) {
            optimal_flag = 1;
            printf("Optimal solution found at iteration %d\n", iteration);
            break;
        }

        // 2. SELECT EXITING VARIABLE (Ratio Test)
        exiting_id = -1;
        double min_ratio = -1;

        for (i = 0; i < m; i++) {
            if (A[i][enter_id] > 1e-9) {
                double ratio = A[i][n] / A[i][enter_id]; // A[i][n] is usually the RHS (b)
                if (exiting_id == -1 || ratio < min_ratio) {
                    min_ratio = ratio;
                    exiting_id = i;
                }
            }
        }

        if (exiting_id == -1) {
            printf("Unbounded problem.\n");
            return;
        }

        // 3. PIVOTING
        // Update basis: basis[exiting_id] = enter_id
        basis[exiting_id] = enter_id;

        // Perform Gaussian elimination on the tableau
        double pivot_val = A[exiting_id][enter_id];
        for (j = 0; j <= n; j++) {
            A[exiting_id][j] /= pivot_val;
        }

        for (i = 0; i <= m; i++) {
            if (i != exiting_id) {
                double factor = A[i][enter_id];
                for (j = 0; j <= n; j++) {
                    A[i][j] -= factor * A[exiting_id][j];
                }
            }
        }
        
        iteration++;
    }
}