#ifndef __NODE_H__
#define __NODE_H__
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node{
        int position;
        int value;
        node* next;
};

void listOptions();
void push(node** top, int value);
int pop(node** top);
int peek(node* head);
void display(node* head);
void printList(const node* head);
void printLine(const int pos, const int val, const node* head, const node* next);
int stackSize(node* head);
void deleteStack(node** top);
void executeOption(const int option, node** top);

#endif
