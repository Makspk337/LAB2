#include "lfu.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

LFUCache* lfu_create(int capacity) {
    LFUCache* c = new LFUCache;
    c->capacity = capacity;
    c->size = 0;
    c->timer = 0;
    c->hash_table = ht_create(capacity);
    c->keys = new int[capacity];
    c->freq = new int[capacity];
    c->time = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        c->keys[i] = -1;
        c->freq[i] = 0;
        c->time[i] = 0;
    }
    return c;
}

static int find_key(LFUCache* c, int key) {
    for (int i = 0; i < c->size; i++) {
        if (c->keys[i] == key) {
            return i;
        }
    }
    return -1;
}

int lfu_get(LFUCache* c, int key) {
    if (c->capacity == 0) return -1;
    
    int idx = find_key(c, key);
    if (idx != -1) {
        c->freq[idx]++;
        c->time[idx] = ++c->timer;
        return ht_get(c->hash_table, key);
    }
    return -1;
}

void lfu_set(LFUCache* c, int key, int value) {
    if (c->capacity == 0) return;
    
    c->timer++;

    int idx = find_key(c, key);
    if (idx != -1) {
        ht_insert(c->hash_table, key, value);
        c->freq[idx]++;
        c->time[idx] = c->timer;
        return;
    }

    if (c->size < c->capacity) {
        ht_insert(c->hash_table, key, value);
        c->keys[c->size] = key;
        c->freq[c->size] = 1;
        c->time[c->size] = c->timer;
        c->size++;
        return;
    }

    int lfu_idx = 0;
    for (int i = 1; i < c->size; i++) {
        if (c->freq[i] < c->freq[lfu_idx] ||
            (c->freq[i] == c->freq[lfu_idx] && c->time[i] < c->time[lfu_idx])) {
            lfu_idx = i;
        }
    }

    int old_key = c->keys[lfu_idx];
    ht_remove(c->hash_table, old_key);
    ht_insert(c->hash_table, key, value);
    
    c->keys[lfu_idx] = key;
    c->freq[lfu_idx] = 1;
    c->time[lfu_idx] = c->timer;
}

void lfu_free(LFUCache* c) {
    if (c) {
        ht_free(c->hash_table);
        delete[] c->keys;
        delete[] c->freq;
        delete[] c->time;
        delete c;
    }
}

LFUCache* lfu_load(const string& path) {
    ifstream in(path);
    if (!in.is_open()) {
        return lfu_create(2);
    }
    int cap;
    if (!(in >> cap)) {
        cap = 2;
    }
    LFUCache* c = lfu_create(cap);
    
    int k, v, f, t;
    while (in >> k >> v >> f >> t) {
        lfu_set(c, k, v);
        int idx = find_key(c, k);
        if (idx != -1) {
            c->freq[idx] = f;
            c->time[idx] = t;
        }
    }
    in.close();
    return c;
}


void lfu_save(LFUCache* c, const string& path) {
    ofstream out(path, ios::trunc);
    if (!out.is_open()) {
        return;
    }
    out << c->capacity << "\n";
    for (int i = 0; i < c->size; i++) {
        int key = c->keys[i];
        out << key << " " << ht_get(c->hash_table, key) << " "
            << c->freq[i] << " " << c->time[i] << "\n";
    }
    out.close();
}
