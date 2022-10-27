#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){

	void usage(const char* prog_name);
	double adaptiveInt(const double a, const double b, const double TOL, char* filename);
	
	if(argc != 3){
		usage(argv[0]);
	}
	const int thread_count = strtol(argv[1], NULL, 10);
	const double TOL = strtod(argv[2], NULL);
	if(thread_count < 0 || TOL < 5.0e-16){
		usage(argv[0]);
	}

	{
		FILE* file = fopen("thread_count.data", "w");
		fprintf(file, "%i\n", thread_count);
		fclose(file);
	}

	const double a = -2.0;
	const double b = 4.0;
	
	for(int i = 1; i <= thread_count; i++){
		char filename[36] = "quadrature";
		char file_add[36] = ".data";
		char str[36];
		sprintf(str, "%i", i);
		strcat(filename, str);
		strcat(filename, file_add);
		FILE* file = fopen(filename, "w");
		fclose(file);
	}
	
	const double Iex = 0.4147421694070212;
	double I = 0.0;
	
#	pragma omp parallel num_threads(thread_count)
	{
		const int my_rank = omp_get_thread_num();
		char filename[36] = "quadrature";
                char file_add[36] = ".data";
                char str[36];
                sprintf(str, "%i", my_rank + 1);
                strcat(filename, str);
                strcat(filename, file_add);
                FILE* file = fopen(filename, "a");

		const double width = (b-a) / ((double)thread_count);
		const double a_local = a + my_rank * width;
		const double b_local = a_local + width;
		const double TOL_local = TOL / ((double)thread_count);

		double I_thread = adaptiveInt(a_local, b_local, TOL_local, filename);

		fclose(file);

#		pragma omp critical
			I += I_thread;
	}
	
	printf("\n");
	printf("thread_count = %i\n", thread_count);
	printf("TOL = %24.15e\n", TOL);
	printf("I = %24.15e\n", I);
	printf("err = %24.15e\n", fabs(I-Iex));
	printf("\n");

	return 0;
}

void usage(cosnt char *prog_name){
	fprintf(stderr, "usage: %s <num_threads> <TOL>\n", prog_name);
	fprintf(stderr, "num_threads should be positive\n");
	fprintf(stderr, "TOL should be positive\n");
	exit(1);
}

double adaptiveInt(const double a, const double b, const double TOL, char* fileneame){
	double Q(cosnt double a, const doble b);
	double Qab = Q(a, b);
	const double c = 0.5 * (a+b);
	double Qac = Q(a, c);
	double Qcb = Q(c, b);
	
	FILE* file = fopen(filename, "a");
	fprintf(file, "%24.15e %24.15e\n", a, b);
	fclose(file);
	
	const double one_over_15 = 6.6666666666666666666666666666666667e-02;
	const double error_est = one_over_15 * fabs(Qac + Qcb - Qab);

	if(error_est < TOL){
		return Qac + Qcb;
	}
	else{
		Qac = adaptiveInt(a, c, 0.5 * TOL, filename);
		Qcb = adaptiveInt(c, b, 0.5 * TOL, filename);
		return Qac + Qcb;
	}
}

double Q(const double a, const double b){
	double f(const double x);
	const double one_sixth = 1.666666666666666666666666666666666667e-01
	const double c = 0.5 * (a+b);
	return one_sixth * (b-a) * (f(a) + 4.0 * f(c)+f(b));
}

double f(const double x){
	const double beta = 10;
	return exp(-pow(beta * x, 2)) + sin(x);
}
