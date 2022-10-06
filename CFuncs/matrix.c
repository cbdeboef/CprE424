#include "matrix.h"

matrix new_matrix(const int rows, const int cols){
	
	// Set up matrix struct
	matrix mat;
	mat.rows = rows;
	mat.cols = cols;
	assert(rows>0); assert(cols>0);
	mat.val = (double*)malloc(sizeof(double)*rows*cols);
	
	// init matrix to 0s
	for(int i = 0; i < rows*cols; i++){
		mat.val[i] = 0.0;
	}

	return mat;
}

void print_matrix_full(const matrix* mat, char* varname){
        
	// Check matrix was input correctly
	assert(mat->rows>0); assert(mat->cols>0);
	
	// Scan through mat.val and print values in matrix form
	printf("\n %.100s = \n", &varname[1]);
	for(int i=1; i<= mat->rows; i++){
		printf("  |  ");
		for(int j = 1; j <= mat->cols; j++){
			printf("%10.3e", mgetp(mat,i,j));
			if(j < mat->cols){ printf(", "); }
			else{ printf(" ");}
		}
		printf("|\n");
	printf("\n");
	}
}

matrix matrix_add(const matrix* A, const matrix* B){

	const int rows = A->rows;
	const int cols = A->cols;
	assert(rows == B->rows); assert(cols == B->cols);
	matrix C = new_matrix(rows, cols);
	
	// Fetch values from each element of A and B and put their sum in C
	for(int i = 1; i <= rows; i++){
		for(int j = 1; j <= cols; j++){
			mget(C,i,j) = mgetp(A,i,j) + mgetp(B,i,j);
		}
	}

	return C;
}

matrix matrix_sub(const matrix* A, const matrix* B){

        const int rows = A->rows;
        const int cols = A->cols;
        assert(rows == B->rows); assert(cols == B->cols);
        matrix C = new_matrix(rows, cols);

        // Fetch values from each element of A and B and put their difference in C
        for(int i = 1; i <= rows; i++){
                for(int j = 1; j <= cols; j++){
                        mget(C,i,j) = mgetp(A,i,j) - mgetp(B,i,j);
                }
        }

        return C;
}

matrix matrix_mult(const matrix* A, const matrix* B){

	// Checks dimentions are compatible for multiplication
        const int rowsA = A->rows; const int rowsB = B->rows;
        const int colsA = A->cols; const int colsB = B->cols;
        assert(colsA == rowsB);
        matrix C = new_matrix(rowsA, colsB);

        // Performs multiplication of matrix A and matrix B and stores value in matrix C
        for(int i = 1; i <= rowsA; i++){
                for(int j = 1; j <= colsB; j++){
                        for(int k = 1; k<= colsA; k++){
                        	mget(C,i,j) += mgetp(A,i,k) * mgetp(B,k,j);
	                }
		}
        }

        return C;
}

matrix matrix_mult_v2(const matrix* A, const matrix* B){
	
        // Checks dimentions are compatible for multiplication
        const int rowsA = A->rows; const int rowsB = B->rows;
        const int colsA = A->cols; const int colsB = B->cols;
        assert(colsA == rowsB);
        matrix C = new_matrix(rowsA, colsB);
	
	// Create 
	matrix B_T = new_matrix(rowsB, colsB);
	for(int i = 0; i <= rowsA; i++){
		for(int j = 0; j <= colsB; j++){
			mget(B_T,i,j) = mgetp(B,j,i);
		}
	}

        // Performs multiplication of matrix A and matrix B and stores value in matrix C
        for(int i = 1; i <= rowsA; i++){
                for(int j = 1; j <= colsB; j++){
                        for(int k = 1; k<= colsA; k++){
                                mget(C,i,j) += mgetp(A,i,k) * mgetp(B_T,j,k);
                        }
                }
        }

        return C;
}

matrix matrix_dot_mult(const matrix* A, const matrix* B){

        const int rows = A->rows; 
        const int cols = A->cols;
        assert(rows == B->rows); assert(cols == B->cols);
        matrix C = new_matrix(rows, cols);

        // Fetch values from each element of A and B and put their product in C
        for(int i = 1; i <= rows; i++){
                for(int j = 1; j <= cols; j++){
                        mget(C,i,j) = mgetp(A,i,j) * mgetp(B,i,j);
                }
        }

        return C;
}

vector new_vector(const int size){

	// Declare and allocate mem for vector
	vector vec;
	vec.size = size;
	assert(size > 0);
	vec.val = (double*)malloc(sizeof(double)*size);
	
	// initalize vector values to 0
	for(int i = 0; i < (size); i++){
		vec.val[i] = 0.0;
	}
	return vec;
}

void print_vector_full(const vector* vec, char* varname){

	assert(vec->size > 0);
	printf("\n");
	printf(" %.100s =\n", &varname[1]);
	printf("  |  ");
	for(int i = 1; i <= vec->size; i++){
		printf("%10.3e", vgetp(vec,i));
		if(i < vec->size) {printf(", "); }
	}
	printf(" |^T\n\n");
}

