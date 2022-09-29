#include "node.h"
#include <stdio.h>
#include <stdlib.h>

void display(node* head){

        // Check that list is not empty
        if(head == NULL){ printf("list is empty.\n\n"); return;}

        printf("\n");

        // Print labels for output
        printf(" --------------------------------------------------\n");
        printf(" |Pos:|   Val:  |    Address:    |      Next      |\n");
        printf(" --------------------------------------------------\n");

        printList(head);

        printf(" --------------------------------------------------\n");
}

// Print the values in a single element of list
void printLine(const int pos, const int val, const node* head, const node* next){
        printf(" |%3i |%3p |%15p |%15p |\n", pos, val, head, next);
}

// Print list elements
void printList(const node* head){
        printLine(head->position, head->value, head, head->next);
        if(head->next == NULL){ return;}
        printList(head->next);
}
