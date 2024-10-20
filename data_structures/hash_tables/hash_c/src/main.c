#include <stdio.h>
#include "hash.h"

int main() {
    // Create a new hash table
    htable* ht = htable_new();

    // Insert key-value pairs into the hash table
    htable_insert(ht, "name", "John Doe");
    htable_insert(ht, "age", "30");
    htable_insert(ht, "email", "johndoe@example.com");
    htable_insert(ht, "address", "123 Main St");

    // Search for values by key
    char* name = htable_search(ht, "name");
    char* age = htable_search(ht, "age");
    char* email = htable_search(ht, "email");
    char* address = htable_search(ht, "address");

    // Display the retrieved values
    printf("Name: %s\n", name);
    printf("Age: %s\n", age);
    printf("Email: %s\n", email);
    printf("Address: %s\n", address);

    // Delete an item from the hash table
    htable_delete(ht, "age");

    // Try to retrieve the deleted item
    char* deleted_age = htable_search(ht, "age");
    if (deleted_age == NULL) {
        printf("Age entry has been deleted.\n");
    }

    // Clean up and free the hash table
    htable_delete_table(ht);

    return 0;
}
