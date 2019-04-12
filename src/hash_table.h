//
// minimal hash table
// hash_table.h
//
// Created by Joao Pereira, 2019. 
//

// ht_item
// holds a single entry in the hash table,
// with its key and value.
typedef struct {
    char* key;
    char *value;
} ht_item;

// ht_hash_table
// holds a hash table, along with its size
// in bytes, count of items and a pointer to
// a list of items.
typedef struct {
    int size;
    int count;
    ht_item **items;
} ht_hash_table;