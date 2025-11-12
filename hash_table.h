#ifndef HASH_TABLE_H
#define HASH_TABLE_H

struct HT {
    int* keys;
    int* values;
    char* flags;
    int capacity;
    int count;
};

HT* ht_create(int capacity);
void ht_free(HT* h);
bool ht_insert(HT* h, int key, int value);
bool ht_remove(HT* h, int key);
bool ht_contains(HT* h, int key);
int ht_get(HT* h, int key);
void ht_resize(HT* h, int new_capacity);
int ht_get(HT* h, int key);

struct HTCuckoo {
    int* keys;
    int* values;
    int capacity;
    int count;
};

HTCuckoo* ht_cuckoo_create(int capacity);
void ht_cuckoo_free(HTCuckoo* h);
bool ht_cuckoo_insert(HTCuckoo* h, int key, int value);
bool ht_cuckoo_remove(HTCuckoo* h, int key);
bool ht_cuckoo_contains(HTCuckoo* h, int key);
int ht_cuckoo_get(HTCuckoo* h, int key);
void ht_cuckoo_resize(HTCuckoo* h, int new_capacity);

#endif
