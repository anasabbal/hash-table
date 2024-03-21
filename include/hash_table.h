#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_


// our key-value pairs (items) will each be stored in a struct
typedef struct ht_item{
    char *key;
    char *value;
} ht_item;


// our hash table stores an array of pointers to items, and some details about its size and how full it is:
typedef struct {
    int size;
    int size_index;
    int count;
    ht_item **items;
} ht_hash_table;

// hash_table.h
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);
void ht_del_hash_table(ht_hash_table* ht);
ht_hash_table* ht_new();


#endif  // HASH_TABLE_H_