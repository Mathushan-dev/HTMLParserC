#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int currentFileIndex;
int tagIndex;

int getCoreTag(int textIndex, char *text, char *tag){
    tagIndex = 0;

    if (text[textIndex] == '\0'){
        return -1;
    }

    while (text[textIndex] != '<'){
        if (text[textIndex] == '\0'){
            return -1;
        }
        textIndex++;
    }

    tag[tagIndex] = text[textIndex];
    tagIndex++;
    textIndex++;

    while (text[textIndex] != ' ') {
        if (text[textIndex] == '\0') {
            return -1;
        }

        if (text[textIndex] == '>') {
            tag[tagIndex] = text[textIndex];
            tagIndex++;
            textIndex++;
            tag[tagIndex] = '\0';
            currentFileIndex = textIndex;
            return 1;
        }

        tag[tagIndex] = text[textIndex];
        tagIndex++;
        textIndex++;
    }

   
    //tag[tagIndex] = text[textIndex];
    //tagIndex++;
    textIndex++;

    while (text[textIndex] != '>'){
        if (text[textIndex] == '\0') {
            return -1;
        }

        textIndex++;
    }

    tag[tagIndex] = text[textIndex];
    tagIndex++;
    textIndex++;

    tag[tagIndex] = '\0';
    currentFileIndex = textIndex;
    return 1;
}

int getCurrentFileIndex(){
    return currentFileIndex;
}