#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>

// Ignore these #defines; they just define place holders you need to replace
#define ________1_1________ 0
#define ________1_2________ 0
#define ________1_3________ 0, 0, 0, 0


int main(int argc, char **argv) {
    FILE *fp;
    char *fname;
    char buf[4096];
    struct stat st;
    int n1, n2;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filenames...>\n", argv[0]);
        return 1;
    }

    while (*++argv) {
        fname = *argv;

        fp = ________1_1________;

        /* Include null terminator in filename */
        n1 = strlen(fname) + 1;
        n2 = htonl(n1);

        fwrite(&n2, 1, sizeof(n2), stdout);
        fwrite(fname, 1, n1, stdout);

        /* Get the size of the file in bytes */
        stat(fname, &st);
        n1 = htonl(st.st_size);
        fwrite(&n1, 1, sizeof(n1), stdout);

        while ( ________1_2________ )
            fwrite( ________1_3________ );

        fclose(fp);
    }

    return 0;
}
