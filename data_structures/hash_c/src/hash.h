typedef struct {
    char* key;
    char* value;
} hash_table_item;

typedef struct {
    int size;
    int count;
    hash_table_item** items;
} hash_table;


static hash_table_item* hash_table_new_item(const char* key, const char* value);
hash_table* hash_table_new();
static void hash_table_delete_item(hash_table_item* item);
void hash_table_delete(hash_table* ht);
