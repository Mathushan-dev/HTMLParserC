#include <stdio.h>
#include <stdlib.h>

#include "FileHandling.h"
#include "HTMLChecker.h"
#include "Stack.h"

char *htmlContent = NULL;
int currentFileIndex = 0;

int main(){
    htmlContent = loadFile();

    int top = -1;
    char stack[MAXIMUM_NO_TAGS][MAX_LEN_TAG];

    char *coreTag = malloc(MAX_LEN_TAG * sizeof(char)); 
    int valid = getCoreTag(currentFileIndex, htmlContent, coreTag);

    while (valid == 1){
        //printf("%s", coreTag);
        push(stack, &top, coreTag);
        currentFileIndex = getCurrentFileIndex();
        valid = getCoreTag(currentFileIndex, htmlContent, coreTag); 
    }

    while (pop(stack, &top, coreTag) != -1){
        printf("%s\n", coreTag);
    }
    
    return 0;
}