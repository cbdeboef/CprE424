#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calcPoly(int N, double b[], double pts[], int numPts, double* y);
void writePolly(int numPts, double pts[], double y[]);

int main(){
	
	const int Nmax = 5;
	int N;
	
	printf("\nInput polynomial degree 0-%i\n", Nmax);
	scanf("%d", &N);
	
	if((N < 0) || (N > Nmax)){
		printf("\nInvalid Value");
		exit(1);
	}
	
	double b[N];
	int i;
	for(i = 0; i <= N; i++){
		printf("Set b[%d]\n", i);
		scanf("%lf", &b[i]);
	}
	
	int numPts = 200;
	double pts[numPts];
	
	for(i = 0; i < numPts; i++){
		pts[i] = i / 100.0 - 1.0;
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
		y[i] = b[0];
		double x = pts[i];
		for(k = 1; k <= N; k++){
			switch(k){
				case 1:
					phi = x; break;
				case 2:
					phi = 2 * pow(x,2) - 1; break;
				case 3:
					phi = 4 * pow(x,3) - 3 * x; break;
				case 4:
					phi = 8 * pow(x,4) - 8 * pow(x,2) + 1; break;
				case 5:
					phi = 16 * pow(x,5) - 20 * pow(x,3) + 5 * x; break;
			}
			y[i] += b[k] * phi;
		}
	}
}
void writePolly(int numPts, double pts[], double y[]){
	FILE *fptr;
	int i;
	fptr = fopen("C:/Users/caleb/CprE424/Cheby.txt","w");
	for(i = 0; i<numPts; i++){
		fprintf(fptr,"%f\t%f\n", pts[i],y[i]);
	}
	fclose(fptr);
}
