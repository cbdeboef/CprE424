#include <stdio.h>
#include "node.h"

int main(){
	
	// Declare node head
	node* head = NULL;
	
	// Get user entered num nodes and create list
	const int num_nodes = getNumberOfNodes();
	generateList(&head, num_nodes);
	
	// print the list both forwards (1) and backwards (0)
	print(1, head);
	print(0, head);
	
	// Make sure list has at least 1 element and get user input for key
	// Then search for value entered in list
	if(num_nodes > 0){	
		const int key = getKey();
		searchList(head,key);
	}
	
	// Delete list after use to save memory
	deleteList(&head);
}
