#include "node.h"
#include <stdio.h>

int main(){
	
	node* top = NULL;

	int option = 0;
	while(option != 6){
		executeOption(option, &top);
		printf("\nEnter command: ");
		scanf("%d",&option);
	}	

	deleteStack(&top);
	return 0;
}