vector vector_add(const vector* x, const vector* y){
	
	// Create new vector z to be returned
	const int size = x->size;
	assert(size == y->size);
	vector z = new_vector(size);

	// Add each element from x and y and store them in z
	for(int i = 1; i <= size; i++){
		vget(z,i) = vgetp(x,i) + vgetp(y,i);
	}

	return z;
}

vector vector_sub(const vector* x, const vector* y){

        // Create new vector z to be returned
        const int size = x->size;
        assert(size == y->size);
        vector z = new_vector(size);

        // Add each element from x and y and store them in z
        for(int i = 1; i <= size; i++){
                vget(z,i) = vgetp(x,i) - vgetp(y,i);
        }

        return z;
}

double vector_dot_mult(const vector* x, const vector* y){

        // Create output var z and save vector size
        const int size = x->size;
        assert(size == y->size);
        double z = 0;

        // Sum the product of each element in x and y
        for(int i = 1; i <= size; i++){
                z += vgetp(x,i) * vgetp(y,i);
        }

        return z;
}

void print_scalar_full(const double* z, char* varname){

	printf("\n %.100s =\n", &varname[1]);
	printf("    %10.3e \n\n", *z);
}

vector matrix_vector_mult(const matrix* A, const vector* x){
	
	// Declare sizes of arrays and create output vector Ax
	const int rows = A->rows;
	const int cols = A->cols;
	const int size = x->size;
	assert(cols == size);
	vector Ax = new_vector(rows);
	
	// compute Ax=b and output b
	for(int i = 1; i <= rows; i++){
		double tmp = 0.0;
		for(int j = 1; j <= size; j++){
			tmp += mgetp(A,i,j) * vgetp(x,j);
		}
		vget(Ax,i) = tmp;
	}
	return Ax;
}

vector solve(const matrix* A, const vector* b){

	// Create output vector x and size arguments from inputs
	const int rows = A->rows;
	const int cols = A->cols;
	const int size = b->size;
	assert(rows == cols); assert(rows == size);
	vector x = new_vector(rows);

	for(int i = 1; i <= (size-1); i++){
		int p = i; 
		double maxA = -100.0e0;
		for(int j = i; j <= size; j++){
			double tmp = fabs(mgetp(A,j,i));
			if(tmp > maxA){ p = j; maxA = tmp; }
		}
		if(maxA <= 1.0e-14){
			printf("Cannot invert System\n");
			exit(1);
		}
		if(p != i){
			for(int j = 1; j <= size; j++){
				double tmp1 = mgetp(A,i,j);
				mgetp(A,i,j) = mgetp(A,p,j);
				mgetp(A,p,j) = tmp1;
			}
			double tmp2 = vgetp(b,i);
			vgetp(b,i) = vgetp(b,p);
			vgetp(b,p) = tmp2;

		}
		for(int j = (i+1); j <= size; j++){
			double dm = mgetp(A,j,i)/mgetp(A,i,i);
			for(int k = 1; k <= size; k++){
				mgetp(A,j,k) = mgetp(A,j,k) - dm * mgetp(A,i,k);
			}
			vgetp(b,j) = vgetp(b,j) - dm * vgetp(b,i);
		}
	}
	vget(x,size) = vgetp(b,size) / mgetp(A,size,size);
	for(int j = 1; j <= (size-1); j++){
		double sum = 0.0e0;
		for(int k = (size-j+1); k <= size; k++){
			sum = sum + mgetp(A,size-j,k) * vget(x,k);
		}
		vget(x,size-j) = (vgetp(b,size-j) - sum) / mgetp(A,size-j, size-j);
	}
	return x;
}

double vector_mag(const vector b){

	// Find abs(b)^2
	double x = vector_dot(b, b);

	// Square root to find abs(b)
	x = sqrt(x);
	
	return x;
}

vector vector_scalar_mult(vector b, double x){

	for(int i = 1; i <= b.size; i++){
		vget(b,i) = x * vget(b,i);
	}
}

matrix vector_transpose(const vector x){
	
	matrix x_T = new_matrix(x.size,1);
	
	for(int i = 1; i <= x.size; i++){
		mget(x_T,i,1) = vget(x,1);
	}
	return x_T;
}

double eigen_power_iteration(matrix A, vector v, double tol, int maxIters){
	
	// v(0) = v(0) / ||v(0)|| (normalized)
	v = vector_scalar_mult(v,1 / (vector_transpose(b)));
	
	// lambda = v_T A v (initialize lambda
	lambda = vector_dot_mult(v, matrix_vector_mult(A, v));

	// Set loop conditions
	int mstop = 0;
	int k = 0;

	while(mstop == 0){
		// w = Av
		vector w = matrix_vector_mult(A, v);
		
		// v = v / ||v||
		v = vector_scalar_mult(w,1 / (vector_transpose(w)));
		
		// lambda = v_T A v
		double lambdaOld = lambda;
		lambda = vector_dot_mult(v, matrix_vector_mult(A, v));
		
		if(((lambda - lambdaOld) < TOL) | k == MaxIters){ mstop = 1; }
	}	
	return lambda;
}

