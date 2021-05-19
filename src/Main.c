#include <stdio.h>
#include <stdlib.h>

#include "FileHandling.h"
#include "HTMLChecker.h"
#include "HTMLExtractor.h"


char *htmlContent = NULL;
int currentFileIndex;

int main(){
    htmlContent = loadFile();

    int top = -1;
    char stack[MAXIMUM_NO_TAGS][MAX_LEN_TAG];

    char *coreTag = malloc(MAX_LEN_TAG * sizeof(char));

    currentFileIndex = 0;
    int valid = getCoreTag(&currentFileIndex, htmlContent, coreTag);

    while (valid == 1){
        int isPushPop = inPlace(stack, &top, coreTag); 

        if (isPushPop == 1){
           push(stack, &top, coreTag); 
        }
        else if (isPushPop == -1){
            pop(stack, &top, coreTag);
        }
        else if (isPushPop != 2){
            exit(0);
        }

        valid = getCoreTag(&currentFileIndex, htmlContent, coreTag); 
    }

    printf("No parse errors\n");

    /*while (peek(stack, &top, coreTag) != -1){
        top = top - 1;
        printf("%s\n", coreTag);
    }*/

    // TODO NEED TO FREE CORE TAG MEMORY
    
    return 0;
}