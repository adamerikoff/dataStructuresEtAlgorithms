#include <stdio.h>

void read_lines(char* filename) {
    FILE * file;
    char line[256];

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    // Close the file
    fclose(file);
}


int main(int argc, char *argv[]) {
    // Check if an argument is provided
    if (argc > 1) {
        read_lines(argv[1]);
    } else {
        printf("Hello, World!\n");  // Default greeting
    }

    return 0;
}
