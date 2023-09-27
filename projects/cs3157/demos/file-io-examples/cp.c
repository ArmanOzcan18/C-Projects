/*
 * cp <source-file> <destination-file>
 *
 * Copy the contents of <source-file> to <destination-file>.
 *
 * Finally, report the file size (i.e., number of bytes read and written).
 *
 * If <destination-file> already exists, it is overwritten.
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    /*
     * Open each file given by the arguments.
     */

    if (argc != 3) {
        fprintf(stderr, "%s\n", "usage: ncat <source-file> <destination-file>");
        exit(1);
    }

    // Open source file for reading.
    char *src_name = argv[1];
    FILE *src = fopen(src_name, "rb");
    if (src == NULL) {
        perror(src_name);
        exit(1);
    }

    // Open destination file for writing; overwrite it if it already exists.
    char *dest_name = argv[2];
    FILE *dest = fopen(dest_name, "wb");
    if (dest == NULL) {
        perror(dest_name);
        exit(1);
    }


    /*
     * Read src chunk by chunk, and write into dest.
     */

    // Keep track of total bytes read and written.
    size_t total = 0;

    // Define a buffer we will read each chunk into.
    char buf[128];

    size_t len;
    while ((len = fread(buf, 1, sizeof(buf), src)) > 0) {
        total += len;
        if(fwrite(buf, 1, len, dest) < len) {
            // Report any errors we encounter while writing to destination
            perror(dest_name);
            exit(1);
        }

        // Writing fwrite(buf, 1, sizeof(buf), dest) is a bug; can you think of why?
    }

    /*
     * Did we terminate the fread() loop because of an error?
     * If so, report the error.
     */

    if (ferror(src)) {
        perror(src_name);
        exit(1);
    }

    fprintf(stderr, "Read and wrote %ld bytes\n", total);

    /*
     * Close our file pointers, and quit.
     */

    fclose(dest);
    fclose(src);
    return 0;
}
