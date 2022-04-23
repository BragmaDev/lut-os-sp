#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decompress_file(FILE *file);

int main(int argc, char *argv[]) {
    // Check for no arguments
    if (argc == 1) {
        fprintf(stderr, "my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    // Go through all arguments
    for (int i = 1; i < argc; i++) {
        // Open the specified file
        FILE *file = fopen(argv[i], "rb");
        if (file == NULL) {
            fprintf(stderr, "my-unzip: cannot open file\n");
            exit(1);
        }
        decompress_file(file);
        fclose(file);
    }
    return 0;
}

// Read a file (compressed in the RLE format), decompress it and write to stdout
void decompress_file(FILE *file) {
    int n;      // Character count
    char c;

    // Read character counts from the file until fread doesn't return 1
    while (fread(&n, 4, 1, file) == 1) {
        // Read the character following its count
        fread(&c, 1, 1, file);
        // Write the decompressed result
        for (int i = 0; i < n; i++) {
            printf("%c", c);
        }
    }
}
