typedef struct {
    char* key;
    char* value;
} htable_element;

typedef struct {
    int base_size;
    int size;
    int count;
    htable_element** items;
} htable;

#define HTABLE_INITIAL_BASE_SIZE 53
#define HTABLE_PRIME_1 151
#define HTABLE_PRIME_2 163

htable* htable_new();
void htable_delete_table(htable* ht);

// api
void htable_insert(htable* ht, const char* key, const char* value);
char* htable_search(htable* ht, const char* key);
void htable_delete(htable* ht, const char* key);
