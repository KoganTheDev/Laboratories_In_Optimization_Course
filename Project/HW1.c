#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double find_highest_absolute_coeff(double coeffs[], int n)
{
	double max_coeff = 0.0;

	for (int i = 0; i < n; i++)
	{
		double absolute_coeff = fabs(coeffs[i]);
		if (absolute_coeff > max_coeff)
		{
			max_coeff = absolute_coeff;
		}
	}

	return max_coeff;
}

double compute_polynom(double coeffs[], double x, int n)
{
	double result = coeffs[n - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		result = result * x + coeffs[i];
	}

	return result;
}


double scaled_compute_polynom(double coeffs[], double x, int n)
{
	double max_absolute_coeff = find_highest_absolute_coeff(coeffs, n);

	// If cmax is less than or equal to 1, no scaling is needed
	if (max_absolute_coeff <= 1)
	{
		return compute_polynom(coeffs, x, n);
	}

	// Create a temporary array to hold the scaled coefficients
	double* temp_coeffs = (double*)malloc(n * sizeof(double));
	if (temp_coeffs == NULL) {
		// Handle memory allocation failure
		fprintf(stderr, "Memory allocation failed in scaled_compute_polynom.\n");
		return 0.0;
	}

	// Divide each coefficient by cmax
	for (int i = 0; i < n; i++)
	{
		temp_coeffs[i] = coeffs[i] / max_absolute_coeff;
	}

	double scaled_result = compute_polynom(temp_coeffs, x, n);
	
	free(temp_coeffs);

	return max_absolute_coeff * scaled_result;
}


int main()
{

	double coeffs[9] = { 10.1, 0.0, -20.2, 0.0, 30.3, 0.0, -60.6 };
	double x, val1, val2;

	x = sqrt(2.0);

	val1 = compute_polynom(coeffs, x, 8);
	val2 = scaled_compute_polynom(coeffs, x, 8);

	printf("val1 = %lg, val2 = %lg\n", val1, val2);

	return 0;
} 
