#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

int main(){
	int N = 0; int stride = 0;
	printf("Input N:"); 
	scanf("%i", &N);
	printf("Input stride:"); 
	scanf("%i", &stride);
	assert(N > 0); assert(stride > 0); assert(stride <= N);

	matrix A = new_matrix(N,N);
	matrix B = new_matrix(N,N);

	
	while(stride <= N && N%stride != 0){
		stride = stride + 1;
	}

	printf("N = %i\n", N);
	printf("stride = %i\n", stride);

	// Stride 1 access
	clock_t time0 = clock();
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			mget(B,j,i) = mget(A,i,j);
		}
	}

	clock_t time1 = clock();

	// Stride "stride" access (version 1)
	for (int ii = 1; ii < N; ii += stride){
		for (int i = ii; i < ii+stride; i++){
			for (int jj = 1; jj < N; jj += stride){
				for (int j = jj; j < jj+stride; j++){
					mget(B,j,i) = mget(A,i,j);
				}
			}
		}
	}

	clock_t time2 = clock ();

	// Stride "stride" access (version 2)
	for (int ii = 1; ii < N; ii += stride){
		for (int jj = 1; jj < N; jj += stride){
			for (int i = ii; i < ii+stride; i++){
				for (int j = jj; j < jj+stride; j++){
					mget(B,j,i) = mget(A,i,j);
				}
			}
		}
	}

	clock_t time3 = clock ();

	// Report times
	double cpu_time1 = ((double)(time1 - time0)) / ((double)(CLOCKS_PER_SEC));
	double cpu_time2 = ((double)(time2 - time1)) / ((double)(CLOCKS_PER_SEC));
	double cpu_time3 = ((double)(time3 - time2)) / ((double)(CLOCKS_PER_SEC));
	printf("cpu_time1 = %11.5e\n", cpu_time1);
	printf("cpu_time2 = %11.5e\n", cpu_time2);
	printf("cpu_time3 = %11.5e\n", cpu_time3);

	delete_matrix (&A);
	delete_matrix (&B);
}
