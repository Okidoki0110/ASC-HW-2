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


	// C = B * At
	register double* B_p = B;
	register double* C_p = C;
 
	register int i,j,k;

	for(i=0; i<N; i++)
	{
	
		register double* A_p = A;
		register double* C_pt = C_p;

		for(j=0; j<N; j++)
		{
			register double result = 0; 
			register double* B_pt = B_p;
			register double* A_pt = A_p;

			for (k = 0; k < N; k++) 
			{
				
				result += (*B_pt) * (*A_pt); 
				
				A_pt++;
				B_pt++;
			}
		
			A_p += N;
			*C_pt = result;
			C_pt++;

		}
		
		B_p += N;
		C_p += N;
	}


	// A_2 = A * A
	register double* A_p = A;
	register double* A2_p = A_2;

	for(i=0; i<N; i++)
	{
		register double* A2_pt = A2_p;

		for(int j=0; j<N; j++)
		{
			register double result = 0; 
			register double* A_pt = A_p;
			register double* And_pt = A + j;

			for (k = 0; k < j + 1; k++) 
			{
				result += (*A_pt) * (*And_pt); 

				A_pt++;
				And_pt+=N;
			}

			*A2_pt = result;
			A2_pt++;
		}

		A_p += N;
		A2_p += N;
	}

	// A2xB = A2 * B
	A2_p = A_2;
	register double* A2xB_p = A2xB;
	for(i=0; i<N; i++)
	{
		register double* A2xB_pt = A2xB_p;

		for(j=0; j<N; j++)
		{
			register double result = 0;
			
			register double* A2_pt = A2_p;
			register double* B_pt = B + j;			

			for (k = 0; k < N; k++) 
			{
				result += (*A2_pt) * (*B_pt);
				
				A2_pt++; 
				B_pt += N;
			}

			*A2xB_pt = result;
			A2xB_pt++; 
		}

		A2_p += N;
		A2xB_p += N;
	}

	free(A_2);
	
	//C = B * At + A2 * B
	C_p = C;
	A2xB_p = A2xB;

	for(i=0; i<N*N; i++)
	{
		*C_p += *A2xB_p;

		C_p++;
		A2xB_p++;
	}	

	free(A2xB);

	return C;
}
