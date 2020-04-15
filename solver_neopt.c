/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>


double* my_solver(int N, double *A, double* B) {
	double* C = (double*)malloc(N * N * sizeof(double)); 
	if(!C)
	{
		printf("Unable to allocate memory\n");
		return NULL;
	}

	double* At = (double*)malloc(N * N * sizeof(double));
	if(!At)
	{
		printf("Unable to allocate memory\n");
		free(C);
		return NULL;
	}

	double* A_2 = (double*)malloc(N * N * sizeof(double)); 
	if(!A_2)
	{
		printf("Unable to allocate memory\n");
		free(C);
		free(At);
		return NULL;
	}

	double* A2xB = (double*)malloc(N * N * sizeof(double)); 
	if(!A2xB)
	{
		printf("Unable to allocate memory\n");
		free(C);
		free(At);
		free(A_2);
		return NULL;
	}

	int i,j,k;

	//A transpus
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			At[(i*N) + j] = A[(j*N) + i]; 
	}

	// C = B * At
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			C[(i*N)+j] = 0; 
			for (k = 0; k < N; k++) 
				C[(i*N)+j] += B[(i*N)+k] * At[(k*N)+j]; 
		}
	}

	free(At);


	// A_2 = A * A
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			A_2[(i*N)+j] = 0; 
			for (k = 0; k < j + 1; k++) 
				A_2[(i*N)+j] += A[(i*N)+k] * A[(k*N)+j]; 
		}
	}

	// A2xB = A2 * B
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			A2xB[(i*N)+j] = 0; 
			for (k = 0; k < N; k++) 
				A2xB[(i*N)+j] += A_2[(i*N)+k] * B[(k*N)+j]; 
		}
	}

	free(A_2);
	
	//C = B * At + A2 * B
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			C[(i*N) + j] += A2xB[(i*N) + j];

	}	

	free(A2xB);


	return C;
}



