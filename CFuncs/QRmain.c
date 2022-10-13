#include "trimatrix.h"

int main(){
	// initialize random vars and get dimention input
	srand( time(NULL) );
	int N = 0;
	printf("	Input N: ");
	scanf("%i",&N);

	assert(N > 1);

	//Get random NxN matrix
	matrix A = new_matrix(N,N);
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= i; j++){
			double tmp = ((double)rand())/((double)RAND_MAX);
			tmp = (double)((int)(10000.0 * tmp))/10000.0;
			mget(A,i,j) = tmp;
		}
	}
	
	// Make matrix symetric
	for(int i = 1; i <= (N-1); i++){
		for(int j = (i + 1); j <= N; j++){
			mget(A,i,j) = mget(A,j,i);
		}
	}

	// Hessenberg Reduction
	trimatrix T = new_trimatrix(N);
	void hessenberg(const matrix* Ain, trimatrix* T);
	double time1 = clock();
	hessenberg(&A, &T);
	double time2 = clock();

	// Print out origianl and reduced matrix
	printf("\n");
	printf("Original Matrix:\n");
	print_matrix(&A);
	printf("Redcution to Tridiagonal Form:\n");
	print_trimatrix(&T);

	// Perform QR algorithm to find eigenvalues and print out matrix
	void QRA(trimatrix* T);
	double time3 = clock();
	QRA(&T);
	double time4 = clock();
	printf("After QR Algorithm:\n");
	print_trimatrix(&T);

	printf("hessenburg time is: %11.5e\n",((double)(time2 - time1))/((double)(CLOCKS_PER_SEC)));
	printf("QR algorithm time is: %11.5e\n",((double)(time4 - time3))/((double)(CLOCKS_PER_SEC)));

	return 0;
}
