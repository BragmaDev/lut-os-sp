#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void search_stream(FILE *stream, char *term);


int main(int argc, char *argv[]) {
    // Check for no arguments
    if (argc == 1) {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    }

    // Go through all arguments
    for (int i = 2; i < argc; i++) {
        // Open the file
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "my-grep: cannot open file\n");
            exit(1);
        }
        search_stream(file, argv[1]);
        fclose(file);
    }

    // If no filenames are given, search stdin
    if (argc == 2) {
        search_stream(stdin, argv[1]);
    }

    return 0;
}

// Search a stream for a term
void search_stream(FILE *stream, char *term) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    size_t line_size = 0;

    // Read the first line from the stream
    line_size = getline(&buffer, &buffer_size, stream);

    while (line_size != -1) {
        // Search for the term in the line
        if (strstr(buffer, term) != NULL) {
            printf("%s", buffer);
        }
        // Read the next line
        line_size = getline(&buffer, &buffer_size, stream);
    }
    return;
}
