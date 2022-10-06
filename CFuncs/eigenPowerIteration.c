#include "matrix.h"

int main(){
	
	// Delclare matrix A
	matrix A = new_matrix(3, 3);
        A.val = (double[9]) {3,2,4,2,0,2,4,2,3};

	vector v = new_vector(3);
	v.val = (double[3]) {1,1,1};

	double lambda = eigen_power_function(A, v, 0.001, 100);
        
	printf("%lf", lambda);
	
	return 0;
}
