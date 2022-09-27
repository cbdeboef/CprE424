void generateList(node** head, const int num_nodes){
	int i;
	node* temp;
	srand(time(NULL));
	for(i = 0; i < num_nodes; i++){
		temp = (node*)malloc(sizeof(node));
		temp->value = rand()%num_nodes;
		temp->position = 0;
		printf("%d",temp->value);
	}
	if(*head == NULL){
		*head = temp;
		(*head)->next = NULL;
	}
	else{
		temp->next = *head;
		*head = temp;
	}
	printf("\n");

	node* ptr = *head;
	int pos = 1;
	while(ptr != NULL){
		ptr->position = pos;
		pos = pos + 1;
		ptr = ptr->next;
	}
}
