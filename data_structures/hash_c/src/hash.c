#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash.h"
#include "helper_prime.h"

static htable_element HTABLE_DELETED_ITEM = {NULL, NULL};

static htable_element* htable_new_element(const char* key, const char* value) {
    htable_element* item = malloc(sizeof(htable_element));
    if (item == NULL) {
        return NULL;
    }

    item->key = strdup(key);
    if (item->key == NULL) {
        free(item);
        return NULL;
    }
    item->value = strdup(value);
    if (item->value == NULL) {
        free(item->key);
        free(item);
        return NULL;
    }

    return item;
}

static htable* htable_new_sized(const int base_size) {
    htable* ht = malloc(sizeof(htable));
    if (ht == NULL) {
        return NULL;
    }

    ht->base_size = base_size;

    ht->size = next_prime(ht->base_size);

    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(htable_element*));
    if (ht->items == NULL) {
        free(ht);
        return NULL;
    }

    return ht;
}

htable* htable_new() {
    return htable_new_sized(HTABLE_INITIAL_BASE_SIZE);
}

static void htable_resize(htable* ht, const int base_size) {
    if (base_size < HTABLE_INITIAL_BASE_SIZE) {
        return;
    }
    htable* new_ht = htable_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        htable_element* item = ht->items[i];
        if (item != NULL && item != &HTABLE_DELETED_ITEM) {
            htable_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    htable_element** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    htable_delete_table(new_ht);
}

static void htable_resize_up(htable* ht) {
    const int new_size = ht->base_size * 2;
    htable_resize(ht, new_size);
}

static void htable_resize_down(htable* ht) {
    const int new_size = ht->base_size / 2;
    htable_resize(ht, new_size);
}

static void htable_delete_element(htable_element* item) {
    if (item == NULL) {
        return;
    }
    free(item->key);
    free(item->value);
    free(item);
}

void htable_delete_table(htable* ht) {
    for (int i =0; i < ht->size; i++) {
        htable_element* item = ht->items[i];
        if(item != NULL) {
            htable_delete_element(item);
        }
    }
    free(ht->items);
    free(ht);
}

static int htable_hash(const char* s, const int prime, const int bucket_size) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(prime, len_s - (i+1)) * s[i];
        hash = hash % bucket_size;
    }
    return (int)hash;
}

static int htable_get_hash(const char* s, const int num_buckets, const int attempt) {
    const int hash_a = htable_hash(s, HTABLE_PRIME_1, num_buckets);
    const int hash_b = htable_hash(s, HTABLE_PRIME_2, num_buckets);

    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void htable_insert(htable* ht, const char* key, const char* value) {
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        htable_resize_up(ht);
    }

    htable_element* item = htable_new_element(key, value);
    int index = htable_get_hash(item->key, ht->size, 0);
    htable_element* current_item = ht->items[index];
    int i = 1;
    while (current_item != NULL) {
        if (current_item != &HTABLE_DELETED_ITEM) {
            if (strcmp(current_item->key, key) == 0) {
                htable_delete_element(current_item);
                ht->items[index] = item;
                return;
            }
        }
        index = htable_get_hash(item->key, ht->size, i);
        current_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}

char* htable_search(htable* ht, const char* key) {
    int index = htable_get_hash(key, ht->size, 0);
    htable_element* item = ht->items[index];
    int i = 1;
    while(item != NULL) {
        if (item != &HTABLE_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        index = htable_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

void htable_delete(htable* ht, const char* key) {
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        htable_resize_down(ht);
    }

    int index = htable_get_hash(key, ht->size, 0);
    htable_element* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HTABLE_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                htable_delete_element(item);
                ht->items[index] = &HTABLE_DELETED_ITEM;
            }
        }
        index = htable_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}
