/*
 * cp-broken <source-file> <destination-file>
 *
 * Copy the contents of <source-file> to <destination-file>.
 *
 * Finally, report the file size (i.e., number of bytes read and written).
 *
 * If <destination-file> already exists, it is overwritten.
 *
 * This implementation is broken because it uses fgets() and fputs(), which do
 * not correctly read and write arbitrary binary content (i.e., null bytes).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    // BUG: using fgets() and fputs() here work if we're only reading textual
    // content, but they will not work with null bytes.
    while (fgets(buf, sizeof(buf), src) != NULL) {
        total += strlen(buf);
        if(fputs(buf, dest) == EOF) {
            // Report any errors we encounter while writing to destination
            perror(dest_name);
            exit(1);
        }
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
