#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <mylist.h>

static void print(void * str){
    printf("%s\n",(char *) str);
    return;
}

int main(int argc, char **argv){
    struct List list;
    initList(&list);
    argv++;
    
    while(*argv != NULL){
        addFront(&list, *argv);
        argv++;
    }
    
    traverseList(&list, &print);
   
    if(findNode(&list, "dude",(int (*)(const void *, const void *)) &strcmp) == NULL){
        printf("\ndude not found\n");
    }else{
        printf("\ndude found\n");
    }
    
    removeAllNodes(&list);

    return 0;
}
