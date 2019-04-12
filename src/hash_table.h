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
    char* value;
} mht_item;

// ht_hash_table
// holds a hash table, along with its size
// in bytes, count of items and a pointer to
// a list of items.
typedef struct {
    int size;
    int count;
    mht_item** items;
} mht_hash_table;