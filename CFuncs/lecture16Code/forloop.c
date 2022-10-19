#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include <math.h>
#include <omp.h>


int main(int argc, char* argv[]){
	void usage(const char* prog_name);

	if(argc != 3) { usage(argv[0]); }
	const int thread_count = strtol(argv[1], NULL, 10);
	const int N = strtol(argv[2], NULL, 10);
	if(thread_count <= 0) { usage(argv[0]); }

	srand( time(NULL) );
	matrix m = new_matrix(N,N);

	const double time1 = omp_get_wtime();

#	pragma omp oparallel for num_threads(thread_count)
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			mget(m,i,j) = 1.0 / (i + j - 1);
		}
	}

	const double time2 = omp_get_wtime();
	const double clock_time = time2 - time1;

	printf("with %i threads, clock time = %11.5e (sec)\n", thread_count, clock_time);

	delete_matrix(&m);
	return 0;
}

void usage(const char *prog_name){
	fprintf(stderr, "usage: %s <thread_count> <matrix size>\n", prog_name);
	fprintf(stderr, " Thread_count should be positive\n");
	fprintf(stderr, "N should be posiitve\n");
	exit(1);
}
