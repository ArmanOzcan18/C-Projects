#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "twecho.h"

char **duplicateArgs(int argc, char **argv){

    char **copy = malloc((argc+1) * sizeof(char *));
    if (copy == NULL) {     
        perror("malloc returned NULL");
        exit(1);
    }
    char **p = copy;
        
    
    while(*argv){
        *p = malloc(((strlen(*argv)+1) * sizeof(char)));
        if (p == NULL) {
            perror("malloc returned NULL");
            exit(1);
        }
        size_t i;
        for(i = 0; i < strlen(*argv); i++){
            *(*p+i)=toupper(*(*argv+i));
        }
        *(*p+strlen(*argv)) = '\0';

        argv++;
        p++;
    }   
    *p = NULL;
    
    return copy;
}

void freeDuplicatedArgs(char **copy){
    
    char **original = copy;

    while(*copy){
        char *temp = *copy;
        free(temp);    
        copy++;
    }
    
    free(original);
    
    return;
}

