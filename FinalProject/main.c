#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char* argv[]){
// This code's purpose is to compute the discrete fourier transform of a set of numbers, input either by the user for smaller lengths or using a txt file.
// It will run a python script to print out the data as a graph with proper labels and with the speedup of MPI it should perform better than matlab for the
// purposes I want to use it for. 

	// setup MPI code
	int comm_sz, my_rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	// 


	void usage(const char* prog_name);
	

