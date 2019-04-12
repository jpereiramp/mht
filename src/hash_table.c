//
// minimal hash table
// hash_table.c
//
// Created by Joao Pereira, 2019. 
//

#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

// mht_new_item
// creates a new item to be inserted in a mht_hash_table
// returns the newly created item.
static mht_item* mht_new_item(const char* key, const char* value) {
    mht_item* item = malloc(sizeof(mht_item));
    item->key = strdup(key);
    item->value = strdup(value);
    return item;
}

// mht_new
// creates a new hash table, allocating memory as
// necessary.
// returns the newly created hash table.
mht_hash_table* mht_new() {
    mht_hash_table* mht = malloc(sizeof(mht_hash_table));
    mht->size = 53;
    mht->count = 0;
    mht->items = calloc((size_t)mht->size, sizeof(mht_item));
    return mht;
}

// mht_delete_item
// frees a given mht_item from memory
static void mht_delete_item(mht_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

// mht_delete_hash_table
// deletes a hash table, freeing itself and all
// its items from memory.
void mht_delete_hash_table(mht_hash_table* mht) {
    for(int i = 0; i < mht->size; i++) {
        mht_item* item = mht->items[i];
        if (item != NULL) {
            mht_delete_item(item);
        }
    }
    free(mht->items);
    free(mht);
}