#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define INIT_SIZE 13

typedef struct {
    char* key;
    int value;
    int is_occupied;
} Entry;

typedef struct {
    Entry* entries;
    int size;
    int capacity;
} HashTable;

HashTable* create_table();
uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length);
unsigned int hash(const char* key);
unsigned int double_hash(const char* key, int attempt);
void insert(HashTable* ht, const char* key, int value);
int search(HashTable* ht, const char* key);
void remove_entry(HashTable* ht, const char* key);
void resize_table(HashTable* ht, int new_capacity);
void free_table(HashTable* ht);

int is_prime(int number);
int get_next_prime(int prime);
void log_message(const char* message);

int main() {
    HashTable* ht = create_table();
    log_message("Hash table created.");

    // Insert entries
    insert(ht, "apple", 1);
    log_message("Inserted: apple -> 1");

    insert(ht, "banana", 2);
    log_message("Inserted: banana -> 2");

    // Search for entries
    int value = search(ht, "banana");
    printf("Value for 'banana': %d\n", value); // Output: 2
    log_message("Searched for 'banana'.");

    // Attempt to search for a non-existent key
    value = search(ht, "grape");
    if (value == -1) {
        log_message("Key 'grape' not found.");
    } else {
        printf("Value for 'grape': %d\n", value);
    }

    // Remove an entry
    remove_entry(ht, "apple");
    log_message("Removed: apple");

    // Attempt to search for the removed key
    value = search(ht, "apple");
    if (value == -1) {
        log_message("Key 'apple' not found after removal.");
    } else {
        printf("Value for 'apple': %d\n", value);
    }

    // Free the hash table
    free_table(ht);
    log_message("Hash table freed.");
    return 0;
}

// Function to log messages
void log_message(const char* message) {
    printf("[LOG] %s\n", message);
}

int is_prime(int number) {
    if (number <= 1) {
        return 0;
    }
    if (number == 2 || number == 3) {
        return 1;
    }
    if (number % 2 == 0 || number % 3 == 0) {
        return 0;
    }
    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

int get_next_prime(int prime) {
    prime++;
    while (!is_prime(prime)) {
        prime++;
    }
    return prime;
}

HashTable* create_table() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    table->entries = (Entry*)calloc(INIT_SIZE, sizeof(Entry));
    if (table->entries == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(table);
        return NULL;
    }
    table->size = INIT_SIZE;
    table->capacity = 0;
    return table;
}

uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length) {
    size_t i = 0;
    uint32_t hash = 0;
    while (i != length) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

unsigned int hash(const char* key) {
    return jenkins_one_at_a_time_hash((const uint8_t*)key, strlen(key));
}

unsigned int double_hash(const char* key, int attempt) {
    unsigned int hash1 = hash(key);
    unsigned int hash2 = 1 + (hash(key) % (INIT_SIZE - 1));
    return (hash1 + attempt * hash2) % INIT_SIZE;
}

void insert(HashTable* ht, const char* key, int value) {
    float load_factor = (float)ht->size / (float)ht->capacity;
    if (load_factor > 0.4) {
        resize_table(ht, get_next_prime(ht->size * 2));
    }

    int attempt = 0;
    unsigned int idx;
    do {
        idx = double_hash(key, attempt++);
        if (!ht->entries[idx].is_occupied) {
            ht->entries[idx].key = strdup(key);
            ht->entries[idx].value = value;
            ht->entries[idx].is_occupied = 1;
            ht->capacity++;
            return;
        }
    } while (attempt < ht->size);
}

int search(HashTable* ht, const char* key) {
    int attempt = 0;
    unsigned int idx;
    do {
        idx = double_hash(key, attempt++);
        if (ht->entries[idx].is_occupied && strcmp(ht->entries[idx].key, key) == 0) {
            return ht->entries[idx].value;
        }
    } while (ht->entries[idx].is_occupied && attempt < ht->size);
    return -1;
}

void resize_table(HashTable* ht, int new_capacity) {
    Entry* old_entries = ht->entries;
    int old_size = ht->size;

    ht->entries = (Entry*)calloc(new_capacity, sizeof(Entry));
    ht->size = new_capacity;
    ht->capacity = 0;

    for (int i = 0; i < old_size; i++) {
        if (old_entries[i].is_occupied) {
            insert(ht, old_entries[i].key, old_entries[i].value);
        }
    }

    free(old_entries);
}

void remove_entry(HashTable* ht, const char* key) {
    int attempt = 0;
    unsigned int idx;
    do {
        idx = double_hash(key, attempt++);
        if (ht->entries[idx].is_occupied && strcmp(ht->entries[idx].key, key) == 0) {
            ht->entries[idx].is_occupied = 0;
            ht->capacity--;
            free(ht->entries[idx].key);
            return;
        }
    } while (ht->entries[idx].is_occupied && attempt < ht->size);
}

void free_table(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->entries[i].is_occupied) {
            free(ht->entries[i].key);
        }
    }
    free(ht->entries);
    free(ht);
}
