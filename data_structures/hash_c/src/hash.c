#include <stdlib.h>
#include <string.h>

#include "hash.h"


static hash_table_item* hash_table_new_item(const char* key, const char* value) {
    hash_table_item* i = malloc(sizeof(hash_table_item));
    i->key = strdup(key);
    i->value = strdup(value);
    return i;
}
