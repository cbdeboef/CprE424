#include "node.h"

void push(node** top, int value){
	
	// Add enterd value to top of stack and increment value of position.
	
	// If first element, only make new element
	if(*top == NULL){
		*top = (node*)malloc(sizeof(struct node));
		(*top)->next = NULL;
		(*top)->value = value;
		(*top)->position = 1;
	}

	// if not first element, increment all element position values below new element
	else{
		node* temp;
		temp = (node*)malloc(sizeof(struct node));
		temp->next = *top;
		temp->value = value;
	 	temp->position = 1;
		*top = temp;

		node* ptr = (*top)->next;
		while(ptr != NULL){
			ptr->position = ptr->position+1;
			ptr = ptr->next;
		}
	}
}
