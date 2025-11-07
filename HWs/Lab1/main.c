#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
double compute_polynom(double coeffs[], double x, int n);
double scaled_compute_polynom(double coeffs[], double x, int n);
int main()
{

    double coeffs[9] = { 10.1, 0.0, -20.2, 0.0, 30.3, 0.0, -60.6 };
    double x, val1, val2;

    x = sqrt(2.0);

    val1 = compute_polynom(coeffs, x, 7);

    val2 = scaled_compute_polynom(coeffs, x, 7);

    printf("val1 = %lg, val2 = %lg\n", val1, val2);


    return 0;

} // main

double compute_polynom(double coeffs[], double x, int n) {

    double result = 0;
    double* power_array = malloc(n * sizeof(double));  power_array[0] = x;
    for (int j = 1; j < n; j++) {
        power_array[j] = power_array[j - 1] * x;
    }

    for (int i = 0; i < n; i++) {
        result += coeffs[i] * power_array[n - i - 1];
    }
    free(power_array);
    return result;
}


double scaled_compute_polynom(double coeffs[], double x, int n) {

    double maxnum = 0;
    double normalize[9] = {};
    double val1, result;
    memcpy(normalize, coeffs, n * sizeof(double));
    for (int i = 0; i < n; i++) {
        if (fabs(coeffs[i]) > maxnum) {
            maxnum = fabs(coeffs[i]);
        }

    }

    for (int i = 0; i < n; i++) {

        normalize[i] = normalize[i] / maxnum;
    }
    val1 = compute_polynom(normalize, x, 7);

    result = val1 * maxnum;

    return result;
}
