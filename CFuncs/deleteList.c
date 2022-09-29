#include <stdlib.h>
#include "node.h"

void deleteList(node ** head){

	// Free allocated space for list in each list element
	node* temp;
	while(*head != NULL){
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}
