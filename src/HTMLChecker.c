#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "HTMLChecker.h"

int headPresent = 0;
int bodyPresent = 0;
int titlePresent = 0;

int inPlace(char tag[MAX_LEN_TAG]){
    char *lastTag = malloc(MAX_LEN_TAG * sizeof(char));
    int stackNotEmpty = peek(lastTag);
    int optionToReturn = 999;

    if (strcmp(tag, "<br>") == 0 || strcmp(tag, "<hr>") == 0){
        optionToReturn = 2;
    } else if (stackNotEmpty == -1 && strcmp(tag, "<html>") == 0){
        optionToReturn = 1;
    } else if (strcmp(lastTag, "<html>") == 0){
        optionToReturn = followsHTMLTag(tag);
    } else if (strcmp(lastTag, "<head>") == 0){
        optionToReturn = followsHeadTag(tag);
    } else if (strcmp(lastTag, "<title>") == 0){
        optionToReturn = followsTitleTag(tag);
    } else if (strcmp(lastTag, "<body>") == 0){
        optionToReturn = followsBodyTag(tag);
    } else if (strcmp(lastTag, "<div>") == 0){
        optionToReturn = followsDivTag(tag);
    } else if (strcmp(lastTag, "<h1>") == 0 || strcmp(lastTag, "<h2>") == 0 || strcmp(lastTag, "<h3>") == 0){
        optionToReturn = followsHeadingTag(lastTag, tag);
    } else if (strcmp(lastTag, "<li>") == 0){
        optionToReturn = followsLiTag(tag);
    } else if (strcmp(lastTag, "<p>") == 0){
        optionToReturn = followsPTag(tag);
    } else if (strcmp(lastTag, "<a>") == 0){
        optionToReturn = followsATag(tag);
    } else if (strcmp(lastTag, "<ul>") == 0){
        optionToReturn = followsUlTag(tag);
    }

    free(lastTag);
    if (optionToReturn == 999){
        printf("Error on parsing %s %s.\n%s is not a recognised tag.", lastTag, tag, tag);
        return 0;
    }
    return optionToReturn;

}

int followsHTMLTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "</html>") == 0 && headPresent == 1 && bodyPresent == 1){
        return -1;
    } else if ((strcmp(tag, "<head>") == 0 && headPresent == 0 && bodyPresent == 0) || (strcmp(tag, "<body>") == 0 && headPresent == 1 && bodyPresent == 0)){
        return 1;
    }
    printf("Error on parsing <html> %s.\n<html> </html> MUST contain a SINGLE pair of opening and closing <head> and <body> tags.", tag);
    return 0;
}

int followsHeadTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "<title>") == 0 && titlePresent == 0){
        return 1;
    } else if(strcmp("</head>", tag) == 0 && titlePresent == 1){
        headPresent = 1;
        return -1;
    }
    printf("Error on parsing <head> %s.\n<head> </head> MUST contain a SINGLE pair of opening and closing <title> tags.", tag);
    return 0;
}

int followsTitleTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "</title>") == 0){
        titlePresent = 1;
        return -1;
    }
    printf("Error on parsing <title> %s.\n<title> </title> can ONLY contain <br> and <hr> tags.", tag);
    return 0;
}

int followsBodyTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "</body>") == 0){
        bodyPresent = 1;
        return -1;
    } else if (strcmp(tag, "<h1>") == 0 || strcmp(tag, "<h2>") == 0 || strcmp(tag, "<h3>") == 0 || strcmp(tag, "<div>") == 0 || strcmp(tag, "<p>") == 0 || strcmp(tag, "<a>") == 0 || strcmp(tag, "<ul>") == 0 || strcmp(tag, "<li>") == 0){
        return 1;
    }
    printf("Error on parsing <body> %s.\n<body> </body> can ONLY contain <h1/2/3> <div> <p> <a> <ul> <li> <br> and <hr> tags.", tag);
    return 0;
}

int followsDivTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "</div>") == 0){
        return -1;
    } else if ((strcmp(tag, "<h1>") == 0 || strcmp(tag, "<h2>") == 0 || strcmp(tag, "<h3>") == 0 || strcmp(tag, "<div>") == 0 || strcmp(tag, "<p>") == 0 || strcmp(tag, "<a>") == 0 || strcmp(tag, "<ul>") == 0 || strcmp(tag, "<li>") == 0)){
        return 1;
    }
    printf("Error on parsing <div> %s.\n<div> </div> can ONLY contain <h1/2/3> <div> <p> <a> <ul> <li> <br> and <hr> tags.", tag);
    return 0;
}

int followsHeadingTag(char *lastTag, char tag[MAX_LEN_TAG]){
    if ((strcmp(lastTag, "<h1>") == 0 && strcmp(tag, "</h1>") == 0) || (strcmp(lastTag, "<h2>") == 0 && strcmp(tag, "</h2>") == 0) || (strcmp(lastTag, "<h3>") == 0 && strcmp(tag, "</h3>") == 0)){
        return -1;
    } else if (strcmp(tag, "<p>") == 0){
        return 1;
    }
    printf("Error on parsing %s %s.\n<h1/2/3> </h/1/2/3> can ONLY contain <p> <br> and <hr> tags.", lastTag, tag);
    return 0; 
}

int followsLiTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "<p>") == 0){
        return 1;
    } else if (strcmp(tag, "</li>") == 0){
        return -1;
    }
    printf("Error on parsing <li> %s.\n<li> </li> can ONLY contain <p> <br> and <hr> tags.", tag);
    return 0;  
}

int followsPTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "</p>") == 0){
        return -1;
    } else if (strcmp(tag, "<a>") == 0){
        return 1;
    }
    printf("Error on parsing <p> %s.\n<p> </p> can ONLY contain <a> <br> and <hr> tags.", tag);
    return 0;   
}

int followsATag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "</a>") == 0){
        return -1;
    }
    printf("Error on parsing <a> %s.\n<a> </a> can ONLY contain <br> and <hr> tags.", tag);
    return 0;   
}

int followsUlTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "</ul>") == 0){
        return -1;
    } else if (strcmp(tag, "<li>") == 0){
        return 1;
    }
    printf("Error on parsing <ul> %s.\n<ul> </ul> can ONLY contain <li> <br> and <hr> tags.", tag);
    return 0;   
}