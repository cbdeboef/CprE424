#include "node.h"
#include <stdio.h>

void print(const int forward, const node* head){
	if(head == NULL){ printf("list is empty.\n\n");}
	
	printf("\n");
	
	printf(" ---------------------------------------------\n"); 
	printf(" |Pos:|Val:|     Address:     |     Next      |\n"); 
	printf(" ---------------------------------------------\n");
	
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
	printf(" ---------------------------------------------\n");
}

void printLine(const int pos, const int val, vonst node* head, const node* next){
	printf(" |%3i |%3p |%15p |%15p |\n", pos, val, head, next);
}

void printList(const node* head){
	printLine(head->position, head->value, head, head->next);
	if(head->next == NULL){ return;}
	printList(head->next)
}

void reverse printlist(const node* head){
	if(head->next == null){
		printLine(head->position, head->value, head, head->next);
		return;
	}
	reversePrintList(head->next);
	printLine(head->position, head->value, head, head->next);
}
