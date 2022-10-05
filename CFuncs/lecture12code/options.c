#include <stdio.h>
#include "node.h"

void listOptions(){
	
	// Lists off options to be input to esecuteOption function. Inputs will be taken in by main function
	printf("\n Enter one of the following commands:\n");
	printf("\n 0: List Options");
	printf("\n 1: Push");
	printf("\n 2: Pop");
	printf("\n 3: Peek");
	printf("\n 4: Display");
	printf("\n 5: Get Stack Size");
	printf("\n 6: Exit\n");
}

void executeOption(const int option, node** top){

	// Switch command to execute option input by main based off the selecti0on in listOptions
	int value;

	switch(option){

		case 0:
			listOptions();
			break;
		
		case 1:
			printf("\nEnter Value: ");
			scanf("%i",&value);
			push(top, value);
			break;
	
		case 2: 
			if(*top != NULL){ printf("Pop value is %d\n",pop(top)); }
			else{ printf(" Stack empty\n"); }
			break;	
			
		case 3:
			if(*top != NULL){ printf("Top value is %d\n",peek(*top)); }
                        else{ printf(" Stack empty\n"); }
                        break;

		case 4:
			display(*top);
			break;

		case 5:
			printf("Stack size is %d\n",stackSize(*top));
			break;

		case 6:
			break;

		default:
			printf("invalid command\n");
			listOptions();
			break;
		}
}
