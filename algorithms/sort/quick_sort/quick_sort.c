#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

// Function to perform Selection Sort
void quick_sort() {
}

int main(int argc, char* argv[]) {

    // Print the array before sorting (optional)
    printf("Array before sorting:\n");
    for (int i = 0; i < 20; i++) {  // Print first 20 elements for brevity
        printf("%d ", list[i]);
    }
    printf("\n");

    clock_t start_time = clock();
    // Perform selection sort
    quick_sort(list, N);

    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\n[QUICK]Time taken to sort array: %.9f seconds\n", time_spent);

    // Print the array after sorting (optional)
    printf("Array after sorting:\n");
    for (int i = 0; i < 20; i++) {  // Print first 20 elements for brevity
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}
