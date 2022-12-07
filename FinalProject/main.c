#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char* argv[]){
// This code's purpose is to compute the discrete fourier transform of a set of numbers, input either by the user for smaller lengths or using a txt file.
// It will run a python script to print out the data as a graph with proper labels and with the speedup of MPI it should perform better than matlab for the
// purposes I want to use it for. 
	printf("got into main");	
	// Declare functions
	void usage(const char* prog_name);
	void get_input(int argc, char* argv[], const int my_rank, const int comm_sz, int* N);


	// setup MPI code
	int comm_sz, my_rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


	// Get inputs and declare outputs
	int N;
	get_input(argc, argv, my_rank, comm_sz, &N);
	
	double X_real[N];
	double X_imag[N];
	double X_mag[N];

	int N_local = N / comm_sz;

	double time_start;
	if(my_rank == 0){ time_start = MPI_Wtime(); }
	
	double x_local[N];
	double X_local_real[N_local];
	double X_local_imag[N_local];
	double X_local_mag [N_local];

	//Create Input Signal(s)

//        // init x to be cosine with omega = 3/16
//        for(int i = 0; i < N; i++){
//                x_local[i] = cos(3.0/8 * M_PI * i);
//        }

        // init x to be a square wave
        for(int i = 0; i < N/2; i++){
                x_local[i] = 1;
        }
        for(int i = 0; i < N/2; i++){
                x_local[i + N/2] = 0;
        }	



	for(int k = 0; k < N_local; k++){
		for(int n = 0; n < N_local; n++){
			X_local_real[k] += x_local[n] * cos(2 * M_PI * k * n / N);
			X_local_imag[k] += x_local[n] * sin(2 * M_PI * k * n / N);
		}
		X_local_mag[k] = sqrt(pow(X_local_real[k],2) + pow(X_local_imag[k],2));
	}	
	
	if(my_rank != 0){
		MPI_Send(X_local_real, 2, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	else{
		for(int i = 0; i < N_local; i++){
			X_real[i] = X_local_real[i];
			X_imag[i] = X_local_imag[i];
			X_mag [i] = X_local_mag[i];
		}
		for(int i = 0; i < comm_sz; i++){
			MPI_Recv(X_local_real, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			for(int j = 0; j < N_local; j++){
				X_real[j + i * N_local] = X_local_real[i];
        	                X_imag[j + i * N_local] = X_local_imag[i];
                	        X_mag [j + i * N_local] = X_local_mag[i];
			}
		}
	}

	if(my_rank == 0){
		double time_end = MPI_Wtime();
		double time_elapsed = time_end - time_start;
		printf("NP = %2i, N = %i", comm_sz, N);
		printf("Time Elapsed: %20.13e\n", time_elapsed);
	}
	MPI_Finalize();
	return 0;
}

void usage(const char *prog_name){
	fprintf(stderr, "usage: %s <N>/n",prog_name);
	fprintf(stderr, "N shoudl be positive/n");
	fprintf(stderr, "N should be exactly divisible by the number of processors");
	exit(1);
}

void get_input(int argc, char* argv[], const int my_rank, const int comm_sz, int* N){
	void usage(const char *prog_name);
	if (my_rank==0){
		if (argc != 2) { usage(argv[0]); }

		*N = strtol(argv[1], NULL, 10);
		if (*N<=0) { usage(argv[0]); }
		if (*N%comm_sz!=0) { usage(argv[0]); }
            
		for (int i=1; i<comm_sz; i++){
			MPI_Send(N,1,MPI_INT,   i,0,MPI_COMM_WORLD);
      		}
	}
	else{
		MPI_Recv(N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
}
