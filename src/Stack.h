#define MAXIMUM_NO_TAGS 100
#define MAX_LEN_TAG 15

int push(char stack[MAXIMUM_NO_TAGS][MAX_LEN_TAG], int *top, char tag[MAX_LEN_TAG]);

int pop(char stack[MAXIMUM_NO_TAGS][MAX_LEN_TAG], int *top, char tag[MAX_LEN_TAG]);