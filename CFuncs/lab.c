#include <stdio.h>
#include <math.h>
#include <limits.h>

int main(){
	
	int n = 0; //Find n!
	float x = 0; //Find e^x
	float y = 0; //Find log(y)

	printf("Please input a number to be factorialized\n");
	scanf("%d",&n);

	if((n > INT_MAX) || (n < 0)){
		printf("number not valid. Must be greater than 0 and less than %d\n",INT_MAX);
		printf("Please input a number to be factorialized\n");
		scanf("%d",&n);
	}
	
	long n_out = 1;

	for(int i=n;i > 0;i--){
		n_out = n_out * i;
	}

	printf("Please input a number to be exponentialized\n");
	scanf("%f",&x);

	double x_out = exp(x);

	printf("Please input a number to be logrithmized\n");
	scanf("%f",&y);

	if(y <= 0){
		printf("number not valid. Must be greater than 0\n");
		printf("Please input a number to be logrithmized\n");
		scanf("%f",&y);
	}

	double y_out = log(y);
	printf("n_factorial = %ld, e^x = %lf, and log(y) = %lf\n",n_out,x_out,y_out);

	return 0;
}
