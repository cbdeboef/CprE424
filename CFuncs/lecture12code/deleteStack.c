#include "node.h"
#include <stdlib.h>

void deleteStack(node** top){
	
	node* temp;
	while(*top != NULL){
		temp = *top;
		*top = (*top)->next;
		free(temp);
	}
}
