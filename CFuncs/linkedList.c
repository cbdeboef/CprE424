#include <stdio.h>
#include "node.h"

int main(){

	node* head = NULL;

	const int num_nodes = getNumberOfNodes();
	generateList(&head, num_nodes);
	

	print(1, head);
	print(0, head);
	
	if(num_nodes > 0){	
		const int key = getKey();
		searchList(head,key);
	}

	deleteList(&head);
}
