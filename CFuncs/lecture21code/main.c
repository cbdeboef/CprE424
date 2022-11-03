#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include "matrix.h"

int main(int argc, char* argv []){

	// Setup MPI code
	int comm_sz;
	int my_rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	double a, b, global_T, error;
	int N;
	void get_input(int argc, char* argv[], const int my_rank, const int comm_sz, double* a, double* b, int* N);
	get_input(argc, argv, my_rank, comm_sz, &a, &b, &N);
	
	// Get time
	double time_start;
	if(my_rank == 0){
		time_start = MPI_Wtime();
	}
	else{ time_start = 0; }	

	// Run local trapezoidal rule
	const double h = (b-a) / ((double)N);
	const int local_N = N / comm_sz;
	const double local_a = a + ((double)(my_rank * local_N)) * h;
	const double local_b = local_a + ((double)local_N) * h;
	double compTrap(const double a, const double b, const int N, const double h);
	double local_T = compTrap(local_a, local_b, local_N, h);

	// Add local results to the global result on processor 0
	if(my_rank != 0){
		MPI_Send(&local_T, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	else{
		global_T = local_T;
		for(int i = 1; i < comm_sz; i++){
			MPI_Recv(&local_T, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			global_T += local_T;
		}
		const double Tex = exp(b) - exp(a);
		error = fabs(Tex - global_T) / fabs(Tex);
	}
	
	if(my_rank == 0){
		double time_end = MPI_Wtime();
		double time_elapsed = time_end - time_start;
		printf("NP = %2i, N = %i, T = %20.13e, |T-Tex| / |Tex| = %20.13e\n", comm_sz, N, global_T, error);
		printf("Elapsed time = %20.13e\n", time_elapsed);
	}

	// End program
	MPI_Finalize();
	return 0;
}

void get_input(int argc, char* argv[], const int my_rank, const int comm_sz, double* a, double* b, int* N){
	void usage(const char* prog_name);
	if(my_rank == 0){
		if(argc != 4){ usage(argv[0]); }

		*a = strtod(argv[1], NULL);
		*b = strtod(argv[2], NULL);
		*N = strtol(argv[3], NULL, 10);
		if(*N <= 0) {usage(argv[0]); }
		if(*N%comm_sz != 0){ usage(argv[0]); }

		for(int i = 1; i < comm_sz; i++){
			MPI_Send(a, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			MPI_Send(b, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			MPI_Send(N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	}
	else{
		MPI_Recv(a, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(b, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
}

void usage(const char* prog_name){
	fprintf(stderr, "usage : %s <N >\n", prog_name);
	fprintf(stderr, "N should be positive \n");
	fprintf(stderr, "N should be exactly divisible by the number of processors \n");
	exit (1);
}

double compTrap(const double a, const double b, const int N, const double h){
	double func(const double x);
	double T = 0.5 * (func(a) + func(b));
	for(int i = 1; i < N; i++){
		T += func(a + ((double)i) * h);
	}

	return h * T;
}

double func(const double x){
	return exp(-pow(10*x,2)) + sin(x);
}
