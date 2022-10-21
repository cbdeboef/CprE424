#include "matrix.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
        // call with <name> <threads> <colsA> <rowsA>
        // Computes for w in the equation w = Ax
        // A: Hilbert Matrix of size N x K
        // V: matrix of 1's of size 1 x K

        void usage(const char* prog_name);
        double matrixMult(int K, int currentRow, vector* V);

        if(argc != 4){ usage(argv[0]); }
        const int thread_count = strtol(argv[1], NULL, 10);
        const int N = strtol(argv[2], NULL, 10);
        const int K = strtol(argv[3], NULL, 10);

        if(thread_count < 1 || N < 1 || K < 1){ usage(argv[0]); }

        vector w = new_vector(K);
        vector V = new_vector(K);
        for(int i = 1; i <= K; i++){ vget(V,i) = 1; }

        const double time1 = omp_get_wtime();

#       pragma omp parallel num_threads(thread_count)
        {
                for(int i = 1; i <= N; i++){
                        vget(w,i) = matrixMult(K, i, &V);
                }
        }

        const double time2 = omp_get_wtime();

  	  delete_vector(&V);

        printf("\nWith %i threads, code ran in %12.5e seconds", thread_count, time2 - time1);

        return 0;
}

void usage(const char * prog_name ){
         fprintf(stderr ,"usage: %s <num_threads > <colsA > <rowsA>\n", prog_name );
         fprintf(stderr ," num_threads should be positive\n");
         fprintf(stderr ," rows and cols should be positive\n");
         exit (1);
}

double matrixMult(int K, int currentRow, vector* V){
        double product = 0;

        for(int i = 0; i < K; i++){
                product += (1 / (i + currentRow)) * vgetp(V,i+1);
        }

        return product;
}
