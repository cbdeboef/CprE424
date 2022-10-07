#include "matrix.h"

int main(){
	
	// create matrix A
	matrix A = new_matrix(3, 3);
        A.val = (double[9]) {3,2,4,2,0,2,4,2,3};
	
	// create vector b to help guess eigenvalues
        vector v = new_vector(3);
        v.val = (double[3]) {1,2,3};
	
	// Find eigenvalue closest to 2
        double lambda = eigen_shifted_inv_function(A, v, 5, 0.00000001, 10000);

        printf("%lf", lambda);

        return 0;
}
