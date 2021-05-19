#include "HTMLExtractor.h"

int tagIndex;

int getCoreTag(int *currentFileIndex, char *text, char *tag){
    int textIndex = *currentFileIndex;
    tagIndex = 0;
    
    if (findTagStart(&tagIndex, &textIndex, tag, text) == -1){
        return -1;
    }

    addIncrementTag(&tagIndex, &textIndex, tag, text);

    if (addCore(&tagIndex, &textIndex, tag, text) == -1){
        return -1;
    }

    addIncrementTag(&tagIndex, &textIndex, tag, text);

    tag[tagIndex] = '\0';
    *currentFileIndex = textIndex;
    return 1;
}

void addIncrementTag(int *tagIndex, int *textIndex, char *tag, char *text){
    tag[*tagIndex] = text[*textIndex];
    (*tagIndex)++;
    (*textIndex)++;
}

int findTagStart(int *tagIndex, int *textIndex, char *tag, char *text){
    while (text[*textIndex] != '<'){
        if (text[*textIndex] == '\0'){
            return -1;
        }
        (*textIndex)++;
    }
    return 0;
}

int addCore(int *tagIndex, int *textIndex, char *tag, char *text){
    int isCore = 1;
    while (text[*textIndex] != '>') {
        if (text[*textIndex] == '\0') {
            return -1;
        }

        if (text[*textIndex] == ' '){
            isCore = 0;
        }

        if (isCore == 1){
            tag[*tagIndex] = text[*textIndex];
            (*tagIndex)++;
        }

        (*textIndex)++;
    }
    return 0;
}