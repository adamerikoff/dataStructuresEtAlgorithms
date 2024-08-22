#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash.h"

hash_table* hash_table_new() {
    hash_table* ht = malloc(sizeof(hash_table));

    ht->size  = 53;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(hash_table_item*));

    return ht;
}

static hash_table_item* hash_table_new_item(const char* key, const char* value) {
    hash_table_item* item = malloc(sizeof(hash_table_item));
    item->key = strdup(key);
    item->value = strdup(value);
    return item;
}

static void hash_table_delete_item(hash_table_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void hash_table_delete(hash_table* ht) {
    for (int i =0; i < ht->size; i++) {
        hash_table_item* item = ht->items[i];
        if(item != NULL) {
            hash_table_delete_item(item);
        }
    }
    free(ht->items);
    free(ht);
}

static int hash_table_hash(const char* s, const int prime, const int bucket_size) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(prime, len_s - (i+1)) * s[i];
        hash = hash % bucket_size;
    }
    return (int)hash;
}
