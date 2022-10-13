#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

typedef struct matrix matrix;
struct matrix{
	int rows;
	int cols;
	double* val;
};
typedef struct vector vector;
struct vector{
	int size;
	double* val;
};

// Define macros for future use

#define mget(mat,i,j) mat.val[(i-1)*mat.cols+(j-1)]
#define mgetp(mat,i,j) mat->val[(i-1)*mat->cols+(j-1)]
#define vget(vec,i) vec.val[(i-1)]
#define vgetp(vec,i) vec->val[(i-1)]
#define print_matrix(mat) print_matrix_full(mat,#mat);
#define print_vector(vec) print_vector_full(vec,#vec);
#define print_scalar(z) print_scalar_full(z,#z);

// Declare function prototypes

matrix new_matrix(const int rows, const int cols);
void print_matrix_full(const matrix* mat, char* varname);
matrix matrix_add(const matrix* A, const matrix* B);
matrix matrix_sub(const matrix* A, const matrix* B);
matrix matrix_mult(const matrix* A, const matrix* B);
matrix matrix_mult_v2(const matrix* A, const matrix* B);
matrix matrix_dot_mult(const matrix* A, const matrix* B);

vector new_vector(const int size);
void print_vector_full(const vector* vec, char* varname);
vector vector_add(const vector* x, const vector* y);
vector vector_sub(const vector* A, const vector* B);
double vector_dot_mult(const vector* A, const vector* B);
vector vector_scalar_mult(vector b, double x);
double vector_mag(const vector b);

void print_scalar_full(const double* z, char* varname);

vector matrix_vector_mult(const matrix* A, const vector* x);

vector solve(const matrix* A, const vector* b);

double eigen_power_function(matrix A, vector b, double tol, int maxIters);
double eigen_shifted_inv_function(matrix A, vector b, double mu, double tol, int maxIters);

matrix vector_transpose(const vector x);

void delete_vector(vector* V);
void delete_matrix(matrix* M);

#endif
