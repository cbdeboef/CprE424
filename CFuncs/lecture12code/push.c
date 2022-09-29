#include "node.h"

void push(node** top, int value){

	if(*top == NULL){
		*top = (node*)malloc(sizeof(struct node));
		(*top)->next = NULL;
		(*top)->value = value;
		(*top)->position = 1;
	}
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
