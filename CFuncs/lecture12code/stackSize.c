#include "node.h"

int stackSize(node* top){
	
	if(top == NULL){ return 0; }
	node* temp = top;
	while(temp->next != NULL){
		temp = temp->next;
	}

	return temp->position;
}
