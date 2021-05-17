#include <string.h>
#include <stdio.h>

#include "Stack.h"

int push(char stack[MAXIMUM_NO_TAGS][MAX_LEN_TAG], int *top, char tag[MAX_LEN_TAG]){
    if(*top == MAXIMUM_NO_TAGS - 1)
        return(-1);
    else{
        *top = *top + 1;
        strcpy(stack[*top], tag);
        //printf("%s", tag);
        return(1);
    }
}

int pop(char stack[MAXIMUM_NO_TAGS][MAX_LEN_TAG], int *top, char tag[MAX_LEN_TAG]){
    if(*top == -1) {
        return (-1);
    }
    else{
        strcpy(tag, stack[*top]);
        *top = *top - 1;
        return(1);
    }
}