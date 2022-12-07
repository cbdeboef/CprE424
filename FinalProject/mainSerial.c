#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char* argv[]){
// This code's purpose is to compute the discrete fourier transform of a set of numbers, input either by the user for smaller lengths or using a txt file.
// It will run a python script to print out the data as a graph with proper labels and with the speedup of MPI it should perform better than matlab for the
// purposes I want to use it for.


        // Get inputs and declare outputs
	FILE *fp_in = fopen("inputData.txt", "r");

        int N = strtol(argv[1], NULL, 10);

        double x[N];
        double X_real[N];
        double X_imag[N];
        double X_mag[N];

	// Get data from txt file
	for(int i = 0; i < N; i++){
                fscanf(fp_in, "%lf", &x[i]);
//              printf("%lf\n",x[i]);
        }
        fclose(fp_in);


        clock_t time_start = clock();

//        // init x to be cosine with omega = 3/16
//        for(int i = 0; i < N; i++){
//                x[i] = cos(3.0/8 * M_PI * i);
//        }

//	// init x to be a square wave
//	for(int i = 0; i < N/2; i++){
//		x[i] = 1;
//	}
//	for(int i = 0; i < N/2; i++){
//		x[i + N/2] = 0;
//	}

        for(int k = 0; k < N; k++){
                for(int n = 0; n < N; n++){
                        X_real[k] += x[n] * cos(2.0 * M_PI * k * n / N);
                        X_imag[k] += x[n] * sin(2.0 * M_PI * k * n / N);
                }
                X_mag[k] = sqrt(pow(X_real[k],2) + pow(X_imag[k],2));
//		printf("%d    %lf\n", k, X_mag[k]);
        }
        clock_t time_end = clock();
	
	for(int i = 0; i < N; i++){
                printf("%d    %lf\n", i, X_mag[i]);
        }
	
	char *filename = "outputDataSerial.txt";
        FILE *fp = fopen(filename, "w");
        if(fp == NULL){ printf("error"); return -1; }
        for(int i = 0; i < N; i++){
                fprintf(fp, "%d\t%lf\t%lf\t%lf\n",i,X_real[i], X_imag[i], X_mag[i]);
        }
        fclose(fp);	

        printf("time elapsed = %lf\n", ((double) (time_end - time_start)) / CLOCKS_PER_SEC);

        return 0;
}
