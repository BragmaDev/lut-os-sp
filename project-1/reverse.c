#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct line {
    char *ptr;
    struct line *previous;
} line;

void print_output(FILE *stream, line *last_line);


int main(int argc, char *argv[]) {
    // Check the number of arguments and if the input and output files are the same
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    } else if (argc == 3) {
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "input and output file must differ\n");
            exit(1);
        }
    }

    char *line_buffer = NULL;
    line *previous_line = NULL;
    size_t buffer_size = 0;
    size_t line_size = 0;
    FILE *input_file;

    // Open the input file
    if ((input_file = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
        exit(1);
    }

    // Read the first line of the input file
    line_size = getline(&line_buffer, &buffer_size, input_file);
    /* Go through the file until getline returns -1 as the line size, meaning the
    end has been reached */
    while (line_size != -1) {
        // Duplicate the read line
        char *line_dup;
        line_dup = strdup(line_buffer);

        // Create a node for the linked list
        line *new_line;
        if ((new_line = (line*)malloc(sizeof(line))) == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        new_line->ptr = line_dup;
        new_line->previous = previous_line;
        previous_line = new_line;

        // Read the next line
        line_size = getline(&line_buffer, &buffer_size, input_file);
    }

    fclose(input_file);
    free(line_buffer);

    // Print the output
    if (argc == 3) {
        FILE *output_file;
        // Open the output file
        if ((output_file = fopen(argv[2], "w")) == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
        print_output(output_file, previous_line);
        fclose(output_file);
    } else {
        print_output(stdout, previous_line);
    }

    return 0;
}

/* Go through the linked list in reverse order starting from the last line
and print the output to the stream in the first parameter */
void print_output(FILE *stream, line *last_line) {
    line *current = last_line;
        while (current != NULL) {
        last_line = current;
        fprintf(stream, "%s", current->ptr);
        current = current->previous;

        // Free allocated memory
        free(last_line->ptr);
        free(last_line);
    }
    return;
}
