#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#include "../include/hash_table.h"


//#define HT_PRIME_1 151;
//#define HT_PRIME_2 163;

static ht_item HT_DELETED_ITEM = {NULL, NULL};

/* define a macro for logging */
// Define custom log function
#define LOG(message) printf("[LOG] %s\n", message)

static ht_item *ht_new_item(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    if (i == NULL) {
        LOG("Failed to allocate memory for ht_item");
        return NULL;
    }
    i->key = strdup(k);
    if (i->key == NULL) {
        LOG("Failed to allocate memory for key");
        free(i);
        return NULL;
    }
    i->value = strdup(v);
    if (i->value == NULL) {
        LOG("Failed to allocate memory for value");
        free(i->key);
        free(i);
        return NULL;
    }
    printf("Memory address of ht: %p\n", (void*)i);
    return i;
}

ht_hash_table* ht_new() {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    if (ht == NULL) {
        LOG("Failed to allocate memory for ht_hash_table");
        return NULL;
    }
    ht->size = 53;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    if (ht->items == NULL) {
        LOG("Failed to allocate memory for items array");
        free(ht);
        return NULL;
    }
    printf("Memory address of ht: %p\n", (void*)ht);
    return ht;
}

static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
    printf("Memory address of i: %p\n", (void*)i);
}

void ht_del_hash_table(ht_hash_table* ht) {
    if (ht == NULL) {
        LOG("Attempted to delete NULL ht_hash_table");
        return;
    }
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
    printf("Memory address of ht: %p\n", (void*)ht);
}
static int ht_hash(const char *s, const int a, const int m){
    long hash = 0;
    const int len_s = strlen(s);
    for(int i = 0; i < len_s; i++){
        //printf("Iteration %d:\n", i + 1);
        //printf(" - Current character: %c\n", s[i]);
        //printf(" - Current length of string: %d\n", len_s - (i + 1));
        hash += (long)pow(a, len_s - (i+1)) *s[i];
        //printf(" - Current hash value: %ld\n", hash);
        hash = hash % m;
    }
    printf("Final hash value = %ld\n", hash);
    return (int)hash;
}
static int ht_get_hash(const char *s, const int num_buckets, const int attempt){
    const int hash_a = ht_hash(s, 151, num_buckets);
    const int hash_b = ht_hash(s, 163, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    ht_item* item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL) {
        if(cur_item != &HT_DELETED_ITEM){
            if(strcmp(cur_item->key, key) == 0){
                ht_del_item(cur_item);
                ht->items[index] = item;
                return;
            }
        }
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    } 
    ht->items[index] = item;
    ht->count++;
}
char* ht_search(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if(item != &HT_DELETED_ITEM){
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    return NULL;
}
void ht_delete(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    ht->count--;
}