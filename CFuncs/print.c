#include "node.h"
#include <stdio.h>
#include <stdlib.h>

void print(const int forward, const node* head){
	
	// Check that list is not empty
	if(head == NULL){ printf("list is empty.\n\n"); return;}
	
	printf("\n");
	
	// Print labels for output
	printf(" --------------------------------------------------\n"); 
	printf(" |Pos:|   Val:  |    Address:    |      Next      |\n"); 
	printf(" --------------------------------------------------\n");
	
	// Check weather to print forward or reverse
	switch(forward){
		case 0:
			reversePrintList(head);
			break;
		case 1:
			printList(head);
			break;
		default:
			printf("error: invalid forward value. Must be 1 or 0");
			exit(1);
	}
	printf(" --------------------------------------------------\n");
}

// Print the values in a single element of list
void printLine(const int pos, const int val, const node* head, const node* next){
	printf(" |%3i |%3p |%15p |%15p |\n", pos, val, head, next);
}

// Print list elements forwards
void printList(const node* head){
	printLine(head->position, head->value, head, head->next);
	if(head->next == NULL){ return;}
	printList(head->next);
}

// Print list elemnts backwards
void reversePrintList(const node* head){
	if(head->next == NULL){
		printLine(head->position, head->value, head, head->next);
		return;
	}
	reversePrintList(head->next);
	printLine(head->position, head->value, head, head->next);
}
