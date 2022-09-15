#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define e 2.718281828459

//Function prototypes
int factorial(int x);
double exponential(float x, int n);

int main(){

	//Define constants and variables
	float x = 1.25;
	int n = 10;
	double exp[n + 1];

	//Populate exp array with exponentials and output the 
	for(int i=0; i <= n; i++){
		exp[i] = exponential(x,i);
		printf("The %dth iteration of e^x is %lf\n",i,exp[i]);
	}
	return 0;
}



double exponential(float x, int n){
	int x_0 = round(x);
	float z = x - x_0;
	float e_x0 = pow(e,x_0);
	float sum = 0;
	
	//Make sure Z is positive
	if(z < 0){ z = -z;}

	//Add the taylor series components
	for(int i = 0; i <= n; i++){
		sum = sum + (pow(z,i) / factorial(i));
	}
	//Multiply the taylor series components with the original e^x_0
	double exp = sum * e_x0;
	return exp;
}

int factorial(int x){
	int i;
	int fac = 1;

	//Multiply series of numbers from x to 1
	for(i = x; i > 0; i--){
		fac = fac * i;
	}

	return fac;
}
