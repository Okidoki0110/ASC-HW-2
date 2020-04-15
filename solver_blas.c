/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

#include "cblas.h"


double* my_solver(int N, double *A, double *B) {
	double* C = (double*)malloc(N * N * sizeof(double)); 
	if(!C)
	{
		printf("Unable to allocate memory\n");
		return NULL;
	}

	double* A_2 = (double*)malloc(N * N * sizeof(double)); 
	if(!A_2)
	{
		printf("Unable to allocate memory\n");
		free(C);
		return NULL;
	}

	double* A2xB = (double*)malloc(N * N * sizeof(double)); 
	if(!A2xB)
	{
		printf("Unable to allocate memory\n");
		free(C);
		free(A_2);
		return NULL;
	}

	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1, B, N, A, N, 0, C, N);
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, A, N, A, N, 0, A_2, N);
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, A_2, N, B, N, 0, A2xB, N);

	free(A_2);

	int i,j;
	for(i=0; i<N; i++)
	{
		double* current_column_C = C + (N*i);
		double* current_column_A2xB = A2xB + (N*i);

		for(j=0; j<N; j++)
			current_column_C[j] += current_column_A2xB[j];

	}	

	free(A2xB);	

	return C;
}



