#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void searchList(const node* head, const int key){
	
	// Check if key value is in list element. If not, go to next element
	if(head->value == key){ printf("Key found at Position: %i\n", head->position);}
	
	// When at end of list, return nothing
	if(head->next == NULL){ printf("\n"); return;}
	
	// Loop to next element and search
	searchList(head->next,key);
}
