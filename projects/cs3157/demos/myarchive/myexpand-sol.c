#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    FILE *fp1;
    char *p1;
    int n1, n1_net;

    FILE *fp2;
    char *p2;
    int n2, n2_net;

    while (1) {
        // Read in length of filename.
        if (fread(&n1_net, 1, sizeof(n1_net), stdin) == 0)
            // If we don't read anything in, then we're done expanding files.
            break;

        // Filename length is in network byte order; convert to host byte order.
        n1 = ntohl(n1_net);

        // Allocate memory for filename; note that filename already includes
        // null terminator, so no need to +1 here.
        p1 = malloc(n1);

        // Read in filename to buffer.
        fread(p1, 1, n1, stdin);

        // Open FILE pointer to file with filename.
        fp1 = fopen(p1, "wb");

        // Read in file size.
        fread(&n1_net, 1, sizeof(n1_net), stdin);

        // File size is also in network byte order; convert to host byte order.
        n1 = ntohl(n1_net);

        // Allocate buffer to read file contents into.
        p2 = malloc(n1);

        // Read file contents into buffer.
        fread(p2, 1, n1, stdin);

        // Write file contents from buffer to file.
        fwrite(p2, 1, n1, fp1);

        // Clean up.
        free(p2);
        fclose(fp1);
        free(p1);
    }

    return 0;
}
