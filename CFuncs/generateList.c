#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateList(node** head, const int num_nodes){
	
	// Create temp node to add to list
	node* temp;
	
	// Allow user entry of node value
	for(int i = 0; i < num_nodes; i++){
		temp = (node*)malloc(sizeof(node));
		printf("Enter node %d voltage\n",i);
		int nodeVoltage;
		scanf("%i", &nodeVoltage);
		temp->value = nodeVoltage;
		temp->position = 0;

		// Check if current node is the head
		// If yes, make next node the null and replace with temp
		if(*head == NULL){
			*head = temp;
			(*head)->next = NULL;
		}
		// If no, save next node as head and replace with temp
		else{
			temp->next = *head;
			*head = temp;
		}
	}
	printf("\n");

	// Assign position to each node
	node* ptr = *head;
	int pos = 1;
	while(ptr != NULL){
		ptr->position = pos;
		pos = pos + 1;
		ptr = ptr->next;
	}

}
