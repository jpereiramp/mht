//
// minimal hash table
// hash_table.c
//
// Created by Joao Pereira, 2019. 
//

#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

#define MHT_PRIME_A 68371
#define MHT_PRIME_B 104729

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

// mht_hash
// private function to generate a hash given
// the entry's value, a prime number bigger than the
// alphabet from the entry, and the count of total buckets
// to use.
// returns the generated hash as integer.
static int mht_hash(const char* string, 
                    const int prime, 
                    const int buckets_count) {
    long hash = 0;
    const int str_len = strlen(string);

    for (int i = 0; i < str_len; i++) {
        hash += (long)pow(prime, str_len - (i+1)) * string[i];
        hash = hash % buckets_count;
    }
    return (int)hash;
}

// mht_get_hash
// handles hash collisions via open addressing with double hashing.
// we use two hash functions to calculate the index an entry should
// be stored at after `i` collisions.
static int mht_get_hash(const char* string, 
                        const int buckets_count, 
                        const int attempt_count) {
    const int hash_a = mht_hash(string, MHT_PRIME_A, buckets_count);
    const int hash_b = mht_hash(string, MHT_PRIME_B, buckets_count);
    return (hash_a + (attempt_count * (hash_b + 1))) % buckets_count;
}

/**
 * API Functions
 **/

// mht_insert(hash_table, key, value)
// inserts a new element in the given hash table,
// iterating through index until we find an empty bucket.
void mht_insert(mht_hash_table* mht, 
                const char* key,
                const char* value) {
    mht_item* item = mht_new_item(key, value);
    int index = mht_get_hash(item->key, mht->size, 0);
    mht_item* curr_item = mht->items[index];
    int i = 1;

    while(curr_item != NULL) {
        index = mht_get_hash(item->key, mht->size, i);
        curr_item = mht->items[index];
        i++;
    }
    mht->items[index] = item;
    mht->count++;
}