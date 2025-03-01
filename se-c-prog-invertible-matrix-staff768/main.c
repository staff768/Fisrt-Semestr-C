#include <stdio.h>
#include <stdlib.h>

int reverse_matrix(double **matrix, int size, double **result)
{
	double **augmented = (double **)malloc(size * sizeof(double *));
	for (int i = 0; i < size; ++i)
	{
		augmented[i] = (double *)malloc(2 * size * sizeof(double));
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			augmented[i][j] = matrix[i][j];
		}
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (i == j)
			{
				augmented[i][size + j] = 1.0;
			}
			else
			{
				augmented[i][size + j] = 0.0;
			}
		}
	}

	for (int i = 0; i < size; ++i)
	{
		int max_row = i;
		for (int k = i + 1; k < size; ++k)
		{
			if (augmented[k][i] * augmented[k][i] > augmented[max_row][i] * augmented[max_row][i])
			{
				max_row = k;
			}
		}

		if (augmented[max_row][i] == 0)
		{
			for (int i = 0; i < size; ++i)
			{
				free(augmented[i]);
			}
			free(augmented);
			return 0;
		}

		if (max_row != i)
		{
			for (int j = 0; j < 2 * size; ++j)
			{
				double temp = augmented[i][j];
				augmented[i][j] = augmented[max_row][j];
				augmented[max_row][j] = temp;
			}
		}

		double pivot = augmented[i][i];
		for (int j = 0; j < 2 * size; ++j)
		{
			augmented[i][j] /= pivot;
		}

		for (int j = i + 1; j < size; ++j)
		{
			double factor = augmented[j][i];
			for (int k = 0; k < 2 * size; ++k)
			{
				augmented[j][k] -= augmented[i][k] * factor;
			}
		}
	}

	for (int i = size - 1; i >= 0; --i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			double factor = augmented[j][i];
			for (int k = 0; k < 2 * size; ++k)
			{
				augmented[j][k] -= augmented[i][k] * factor;
			}
		}
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			result[i][j] = augmented[i][size + j];
		}
	}

	for (int i = 0; i < size; ++i)
	{
		free(augmented[i]);
	}
	free(augmented);

	return 1;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Error: incorrect number of arguments\n");
		return 1;
	}
	FILE *f_input = fopen(argv[1], "r");
	FILE *f_output = fopen(argv[2], "w");

	int R, C;
	if (fscanf(f_input, "%d %d", &R, &C) != 2)
	{
		fprintf(stderr, "Error: Invalid matrix size\n");
		fclose(f_input);
		fclose(f_output);
		return 1;
	}

	if (R != C)
	{
		fprintf(f_output, "no_solution\n");
		fclose(f_input);
		fclose(f_output);
		return 0;
	}

	double **matrix = malloc(R * sizeof(double *));
	for (int i = 0; i < R; ++i)
	{
		matrix[i] = malloc(C * sizeof(double));
	}

	for (int i = 0; i < R; ++i)
	{
		for (int j = 0; j < C; ++j)
		{
			if (fscanf(f_input, "%lf", &matrix[i][j]) != 1)
			{
				fprintf(stderr, "Error: invalid matrix arguments\n");
				fclose(f_input);
				fclose(f_output);
				return 1;
			}
		}
	}

	double **result = (double **)malloc(R * sizeof(double *));
	for (int i = 0; i < R; ++i)
	{
		result[i] = (double *)malloc(C * sizeof(double));
	}

	if (reverse_matrix(matrix, R, result) == 0)
	{
		fprintf(f_output, "no_solution\n");
	}
	else
	{
		fprintf(f_output, "%d %d\n", R, C);
		for (int i = 0; i < R; ++i)
		{
			for (int j = 0; j < C; ++j)
			{
				fprintf(f_output, "%g ", result[i][j]);
			}
			fprintf(f_output, "\n");
		}
	}

	for (int i = 0; i < R; ++i)
	{
		free(matrix[i]);
		free(result[i]);
	}
	free(matrix);
	free(result);

	fclose(f_input);
	fclose(f_output);

	return 0;
}
