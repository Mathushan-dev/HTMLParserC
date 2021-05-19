#include "Stack.h"

#define MAX_LEN_ERROR_MESSAGE 30

int getCoreTag(int *currentFileIndex, char *text, char *tag);

void addIncrementTag(int *tagIndex, int *textIndex, char *tag, char *text);

int findTagStart(int *tagIndex, int *textIndex, char *tag, char *text);

int addCore(int *tagIndex, int *textIndex, char *tag, char *text);

int inPlace(char stack[MAXIMUM_NO_TAGS][MAX_LEN_TAG], int *top, char tag[MAX_LEN_TAG]);

int followsHTMLTag(char tag[MAX_LEN_TAG]);

int followsHeadTag(char tag[MAX_LEN_TAG]);

int followsTitleTag(char tag[MAX_LEN_TAG]);

int followsBodyTag(char tag[MAX_LEN_TAG]);

int followsDivTag(char tag[MAX_LEN_TAG]);

int followsHeadingTag(char *lastTag, char tag[MAX_LEN_TAG]);

int followsLiTag(char tag[MAX_LEN_TAG]);

int followsPTag(char tag[MAX_LEN_TAG]);

int followsATag(char tag[MAX_LEN_TAG]);

int followsUlTag(char tag[MAX_LEN_TAG]);