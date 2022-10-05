#include "node.h"
#include <stdlib.h>

void deleteStack(node** top){
	// Delete the stack and free allocated Memory
		
	node* temp;
	while(*top != NULL){
		temp = *top;
		*top = (*top)->next;
		free(temp);
	}
}
