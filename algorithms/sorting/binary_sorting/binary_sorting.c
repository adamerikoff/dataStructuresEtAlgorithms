#include <stdio.h>

int main(int argc, char *argv[]) {
    // Check if an argument is provided
    if (argc > 1) {
        printf("Hello, %s!\n", argv[1]);  // Greet the argument
    } else {
        printf("Hello, World!\n");  // Default greeting
    }

    return 0;
}
