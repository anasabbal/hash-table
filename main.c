// main.c
#include <stdio.h>
#include <stdlib.h>

#include "include/hash_table.h"


int main() {
    ht_hash_table* ht = ht_new();

    // test insert
    ht_insert(ht, "key1", "value1");
    //ht_insert(ht, "key2", "value2");
    //ht_insert(ht, "key3", "value3");

    // search for a key
    char* result = ht_search(ht, "key2");
    if (result != NULL) {
        printf("Value for key2: %s\n", result);
    } else {
        printf("Key2 not found\n");
    }

    // delete a key
    ht_delete(ht, "key2");

    // search for the deleted key
    result = ht_search(ht, "key2");
    if (result != NULL) {
        printf("Value for key2: %s\n", result);
    } else {
        printf("Key2 not found after deletion\n");
    }

    ht_del_hash_table(ht);

    return 0;
}