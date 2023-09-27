#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>

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

        fp = fopen(fname, "rb");                            // (1.1)

        /* Include null terminator in filename */
        n1 = strlen(fname) + 1;
        n2 = htonl(n1);

        fwrite(&n2, 1, sizeof(n2), stdout);
        fwrite(fname, 1, n1, stdout);

        /* Get the size of the file in bytes */
        stat(fname, &st);
        n1 = htonl(st.st_size);
        fwrite(&n1, 1, sizeof(n1), stdout);

        while ((n1 = fread(buf, 1, sizeof(buf), fp)) > 0)   // (1.2)
            fwrite(buf, 1, n1, stdout);                     // (1.3)

        fclose(fp);
    }

    return 0;
}
