#include "node.h"
#include <stdio.h>

int main(){
	// Loop through the execute option function and take user input to allow for 
	// pushing and popping of values. Deletes stack when done
	
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
