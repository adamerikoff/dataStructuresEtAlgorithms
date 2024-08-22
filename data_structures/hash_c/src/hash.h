typedef struct {
    char* key;
    char* value;
} htable_element;

typedef struct {
    int size;
    int count;
    htable_element** items;
} htable;
