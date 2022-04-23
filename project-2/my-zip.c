#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compress_file(FILE *file);

int main(int argc, char *argv[]) {
    // Check for no arguments
    if (argc == 1) {
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    // Go through all arguments
    for (int i = 1; i < argc; i++) {
        // Open the specified file
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "my-zip: cannot open file\n");
            exit(1);
        }
        compress_file(file);
        fclose(file);
    }
    return 0;
}

// Read a file, compress it with RLE and write to stdout
void compress_file(FILE *file) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    size_t line_size = 0;
    int n = 1;  // Number of times a character appears in a row
    char c;

    // Read the first line from the file
    line_size = getline(&buffer, &buffer_size, file);
    while (line_size != -1) {
        // Go through the line character by character
        for (int i = 0; i < line_size; i++) {
            // Check if the next character is the same
            if (buffer[i] == buffer[i+1]) {
                n++;
            } else {
                // Set the current character
                c = buffer[i];
                // Write the character's count
                fwrite(&n, 4, 1, stdout);
                // Write the character
                fwrite(&c, 1, 1, stdout);
                // Reset the character count
                n = 1;
            }
        }
        // Read the next line
        line_size = getline(&buffer, &buffer_size, file);
    }
}
