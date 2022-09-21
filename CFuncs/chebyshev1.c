#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calcPoly(int N, double b[], double pts[], int numPts, double* y);
void writePolly(int numPts, double pts[], double y[]);

int main(){
	//Scan in N and coeficient values	
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
	// Create x values -1 to 1
	int numPts = 200;
	double pts[numPts];
	
	for(i = 0; i < numPts; i++){
		pts[i] = i / 100.0 - 1.0;
	}
	
	// Call CalcPoly, Write Polly, and the python graphing script
	double y[numPts]; 
	calcPoly(N, b, pts, numPts, y);
	
	writePolly(numPts, pts, y);
	
	system("python C:/Users/Caleb/CprE424/PythonFuncs/plotPoly.py");
	
	return 0;	
}

void calcPoly(int N, double b[], double pts[], int numPts, double* y){
	int i;
	double phi;
        int k;
	// Loop through to create the output for all given inputs X[]
	for(i = 0; i < numPts; i++){
		y[i] = b[0];
		double x = pts[i];
		for(k = 1; k <= N; k++){
			if(k == 1){ phi = x;}
			else if(k == 2){ phi = 2 * pow(x,2) - 1;}
			else if(k == 3){ phi = 4 * pow(x,3) - 3 * x;}
			else if(k == 4){ phi = 8 * pow(x,4) - 8 * pow(x,2) + 1;}
			else if(k == 5){ phi = 16 * pow(x,5) - 20 * pow(x,3) + 5 * x;}
			
			y[i] += b[k] * phi;	
		}
	}
}
void writePolly(int numPts, double pts[], double y[]){
	// Create file with X and Y values separated by a Tab
	FILE *fptr;
	int i;
	fptr = fopen("C:/Users/caleb/CprE424/Cheby.txt","w");
	for(i = 0; i<numPts; i++){
		fprintf(fptr,"%f\t%f\n", pts[i],y[i]);
	}
	fclose(fptr);
}
