#include "node.h"

int pop(node** top){
	
	// Look at value on top of stack. Remove it and return the value.
	int val;
	node* temp = *top;
	
	if(temp == NULL){ return 0; }
	else{ temp = temp->next; }
	
	val = (*top)->value;
	free(*top);
	*top = temp;

	node* ptr = *top;
	while(ptr != NULL){
		(ptr->position)--;
		ptr = ptr->next;
	}

	return val;
}
