#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calcPoly(int N, double b[], double pts[], int numPts, double* y);
void writePolly(int numPts, double pts[], double y[]);

int main(){
	
	const int Nmax = 5;
	int N;
	
	printf("\nInput polynomial degree 0-%i", Nmax);
	scanf("%i", &N);
	
	if((N < 0) || (N > Nmax)){
		printf("\nInvalid Value");
		exit(1);
	}
	
	double b[N];
	int i;
	for(i = 0; i < N; i++){
		printf("Set b[%i]\n", i);
		scanf("%i", &b[i]);
	}
	
	int numPts = 200;
	double pts[numPts - 1];
	
	for(i = 0; i < numPts; i++){
		pts[i] = i / numPts - 1;
	}
	
	double y[numPts]; 
	calcPoly(N, b, pts, numPts, y);
	
	writePolly(numPts, pts, y);
	
//	system("python3 plotPoly.py");
	
	return 0;	
}

void calcPoly(int N, double b[], double pts[], int numPts, double* y){
	int i;
	double phi;
        int k;
	for(i = 0; i < numPts; i++){
		float x = pts[i];	
		for(k = 0; k < N; k++){
			if(k == 0){ phi = 1;}
			else if(k == 1){ phi = x;}
			else if(k == 2){ phi = 2 * pow(x,2) - 1;}
			else if(k == 3){ phi = 4 * pow(x,3) - 3 * x;}
			else if(k == 4){ phi = 8 * pow(x,4) - 8 * pow(x,2) + 1;}
			else if(k == 5){ phi = 16 * pow(x,5) - 20 * pow(x,3) + 5 * x;}
			
			y[i] += b[k] * phi;	
		}
	}
}
void writePolly(int numPts, double pts[], double y[]){
	FILE *fptr;
printf("\n1\n");
	int i;
	fptr = fopen("U:/CprE424/chebychev1.txt","w+");
printf("\n2\n");
	for(i = 0; i<numPts; i++){
		fprintf(fptr,"%Lf	%Lf\n", pts[i],y[i]);
	}
printf("\n3\n");
	fclose(fptr);
}
