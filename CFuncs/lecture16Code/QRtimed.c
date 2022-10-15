#include "trimatrix.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"

int main(){
	srand( time(NULL) );
	int N = 100;

	// Create a random symetric matrix
	matrix A = new_matrix(N,N);
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= i; j++){
			double tmp = ((double)rand())/((double)RAND_MAX);
			tmp = (double)((int)(10000.0*tmp))/10000.0;
			mget(A,i,j) = tmp;
		}
	}
	for(int i = 1; i <= (N-1); i++){
		for(int j = (i+1); j <= N; j++){
			mget(A,i,j) = mget(A,j,i);
		}
	}
	
	// initialize functions
	void QRA(trimatrix* T);
	void Hessenberg(const matrix*A, trimatrix*T);

	trimatrix T = new_trimatrix(N);

	double time1 = clock();
	Hessenberg(&A,&T);
	double time2 = clock();
	QRA(&T);
	double time3 = clock();
	printf("\n Eigenvalues of A:\n");

	for(int i = 1; i <= N; i++){
		printf(" lambda(%3i) = %24.16e\n",i,tget(&T,i,i));
	}
	printf("\n");
	printf("Hessenberg time is: %11.5e\n", ((double)(time2 - time1))/((double)(CLOCKS_PER_SEC)));
	printf("QRA time is: %11.5e\n", ((double)(time3 - time2))/((double)(CLOCKS_PER_SEC)));
	return 0;
}
