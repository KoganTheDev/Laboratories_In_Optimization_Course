#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

// Step size for numerical differentiation (Centered Difference)
#define NUM_DIFF_H 1e-5

/**
 * @brief Numerical differentiation - approximation of the first derivative.
 *
 * Uses the Centered Difference method:
 * f'(x) ≈ (f(x + h_diff) - f(x - h_diff)) / (2 * h_diff)
 *
 * @param fp Pointer to the objective function f(x).
 * @param x The point where the derivative is calculated.
 * @return The approximate value of f'(x).
 */
double numerical_derivative(double (*fp)(double), double x)
{
    // Check if the differentiation step is too small to prevent catastrophic cancellation
    double h = NUM_DIFF_H;
    if (h == 0.0) h = 1e-6; // Safety fallback

    return (fp(x + h) - fp(x - h)) / (2.0 * h);
}

/**
 * @brief Inverse Quadratic Interpolation Root Finder (Internal Logic).
 *
 * Finds the root of a function (f'(x) in our case).
 *
 * @param fp_prime Pointer to the derivative function f'(x) (passed implicitly via numerical_derivative).
 * @param x0 Initial approximation point 1.
 * @param x1 Initial approximation point 2.
 * @param x2 Initial approximation point 3.
 * @param epsilon Tolerance for the convergence criterion: |x_new - x_prev| < epsilon.
 * @param obj_fp Pointer to the original objective function f(x).
 * @return The root approximation xstar.
 */
double opt_inv_quad(double (*fp)(double), double low, double high, double h, double epsilon)
{
    double x0, x1, x2;
    double f_left, f_mid, f_right;
    double diff, d0, d1, d2, c;
    int found = 0;

    /* Step 1: find initial triple where f(x0)>f(x1)<f(x2) */
    double x = low + h;
    while (x + h <= high)
    {
        f_left = fp(x - h);
        f_mid = fp(x);
        f_right = fp(x + h);

        if (f_left > f_mid && f_mid < f_right)
        {
            x0 = x - h;
            x1 = x;
            x2 = x + h;
            found = 1;
            break;
        }
        x += h;
    }

    if (!found)
    {
        /* fallback in case no triple found */
        x0 = low;
        x1 = (low + high) / 2.0;
        x2 = high;
    }

    /* Step 2: apply inverse quadratic interpolation to f'(x) */
    diff = fabs(x2 - x1);
    while (diff > epsilon)
    {
        d0 = numerical_derivative(fp, x0);
        d1 = numerical_derivative(fp, x1);
        d2 = numerical_derivative(fp, x2);

        c = (x0 * d1 * d2) / ((d0 - d1) * (d0 - d2))
            + (x1 * d0 * d2) / ((d1 - d0) * (d1 - d2))
            + (x2 * d0 * d1) / ((d2 - d0) * (d2 - d1));

        x0 = x1;
        x1 = x2;
        x2 = c;

        diff = fabs(x2 - x1);
    }

    return x2;
}


double obj_f(double x)
{
    double xp, sum;

    sum = x * x * x * x;
    sum = sum - 2.0 * x * x * x;
    sum = sum + 3.0 * x * x;
    sum = sum - 4.0 * x;
    sum = sum - 4.0;


    return sum;
} // obj_f


int main()
{
    double low, high, xstar, epsilon, h;

    printf("\nEnter low, high, h, epsilon\n");
    scanf("%lf %lf %lf %lf", &low, &high, &h, &epsilon);

    xstar = opt_inv_quad(obj_f, low, high, h, epsilon);

    printf("\nxstar = %lf\n", xstar);


} // main
