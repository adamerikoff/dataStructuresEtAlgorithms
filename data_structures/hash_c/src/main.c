#include <stdio.h>

#include "hash.h"

int main() {
    // Create a new hash table
    hash_table* ht = hash_table_new();

    // Print the address and size of the hash table
    printf("Hash Table Address: %p\n", (void*)ht);
    printf("Hash Table Size: %d\n", ht->size);
    printf("Hash Table Count: %d\n", ht->count);

    // Iterate through the hash table and print the address and contents of each element
    for (int i = 0; i < ht->size; i++) {
        hash_table_item* item = ht->items[i];
        if (item != NULL) {
            printf("Item %d Address: %p\n", i, (void*)item);
            printf("Item %d Key Address: %p, Key: %s\n", i, (void*)item->key, item->key);
            printf("Item %d Value Address: %p, Value: %s\n", i, (void*)item->value, item->value);
        } else {
            printf("Item %d is NULL\n", i);
        }
    }

    // Clean up
    hash_table_delete(ht);

    return 0;
}
