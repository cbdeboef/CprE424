#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#ifdef _OPENMP
	#include <omp.h>
#endif

int main(int argc, char* argv[]){
// This code's purpose is to compute the discrete fourier transform of a set of numbers, input either by the user for smaller lengths or using a txt file.
// a python script will run to print out the data as a graph with proper labels and with the speedup of OpenMP it should perform better than matlab for the
// purposes I want to use it for.
	
	// Open Input Data File for read
        FILE *fp_in = fopen("inputData.txt", "r");

	// Get data length (Passed in as argument for easy truncation of data)
	int N = strtol(argv[2], NULL, 10);

        // Declare inputs and outputs
	double x[N];
        double X_real[N];
        double X_imag[N];
        double X_mag[N];
	
	// Fill x array with input and initialize Output arrays
	for(int i = 0; i < N; i++){
		fscanf(fp_in, "%lf", &x[i]);
		X_real[i] = 0.0;
		X_imag[i] = 0.0;
	}
	fclose(fp_in);

	// Start Time for speedup check
        double time_start = omp_get_wtime();
		
	// Begin Paralelisation of for loop
	#pragma omp parallel for num_threads(strtol(argv[1], NULL, 10))
	for(int k = 0; k < N; k++){
                for(int n = 0; n < N; n++){
                        X_real[k] += x[n] * cos(2.0 * M_PI * k * n / N);
                        X_imag[k] += x[n] * sin(2.0 * M_PI * k * n / N);
                }
                X_mag[k] = sqrt(pow(X_real[k],2) + pow(X_imag[k],2));
        }
	
	// End time
	double time_end = omp_get_wtime();
	
	// Fill outputDataOpenMP.txt with the input, real component, imaginary component, and magnitude 
	char* filename = "outputDataOpenMP.txt";
	FILE *fp = fopen(filename, "w");	
	if(fp == NULL){ printf("error"); return -1; }
	for(int i = 0; i < N; i++){
		fprintf(fp, "%d\t%lf\t%lf\t%lf\n",i,X_real[i], X_imag[i], X_mag[i]);
	}
	fclose(fp);
	
	// Print elapsed time
	printf("time elapsed = %lf\n", (time_end - time_start));

        return 0;
}
