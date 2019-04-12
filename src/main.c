//
// minimal hash table
// main.c
//
// Created by Joao Pereira, 2019. 
//

#include "hash_table.h"

int main() {
    mht_hash_table* mht = mht_new();
    mht_delete_hash_table(mht);
    return 0;
}