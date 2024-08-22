typedef struct {
    char* key;
    char* value;
} htable_element;

typedef struct {
    int size;
    int count;
    htable_element** items;
} htable;

htable* htable_new();
void htable_delete_table(htable* ht);
void htable_insert(htable* ht, const char* key, const char* value);
char* htable_search(htable* ht, const char* key);
void htable_delete(htable* ht, const char* key);
