#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

struct node {
    char data[MAX_LEN_TAG];
    struct node *next;
};

struct node *top = NULL;

int push(char *tag){
    struct node *nextNode = malloc(sizeof(struct node));
    strcpy(nextNode->data, tag);
    nextNode->next = top;
    top = nextNode;
    return 1;
}

int pop(char *tag) {
    if (top == NULL) {
        return -1;
    }
    else {
        struct node *temp;
        temp = top;
        top = top->next;
        free(temp);
        return 1;
    }
}

int peek(char *tag) {
    if (top == NULL) {
        return -1;
    }
    else {
        strcpy(tag, top->data);
        return 1;
    }
}