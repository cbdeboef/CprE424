#ifndef __NODE_H__
#define __NODE_H__

typedef struct node node;
struct node{
	int position;
	int value;
	node* next;
};

int getNumberOfNodes();
void generateList(node** head, const int num);
void print(const int forward, const node* head);
void printList(const node* head);
void reversePrintList(const node* head);
void reversePrintList(const node* head);
int getKey();
void searchList(const node* head, const int key);
void deleteList(node** head);

#endif
