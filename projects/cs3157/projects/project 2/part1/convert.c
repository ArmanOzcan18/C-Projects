#include <stdio.h>  // for printf()
#include <stdlib.h> // for atoi()

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Error: no argument specified.\n");
        return 1;
    }

    int x = atoi(argv[1]); // Parse the first argument as an int

    char binary[] = "0000 0000 0000 0000 0000 0000 0000 0000";
    
    int compare  = 1;
    int count = 0;
    
    while(count != 32){
        if(x & compare){
            binary[38  -count -count/4]='1';
        }
        compare = compare << 1;
        count++;
    }  

    printf("signed dec:   %d\n", x);
    printf("unsigned dec: %u\n", x);
    printf("hex:          %x\n", x);
    printf("binary:       %s\n", binary);
   
    return 0;
}
