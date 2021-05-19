#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "HTMLChecker.h"

int headPresent = 0;
int bodyPresent = 0;
int titlePresent = 0;

int inPlace(char stack[MAXIMUM_NO_TAGS][MAX_LEN_TAG], int *top, char tag[MAX_LEN_TAG]){
    char *lastTag = malloc(MAX_LEN_TAG * sizeof(char));
    int stackNotEmpty = peek(stack, top, lastTag);

    if (stackNotEmpty == -1 && strcmp(tag, "<html>") == 0){
        return 1;
    } else if (strcmp(lastTag, "<html>") == 0){
        return followsHTMLTag(tag);
    } else if (strcmp(lastTag, "<head>") == 0){
        return followsHeadTag(tag);
    } else if (strcmp(lastTag, "<title>") == 0){
        return followsTitleTag(tag);
    } else if (strcmp(lastTag, "<body>") == 0){
        return followsBodyTag(tag);
    } else if (strcmp(lastTag, "<div>") == 0){
        return followsDivTag(tag);
    } else if (strcmp(lastTag, "<h1>") == 0 || strcmp(lastTag, "<h2>") == 0 || strcmp(lastTag, "<h3>") == 0){
        return followsHeadingTag(lastTag, tag);
    } else if (strcmp(lastTag, "<li>") == 0){
        return followsLiTag(tag);
    } else if (strcmp(lastTag, "<p>") == 0){
        return followsPTag(tag);
    } else if (strcmp(lastTag, "<a>") == 0){
        return followsATag(tag);
    } else if (strcmp(lastTag, "<ul>") == 0){
        return followsUlTag(tag);
    } else if (strcmp(tag, "<br>") == 0 || strcmp(tag, "<hr>") == 0){
        printf("Error on parsing %s %s.\n%s tags cannot be used outside the <body> and </body> tags.", lastTag, tag, tag);
        return 0;
    }
    printf("Error on parsing %s %s.\n%s is not a recognised tag.", lastTag, tag, tag);
    return 0;
}

int followsHTMLTag(char tag[MAX_LEN_TAG]){
    // ASSUMPTION <br> or <hr> CANNOT FOLLOW <html>
    if (strcmp(tag, "</html>") == 0 && headPresent == 1 && bodyPresent == 1){
        return -1;
    } else if ((strcmp(tag, "<head>") == 0 && headPresent == 0 && bodyPresent == 0) || (strcmp(tag, "<body>") == 0 && headPresent == 1 && bodyPresent == 0)){
        return 1;
    }
    printf("Error on parsing <html> %s.\n<html> </html> MUST surround a SINGLE pair of opening and closing <head> and <body> tags.", tag);
    return 0;
}

int followsHeadTag(char tag[MAX_LEN_TAG]){
    // ASSUMPTION <br> or <hr> CANNOT FOLLOW <head>
    if (strcmp(tag, "<title>") == 0 && titlePresent == 0){
        return 1;
    } else if(strcmp("</head>", tag) == 0 && titlePresent == 1){
        headPresent = 1;
        return -1;
    }
    printf("Error on parsing <head> %s.\n<head> </head> MUST surround a SINGLE pair of opening and closing <title> tags.", tag);
    return 0;
}

int followsTitleTag(char tag[MAX_LEN_TAG]){
    // ASSUMPTION <br> or <hr> CANNOT FOLLOW <title>
    if (strcmp(tag, "</title>") == 0){
        titlePresent = 1;
        return -1;
    }
    printf("Error on parsing <title> %s.\n<title> </title> can NOT surround unrecognised tags.", tag);
    return 0;
}

int followsBodyTag(char tag[MAX_LEN_TAG]){
    // ASSUMPTION <li> CANNOT FOLLOW <body> AS <li> MUST BE IN <ul> tags
    if (strcmp(tag, "</body>") == 0){
        bodyPresent = 1;
        return -1;
    } else if (strcmp(tag, "<h1>") == 0 || strcmp(tag, "<h2>") == 0 || strcmp(tag, "<h3>") == 0 || strcmp(tag, "<div>") == 0 || strcmp(tag, "<p>") == 0 || strcmp(tag, "<a>") == 0 || strcmp(tag, "<ul>") == 0){
        return 1;
    } else if (strcmp(tag, "<br>") == 0 || strcmp(tag, "<hr>") == 0){
        return 2;
    }
    printf("Error on parsing <body> %s.\n<body> </body> can NOT surround uncontained <li> or unrecognised tags.", tag);
    return 0;
}

int followsDivTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "</div>") == 0){
        return -1;
    } else if ((strcmp(tag, "<h1>") == 0 || strcmp(tag, "<h2>") == 0 || strcmp(tag, "<h3>") == 0 || strcmp(tag, "<div>") == 0 || strcmp(tag, "<p>") == 0 || strcmp(tag, "<a>") == 0 || strcmp(tag, "<ul>") == 0)){
        return 1;
    } else if (strcmp(tag, "<br>") == 0 || strcmp(tag, "<hr>") == 0){
        return 2;
    } 
    printf("Error on parsing <div> %s.\n<div> </div> can NOT surround uncontained <li> or unrecognised tags.", tag);
    return 0;
}

int followsHeadingTag(char *lastTag, char tag[MAX_LEN_TAG]){
    if ((strcmp(lastTag, "<h1>") == 0 && strcmp(tag, "</h1>") == 0) || (strcmp(lastTag, "<h2>") == 0 && strcmp(tag, "</h2>") == 0) || (strcmp(lastTag, "<h3>") == 0 && strcmp(tag, "</h3>") == 0)){
        return -1;
    } else if (strcmp(tag, "<p>") == 0){
        return 1;
    } else if (strcmp(tag, "<br>") == 0 || strcmp(tag, "<hr>") == 0){
        return 2;
    } 
    printf("Error on parsing %s %s.\n<h1/2/3> </h/1/2/3> can ONLY surround <p> <br> or <hr> tags.", lastTag, tag);
    return 0; 
}

int followsLiTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "<p>") == 0){
        return 1;
    } else if (strcmp(tag, "</li>") == 0){
        return -1;
    } else if (strcmp(tag, "<br>") == 0 || strcmp(tag, "<hr>") == 0){
        return 2;
    } 
    printf("Error on parsing <li> %s.\n<li> </li> can ONLY surround <p> <br> and <hr> tags.", tag);
    return 0;  
}

int followsPTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "</p>") == 0){
        return -1;
    } else if (strcmp(tag, "<a>") == 0){
        return 1;
    } else if (strcmp(tag, "<br>") == 0 || strcmp(tag, "<hr>") == 0){
        return 2;
    }
    printf("Error on parsing <p> %s.\n<p> </p> can ONLY surround <a> <br> and <hr> tags.", tag);
    return 0;   
}

int followsATag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "</a>") == 0){
        return -1;
    } else if (strcmp(tag, "<br>") == 0 || strcmp(tag, "<hr>") == 0){
        return 2;
    }
    printf("Error on parsing <a> %s.\n<a> </a> can ONLY surround <br> and <hr> tags.", tag);
    return 0;   
}

int followsUlTag(char tag[MAX_LEN_TAG]){
    if (strcmp(tag, "</ul>") == 0){
        return -1;
    } else if (strcmp(tag, "<li>") == 0){
        return 1;
    } else if (strcmp(tag, "<br>") == 0 || strcmp(tag, "<hr>") == 0){
        return 2;
    }
    printf("Error on parsing <ul> %s.\n<ul> </ul> can ONLY surround <li> <br> and <hr> tags.", tag);
    return 0;   
}