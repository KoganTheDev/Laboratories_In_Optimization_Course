#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NMAX 100
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Typedefs from original code
typedef double (*FUN_PTR)(double[]);
typedef void (*GRAD_FUN_PTR)(double grad[], double x[]);
typedef int VECTOR_CONVERGENCE_TEST(double arr[], int n, double epsilon);

// Global state for steepest logic (from original)
FUN_PTR objective_function;
double grad_vector[NMAX];
double xnm1[NMAX];
double gtemp[NMAX];
double diff[NMAX];
int vector_n;

// --- Helper Functions ---

void copy_vector(double dest[], double source[], int n) {
    for (int i = 0; i < n; i++) dest[i] = source[i];
}

int vector_convergence_test(double arr[], int n, double epsilon) {
    for (int i = 0; i < n; i++)
        if (fabs(arr[i]) > epsilon) return 0;
    return 1;
}

double falpha(double alpha) {
    for (int i = 0; i < vector_n; i++)
        gtemp[i] = xnm1[i] - alpha * grad_vector[i];
    return objective_function(gtemp);
}

double golden(double (*fp)(double), double x1, double x3, double eps) {
    double x2, fx2, x4, fx4;
    double phi = 1.618, phi1 = 2.618;
    x2 = x1 + (x3 - x1) / phi1;
    fx2 = (*fp)(x2);
    x4 = x1 + (x3 - x1) / phi;
    fx4 = (*fp)(x4);
    do {
        if (fx2 > fx4) {
            x1 = x2; x2 = x4; fx2 = fx4;
            x4 = x1 + (x3 - x1) / phi; fx4 = (*fp)(x4);
        } else {
            x3 = x4; x4 = x2; fx4 = fx2;
            x2 = x1 + (x3 - x1) / phi1; fx2 = (*fp)(x2);
        }
    } while ((x3 - x1) > eps);
    return ((x1 + x3) / 2);
}

void find_initial_alphas(double (*f_alpha)(double), double *alpha_1, double *alpha_2) {
    double f1, f2, a1 = 0.0, a2 = 0.0009765625, prev_a = 0.0;
    while (1) {
        f1 = f_alpha(a1);
        f2 = f_alpha(a2);
        if (f2 >= f1) break;
        prev_a = a1;
        a1 = a2;
        a2 *= 2.0;
        if (a2 > 1e6) break; // Safety break
    }
    *alpha_1 = prev_a;
    *alpha_2 = a2;
}

// --- Optimization Core ---

void steepest(double xn[], double x0[], int n, FUN_PTR f, GRAD_FUN_PTR grad, double epsilon, VECTOR_CONVERGENCE_TEST v) {
    double alpha_1, alpha_2, alpha_k;
    vector_n = n;
    objective_function = f;
    copy_vector(xn, x0, n);
    copy_vector(xnm1, xn, n);
    grad(grad_vector, xnm1);
    
    // Initial diff to enter loop
    for(int i=0; i<n; i++) diff[i] = epsilon + 1.0;

    while ((v(diff, n, 0.001) == 0) || (v(grad_vector, n, 0.001) == 0)) {
        find_initial_alphas(falpha, &alpha_1, &alpha_2);
        alpha_k = golden(falpha, alpha_1, alpha_2, epsilon);
        for (int i = 0; i < n; i++) {
            diff[i] = alpha_k * grad_vector[i];
            xn[i] = xnm1[i] - diff[i];
        }
        copy_vector(xnm1, xn, n);
        grad(grad_vector, xn);
    }
}

// --- Coordinate Descent Logic for X0 ---

void find_initial_x0(double x0[], int n, FUN_PTR f, double lowb, double highb, int m) {
    double h = (highb - lowb) / m;
    double mid = (lowb + highb) / 2.0;
    double xtemp[NMAX];

    // Initialize with midpoints
    for (int i = 0; i < n; i++) x0[i] = mid;

    // Perform two passes of coordinate adjustment
    for (int pass = 0; pass < 2; pass++) {
        for (int i = 0; i < n; i++) {
            copy_vector(xtemp, x0, n);
            double best_xi = lowb;
            double min_f = 1e30;

            for (int j = 0; j <= m - 2; j++) {
                double x_j = lowb + j * h;
                xtemp[i] = x_j;       double f_j = f(xtemp);
                xtemp[i] = x_j + h;   double f_j1 = f(xtemp);
                xtemp[i] = x_j + 2*h; double f_j2 = f(xtemp);

                if (f_j > f_j1 && f_j1 < f_j2) {
                    best_xi = x_j + h;
                    break; 
                }
                if (f_j1 < min_f) { min_f = f_j1; best_xi = x_j + h; }
            }
            x0[i] = best_xi;
        }
    }
}

// --- Schema Implementation ---

void mutli_variable_optimization_schema(double xn[], int n, FUN_PTR f, GRAD_FUN_PTR grad, 
                                       double epsilon, VECTOR_CONVERGENCE_TEST v, 
                                       double lowb, double highb, int initial_m) {
    double x0[NMAX], x_prev[NMAX];
    double current_eps = epsilon;
    
    printf("Stage 1: Finding initial x0...\n");
    find_initial_x0(x0, n, f, lowb, highb, initial_m);
    
    int first_run = 1;
    while (1) {
        steepest(xn, x0, n, f, grad, current_eps, v);
        
        if (!first_run) {
            double sum_diff = 0, sum_prev = 0;
            for (int i = 0; i < n; i++) {
                sum_diff += fabs(xn[i] - x_prev[i]);
                sum_prev += fabs(xn[i]);
            }
            // Convergence check based on ratio of change
            if (sum_prev > 0 && (1.0 - (sum_diff / sum_prev)) > 0.995) break;
        }

        copy_vector(x_prev, xn, n);
        copy_vector(x0, xn, n); // Next run starts from current result
        current_eps /= 2.0;
        first_run = 0;
        if (current_eps < 1e-12) break; // Precision floor
    }
}

// --- Example Objective & Gradient (Quadratic Form) ---

double Q[3][3], b[3];
void approx_g(double grad[], double x[]) {
    double h = 1e-7;
    for (int i = 0; i < 3; i++) {
        double tmp = x[i];
        x[i] = tmp + h; double f1 = objective_function(x);
        x[i] = tmp - h; double f2 = objective_function(x);
        grad[i] = (f1 - f2) / (2 * h);
        x[i] = tmp;
    }
}

double f(double x[]) {
    int i,j;
    double sum;

    sum = (-sin(x[0]+3*x[1] + 15*x[2]) - sin(3*x[0] + 3*x[1] + 9*x[2]) - sin(x[0] + x[1] + 18*x[2]));

    return sum;
}

int main()
    {
    double xstar[10], value;
    int i, j;

    mutli_variable_optimization_schema(xstar, 3,
    f, approx_g, 0.00001, vector_convergence_test,
    0.0, 1.0, 100);

    printf("\n\noptimal solution:\n\txstar[0] = %lf,\n\txstar[1] = %lf,\n\txstar[2] = %lf\n",
        xstar[0],
        xstar[1],
        xstar[2]);

    printf("\n\nIn degrees:\n\txstar[0] = %lf,\n\txstar[1] = %lf,\n\txstar[2] = %lf\n",
        xstar[0]*180.0/M_PI,
        xstar[1]*180.0/M_PI,
        xstar[2]*180.0/M_PI);

    printf("\n\noptimal value = %lf\n", f(xstar));
}
