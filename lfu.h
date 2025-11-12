#ifndef LFU_H
#define LFU_H

#include <string>
#include "hash_table.h"

using namespace std;

struct LFUCache {
    HT* hash_table;
    int* keys;
    int* freq;
    int* time;
    int size;
    int capacity;
    int timer;
};

LFUCache* lfu_create(int capacity);
void lfu_set(LFUCache* c, int key, int value);
int lfu_get(LFUCache* c, int key);
void lfu_free(LFUCache* c);
LFUCache* lfu_load(const string& path);
void lfu_save(LFUCache* c, const string& path);

#endif
