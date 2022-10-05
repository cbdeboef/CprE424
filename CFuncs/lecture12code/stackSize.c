#include "node.h"

int stackSize(node* top){

	// reutrn stack size to be output

	if(top == NULL){ return 0; }
	node* temp = top;
	while(temp->next != NULL){
		temp = temp->next;
	}

	return temp->position;
}
