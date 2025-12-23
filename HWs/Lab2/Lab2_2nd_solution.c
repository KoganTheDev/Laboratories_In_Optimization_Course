#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

/**
 * @brief Inverse Quadratic Interpolation Root Finder.
 *
 * Implements the Inverse Quadratic Interpolation method to find a root (x*)
 * of a non-linear function f(x), such that f(x*) = 0.
 * The method uses three points (x0, x1, x2) to fit an inverse quadratic
 * polynomial (x as a function of f) and finds the root by evaluating
 * this polynomial at f=0.
 *
 * @param fp Pointer to the target function f(x).
 * @param x0 Initial approximation point 1.
 * @param x1 Initial approximation point 2.
 * @param x2 Initial approximation point 3.
 * @param epsilon Tolerance for the convergence criterion: |x_new - x_prev| < epsilon.
 * @return The root approximation xstar.
 */
double inv_quad(double (*fp)(double), double x0, double x1, double x2, double epsilon)
{
    double f0, f1, f2;      // Function values at x0, x1, x2
    double x_prev, x_new;   // Variables for iteration
    int max_iterations = 100; // Safety limit to prevent infinite loops
    int iter = 0;

    // Set the previous approximation to x2 for the first convergence check.
    x_prev = x2;

    while (iter < max_iterations) {
        // Calculate function values at the current three points
        f0 = fp(x0);
        f1 = fp(x1);
        f2 = fp(x2);

        // Check for potential division by zero (identical function values)
        if (fabs(f0 - f1) < 1e-12 || fabs(f0 - f2) < 1e-12 || fabs(f1 - f2) < 1e-12) {
            printf("Error: Two function values are too close or identical (f0, f1, or f2). Interpolation failed.\n");
            return x_prev;
        }

        // --- Inverse Quadratic Formula Calculation ---
        x_new = (x0 * f1 * f2) / ((f0 - f1) * (f0 - f2))
            + (x1 * f0 * f2) / ((f1 - f0) * (f1 - f2))
            + (x2 * f0 * f1) / ((f2 - f0) * (f2 - f1));

        // Check for convergence: stop if the difference between the current and previous
        // approximation is less than the tolerance epsilon.
        if (fabs(x_new - x_prev) < epsilon) {
            return x_new;
        }

        // Simple check for divergence: if x_new is extremely far from the current points,
        // it suggests divergence, though this is only a rough safeguard.
        double range = fmax(fmax(x0, x1), x2) - fmin(fmin(x0, x1), x2);
        if (range > 1e-6 && fabs(x_new - x_prev) > 100 * range) {
            printf("Warning: Significant divergence detected. Aborting interpolation.\n");
            return x_new;
        }

        // Update x_prev for the next iteration's convergence check.
        x_prev = x2;

        // Shift the points for the next iteration: (x0, x1, x2) -> (x1, x2, x_new)
        x0 = x1;
        x1 = x2;
        x2 = x_new;

        iter++;
    }

    // Warning if the maximum number of iterations is reached
    printf("Warning: Maximum iterations (%d) reached without convergence.\n", max_iterations);
    return x_new;
}

/**
 * @brief Example Target Function f(x) for the second test case.
 *
 * f(x) = 1.1*x^4 - 2.1*x^2 - 0.2
 * The root of this function is approximately x = 1.414214 (sqrt(2))
 */
double f(double x)
{
    double xp, sum;

    sum = 1.1 * x * x * x * x;
    sum = sum - 2.1 * x * x;
    sum = sum - 0.2;

    return sum;
} // f


/**
 * @brief Main function to test the Inverse Quadratic Interpolation routine.
 */
int main()
{
    double x0, x1, x2, xstar, epsilon;

    // Prompt the user for input
    printf("\nEnter x0, x1, x2, epsilon\n");

    // Read input values
    if (scanf("%lf %lf %lf %lf", &x0, &x1, &x2, &epsilon) != 4) {
        printf("Error reading input.\n");
        return 1;
    }

    // Call the root-finding routine
    xstar = inv_quad(f, x0, x1, x2, epsilon);

    // Print the result
    printf("\nxstar = %lf\n", xstar);

    return 0;
} // main