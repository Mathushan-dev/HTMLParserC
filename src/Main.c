#include <stdio.h>
#include <stdlib.h>

#include "FileHandling.h"
#include "HTMLChecker.h"
#include "HTMLExtractor.h"


char *htmlContent = NULL;
int currentFileIndex;

int main(){
    htmlContent = loadFile();

    char *coreTag = malloc(MAX_LEN_TAG * sizeof(char));
    currentFileIndex = 0;
    int valid = getCoreTag(&currentFileIndex, htmlContent, coreTag);

    while (valid == 1){
        int isPushPop = inPlace(coreTag); 

        if (isPushPop == 1){
           push(coreTag); 
        }
        else if (isPushPop == -1){
            pop(coreTag);
        }
        else if (isPushPop != 2){
            exit(0);
        }

        valid = getCoreTag(&currentFileIndex, htmlContent, coreTag); 
    }

    printf("No parse errors\n");
    free(htmlContent);
    free(coreTag);
    return 0;
}