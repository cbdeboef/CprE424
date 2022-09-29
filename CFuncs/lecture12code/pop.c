#include "node.h"

int pop(node** top){

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
