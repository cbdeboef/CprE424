#include "matrix.h"

/*
matrix create_random_matrix(int N);
matrix matrix_mult(const matrix* A, const matrix* B);
matrix matrix_mult_v2(const matrix* A, const matrix* B);
matrix new_matrix(const int rows, const int cols);
void delete_matrix(matrix* A);
typedef struct matrix matrix;
*/

int main(){

	int N;
	printf("input N:\n");
	scanf("%i",&N);
	assert(N > 0);

	matrix create_random_matrix(const int);
	matrix A = create_random_matrix(N);

	clock_t time0, time1, time2;
	
	time0 = clock();
	matrix A1 = matrix_mult(&A,&A);
	time1 = clock();
	matrix A2 = matrix_mult_v2(&A,&A);
	time2 = clock();

	double cpu_time1 = ((double)(time1 - time0))/((double)(CLOCKS_PER_SEC));
	double cpu_time2 = ((double)(time2 - time1))/((double)(CLOCKS_PER_SEC));
	
	printf("CPU time 1 = %11.5e\n",cpu_time1);
	printf("CPU time 2 = %11.5e\n",cpu_time2);



	delete_matrix(&A);
}

matrix create_random_matrix(int N){
//Get random NxN matrix
	assert(N > 1);
        matrix A = new_matrix(N,N);
        for(int i = 1; i <= N; i++){
                for(int j = 1; j <= i; j++){
                        double tmp = ((double)rand())/((double)RAND_MAX);
                        tmp = (double)((int)(10000.0 * tmp))/10000.0;
                        mget(A,i,j) = tmp;
                }
	}	
        return A;
}

/*
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
	delete_matrix(&Btranspose);
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
        for(int i = 1; i <= rowsA; i++){
                for(int j = 1; j <= colsB; j++){
                        mget(B_T,i,j) = mgetp(B,j,i);
                }
        }

        // Performs multiplication of matrix A and matrix B and stores value in matrix C
        for(int i = 1; i <= rowsA; i++){
                for(int j = 1; j <= colsB; j++){
                        for(int k = 1; k<= colsA; k++){
                                mget(C,i,j) += mgetp(A,i,k) * mget(B_T,j,k);
                        }
                }
        }

        return C;
}

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

void delete_matrix(matrix* A){
	free(A);
}

struct matrix{
                int rows;
                int cols;
                double* val;
};
*/
