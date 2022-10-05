#include "matrix.h"

int main(){

	matrix A = new_matrix(3, 3);
	matrix B = new_matrix(3, 3);

	A.val = (double[9]) {-2,0,1,-1,7,1,5,-1,1};
	B.val = (double[9]) {12,10,6,7,2,4,9,1,1};
	
	print_matrix(&A);
	print_matrix(&B);

	matrix Csum  = matrix_add(&A, &B);
	print_matrix(&Csum);
	matrix Cdif  = matrix_sub(&A, &B);
	print_matrix(&Cdif);
	matrix Cprod = matrix_mult(&A, &B);
	print_matrix(&Cprod);
	matrix Cdot  = matrix_dot_mult(&A, &B);
	print_matrix(&Cdot);

	vector x = new_vector(3);
	vector y = new_vector(3);

	vget(x,1) = -4;  vget(y,1) = 4;
	vget(x,2) = -50; vget(y,2) = 2;
	vget(x,3) = -26; vget(y,3) = 3;

	print_vector(&x);
	print_vector(&y);

	vector zsum = vector_add(&x, &y);
	print_vector(&zsum);
	vector zdiff = vector_sub(&x, &y);
	print_vector(&zdiff);
	double zdot = vector_dot_mult(&x, &y);
	print_scalar(&zdot);

	vector Ay = matrix_vector_mult(&A, &y);
	print_vector(&Ay);

	vector soln = solve(&A, &x);
	print_vector(&soln);

	return 0;
}
