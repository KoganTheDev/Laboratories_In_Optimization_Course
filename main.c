#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NMAX 100

typedef double (*FUN_PTR)(double[]);
typedef void (*GRAD_FUN_PTR)(double grad[], double x[]);
typedef int VECTOR_CONVERGENCE_TEST(double arr[], int n, double epsilon);

// Global variables for the Steepest Descent logic
FUN_PTR objective_function;
double grad_vector[NMAX];
double xnm1[NMAX];
double gtemp[NMAX];
double diff[NMAX];
int vector_n;

// Utility functions from original code
void copy_vector(double dest[], double source[], int n) {
    for (int i = 0; i < n; i++) dest[i] = source[i];
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
            x4 = x1 + (x3 - x1) / phi;
            fx4 = (*fp)(x4);
        } else {
            x3 = x4; x4 = x2; fx4 = fx2;
            x2 = x1 + (x3 - x1) / phi1;
            fx2 = (*fp)(x2);
        }
    } while ((x3 - x1) > eps);
    return ((x1 + x3) / 2);
}

void find_initial_alphas(double (*falpha)(double), double *alpha_1, double *alpha_2) {
    double falpha1, falpha2, alpha1, alpha2, prev_alpha;
    alpha1 = 0.0;
    alpha2 = 0.0009765625;
    int going_down = 1;
    while (going_down) {
        prev_alpha = alpha1;
        falpha1 = (*falpha)(alpha1);
        falpha2 = (*falpha)(alpha2);
        alpha1 = alpha2;
        if (falpha2 >= falpha1) going_down = 0;
        else alpha2 = 2.0 * alpha2;
        if (alpha2 > 1e6) break; // Safety break
    }
    *alpha_1 = prev_alpha;
    *alpha_2 = alpha2;
}

int vector_convergence_test(double arr[], int n, double epsilon) {
    for (int i = 0; i < n; i++) if (fabs(arr[i]) > epsilon) return 0;
    return 1;
}

// Steepest Descent Engine
void steepest(double xn[], double x0[], int n, FUN_PTR f, GRAD_FUN_PTR grad, double epsilon, VECTOR_CONVERGENCE_TEST v) {
    vector_n = n;
    objective_function = f;
    copy_vector(xn, x0, n);
    copy_vector(xnm1, xn, n);
    grad(grad_vector, xnm1);
    
    // Initialize diff to bypass first check
    for(int i=0; i<n; i++) diff[i] = epsilon + 1.0;

    int iter = 0;
    while (((v(diff, n, epsilon) == 0) || (v(grad_vector, n, epsilon) == 0)) && iter < 1000) {
        double a1, a2, ak;
        find_initial_alphas(falpha, &a1, &a2);
        ak = golden(falpha, a1, a2, epsilon);
        for (int i = 0; i < n; i++) {
            diff[i] = ak * grad_vector[i];
            xn[i] = xnm1[i] - diff[i];
        }
        copy_vector(xnm1, xn, n);
        grad(grad_vector, xn);
        iter++;
    }
}

// Numerical Gradient
double approx_partial_derivative(double (*obj_f)(double x[]), int i, double x[]) {
    double xi_orig = x[i];
    double h = (fabs(xi_orig) > 1e-6) ? xi_orig / 1048576.0 : 1e-7;
    x[i] = xi_orig + h;
    double t1 = (*obj_f)(x);
    x[i] = xi_orig - h;
    double t2 = (*obj_f)(x);
    x[i] = xi_orig;
    return (t1 - t2) / (2 * h);
}

void approx_g(double grad[], double x[]) {
    for (int i = 0; i < vector_n; i++) grad[i] = approx_partial_derivative(objective_function, i, x);
}

// THE NEW TASK LOGIC STARTS HERE

// Finds a local minimum point for a single dimension while keeping others constant
double find_best_coordinate(double current_x[], int dim, int n, double low, double high, int m, FUN_PTR f) {
    double h = (high - low) / m;
    double test_x[NMAX];
    copy_vector(test_x, current_x, n);

    for (int j = 0; j <= m - 2; j++) {
        test_x[dim] = low + j * h;
        double f1 = f(test_x);
        test_x[dim] = low + (j + 1) * h;
        double f2 = f(test_x);
        test_x[dim] = low + (j + 2) * h;
        double f3 = f(test_x);

        if (f2 < f1 && f2 < f3) {
            return low + (j + 1) * h;
        }
    }
    return (low + high) / 2.0; // Default to mid if no triplet found
}

void mutli_variable_optimization_schema(double xn[], int n, FUN_PTR f, GRAD_FUN_PTR grad, 
                                      double epsilon, VECTOR_CONVERGENCE_TEST v, 
                                      double lowb, double highb, int initial_m) {
    double xm[NMAX];
    double mid = (lowb + highb) / 2.0;
    objective_function = f;
    vector_n = n;

    // Phase 1: Coordinate Descent to find initial x0
    for (int i = 0; i < n; i++) xm[i] = mid;

    // Two rounds of coordinate search
    for (int round = 0; round < 2; round++) {
        for (int i = 0; i < n; i++) {
            xm[i] = find_best_coordinate(xm, i, n, lowb, highb, initial_m, f);
        }
    }
    
    copy_vector(xn, xm, n); // xm is now our x0 for steepest descent

    // Phase 2: Iterative Steeping with Epsilon refinement
    double last_xn[NMAX];
    double current_eps = epsilon;
    double ratio = 0;

    do {
        copy_vector(last_xn, xn, n);
        double start_x[NMAX];
        copy_vector(start_x, xn, n);
        
        steepest(xn, start_x, n, f, grad, current_eps, v);

        // Convergence ratio logic
        double sum_diff = 0, sum_last = 0;
        for (int i = 0; i < n; i++) {
            sum_diff += fabs(xn[i] - last_xn[i]);
            sum_last += fabs(last_xn[i]);
        }
        
        if(sum_last > 0) ratio = (sum_diff / sum_last);
        else ratio = 1.0; // Avoid div by zero

        current_eps /= 2.0;
        
        // Task says loop until ratio is "greater than 0.995" 
        // Note: In typical math, you loop while ratio is SIGNIFICANT. 
        // If ratio is tiny (< 0.005), it means the vectors are nearly identical.
    } while (ratio > 0.005); // Loop while the change is still significant
}

// Example target function
double f_example(double x[]) {
    return (-sin(x[0] + 3*x[1] + 15*x[2]) - sin(3*x[0] + 3*x[1] + 9*x[2]) - sin(x[0] + x[1] + 18*x[2]));
}

int main() {
    double xstar[NMAX];
    int n = 3;

    mutli_variable_optimization_schema(xstar, n, f_example, approx_g, 0.0001, 
                                      vector_convergence_test, 0.0, 1.0, 100);

    printf("\nOptimal solution:\n");
    for(int i=0; i<n; i++) printf("xstar[%d] = %lf\n", i, xstar[i]);

  printf("\n\nIn degrees: xstar[0] = %lf\n,  xstar[1] = %lf\n,  xstar[2] = %lf\n",
                xstar[0]*180.0/M_PI, xstar[1]*180.0/M_PI, xstar[2]*180.0/M_PI);


    printf("\nOptimal value = %lf\n", f_example(xstar));

    return 0;
}