#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512


int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE];

    // Go through all arguments
    for (int i = 1; i < argc; i++) {
        // Open the file
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "my-cat: cannot open file\n");
            exit(1);
        }

        // Read the file until the end is reached
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }

        fclose(file);
    }

    return 0;
}
