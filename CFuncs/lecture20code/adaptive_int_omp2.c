#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef _OPENMP
#	include <omp.h>
#endif

int main(int argc, char* argv[]){

	void usage(const char* prog_name);
	double adaptiveInt(const double a, const double b, const double TOL, char* filename, const int num_threads);
	double adaptiveIntSerial(const double a, const double b, const double TOL, char* filename);

	const int thread_count = strtol(argv[1], NULL, 10);
	const double TOL = strtod(argv[2], NULL);
	if(thread_count < 0 || TOL < 5.0e-16){
			usage(argv[0]);
	}

	const double a = -2.0;
	const double b = 4.0;

	char filename[36] = "quadrature.data";
	FILE* file = fopen(filename, "w");
	fclose(file);

	const double Iex = 0.4147421694070212;

	// allow for nested OpenMP
	omp_set_nested(1); omp_set_dynamic(0);

	// call adaptive integration recursively
	double I;
	if(thread_count == 1){
		I = adaptiveIntSerial(a, b, TOL, filename);
	}
	else{
		I = adaptiveInt(a, b, TOL, filename, thread_count);
	}

	// print data to screen
	printf("\n");
	printf("thread_count = %i\n", thread_count);
	printf("TOL = %24.15e\n", TOL);
	printf("I = %24.15e\n", I);
	printf("err = %24.15e\n", fabs(I-Iex));
	printf("\n");

	return 0;
}

void usage(const char *prog_name){
	fprintf(stderr, "usage: %s <num_threads> <TOL>\n", prog_name);
	fprintf(stderr, "num_threads should be positive\n");
	fprintf(stderr, "TOL should be positive\n");
	exit(1);
}

double adaptiveIntSerial(const double a, const double b, const double TOL, char* filename){
	double Q(const double a, const double b);
	double Qab = Q(a, b);
	const double c = 0.5 * (a+b);
	double Qac = Q(a, c);
	double Qcb = Q(c, b);
	const int my_rank = omp_get_thread_num();

	FILE* file = fopen(filename, "a");
	fprintf(file, "%3i %24.15e %24.15e\n", my_rank + 1, a, b);
	fclose(file);

	const double one_over_15 = 6.6666666666666666666666666666666667e-02;
	const double error_est = one_over_15 * fabs(Qac + Qcb - Qab);
	double result = 0.0;

	if(error_est < TOL){
		return Qac + Qcb;
	}
	else{
		result = AdaptiveIntSerial (a,c ,0.5* TOL , filename);
		result += AdaptiveIntSerial (c,b ,0.5* TOL , filename);
	}
	return result;
}

double AdaptiveInt (const double a, const double b, const double TOL, char* filename, const int num_threads){
	double Q(const double a, const double b);
        double Qab = Q(a, b);
        const double c = 0.5 * (a+b);
        double Qac = Q(a, c);
        double Qcb = Q(c, b);
        const int my_rank = omp_get_thread_num();
	
	FILE* file = fopen(filename, "a");
        fprintf(file, "%3i %24.15e %24.15e\n", my_rank + 1, a, b);
        fclose(file);

	const double one_over_15 = 6.6666666666666666666666666666666667e-02;
        const double error_est = one_over_15 * fabs(Qac + Qcb - Qab);
        double result = 0.0;

        if(error_est < TOL){
                return Qac + Qcb;
        }
        else{
                result = AdaptiveIntSerial (a,c ,0.5* TOL , filename);
                result += AdaptiveIntSerial (c,b ,0.5* TOL , filename);
        }
        return result;
}

double Q(const double a, const double b){
	double f(const double x);
	const double one_sixth = 1.666666666666666666666666666666666667e-01;
	const double c = 0.5 * (a+b);
	return one_sixth * (b-a) * (f(a) + 4.0 * f(c)+f(b));
}

double f(const double x){
	const double beta = 10;
	return exp(-pow(beta * x, 2)) + sin(x);
}
