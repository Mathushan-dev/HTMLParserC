#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fPtr;
char filePath[]="file.txt";
char *fileContents = NULL;
size_t size = 0;

char* loadFile(){
    fPtr = fopen(filePath, "r");
    if (fPtr == NULL){
        return("Unable to open file.");
    }
    else {
        fseek(fPtr, 0, SEEK_END);
        size = ftell(fPtr);
        rewind(fPtr);

        fileContents = malloc((size + 1) * sizeof(*fileContents));
        fread(fileContents, size, 1, fPtr);

        fileContents[size] = '\0';

        return(fileContents);
    }
}