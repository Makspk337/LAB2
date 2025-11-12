#include "hash_table.h"


int next_power_of_two(int n) {
    if (n <= 1) {
        return 2;
    }
    int p = 1;
    while (p < n) {
        p <<= 1;
    }
    return p;
}

HT* ht_create(int capacity) {
    HT* h = new HT;
    h->capacity = next_power_of_two(capacity);
    h->count = 0;
    h->keys = new int[h->capacity];
    h->values = new int[h->capacity];
    h->flags = new char[h->capacity];
    for (int i = 0; i < h->capacity; ++i) {
        h->flags[i] = 0;
    }
    return h;
}

void ht_free(HT* h) {
    delete[] h->keys;
    delete[] h->values;
    delete[] h->flags;
    delete h;
}

int hash1(int key, int cap) {
    unsigned int k = (unsigned int)key;
    k = k * 0x45d9f3b;
    k = k * 0x45d9f3b;
    return k & (cap - 1);
}

int hash2(int key, int cap) {
    unsigned int k = (unsigned int)key;
    k = (k * 2654435761u) + 12345;
    k = (k * 1103515245u) + 67890;
    return k & (cap - 1);
}

bool ht_contains(HT* h, int key) {
    int cap = h->capacity;
    int idx = hash1(key, cap);
    int step = hash2(key, cap);
    for (int i = 0; i < cap; i++) {
        int pos = (idx + i * step) & (cap - 1);
        if (h->flags[pos] == 0) {
            return false;
        }
        if (h->flags[pos] == 1 && h->keys[pos] == key) {
            return true;
        }
    }
    return false;
}

bool ht_insert(HT* h, int key, int value) {
    if ((h->count + 1) * 100 / h->capacity >= 90) {
        ht_resize(h, h->capacity * 2);
    }

    int cap = h->capacity;
    int idx = hash1(key, cap);
    int step = hash2(key, cap);
    int first_deleted = -1;

    for (int i = 0; i < cap; i++) {
        int pos = (idx + i * step) & (cap - 1);
        if (h->flags[pos] == 1 && h->keys[pos] == key) {
            h->values[pos] = value;
            return true;
        }
        if (h->flags[pos] == 2 && first_deleted == -1) {
            first_deleted = pos;
        }
        if (h->flags[pos] == 0) {
            int use = (first_deleted != -1) ? first_deleted : pos;
            h->keys[use] = key;
            h->values[use] = value;
            h->flags[use] = 1;
            h->count++;
            return true;
        }
    }
    return false;
}

bool ht_remove(HT* h, int key) {
    int cap = h->capacity;
    int idx = hash1(key, cap);
    int step = hash2(key, cap);
    for (int i = 0; i < cap; i++) {
        int pos = (idx + i * step) & (cap - 1);
        if (h->flags[pos] == 0) {
            return false;
        }
        if (h->flags[pos] == 1 && h->keys[pos] == key) {
            h->flags[pos] = 2;
            h->count--;
            return true;
        }
    }
    return false;
}

void ht_resize(HT* h, int new_capacity) {
    int nc = (4 > next_power_of_two(new_capacity)) ? 4 : next_power_of_two(new_capacity);
    HT temp;
    temp.capacity = nc;
    temp.count = 0;
    temp.keys = new int[temp.capacity];
    temp.values = new int[temp.capacity];
    temp.flags = new char[temp.capacity];
    for (int i = 0; i < temp.capacity; ++i) temp.flags[i] = 0;

    for (int i = 0; i < h->capacity; i++) {
        if (h->flags[i] == 1) {
            int key = h->keys[i];
            int value = h->values[i];
            int idx = hash1(key, temp.capacity);
            int step = hash2(key, temp.capacity);
            for (int j = 0; j < temp.capacity; j++) {
                int pos = (idx + j * step) & (temp.capacity - 1);
                if (temp.flags[pos] == 0) {
                    temp.flags[pos] = 1;
                    temp.keys[pos] = key;
                    temp.values[pos] = value;
                    temp.count++;
                    break;
                }
            }
        }
    }

    delete[] h->keys;
    delete[] h->values;
    delete[] h->flags;
    *h = temp;
}

int ht_get(HT* h, int key) {
    int cap = h->capacity;
    int idx = hash1(key, cap);
    int step = hash2(key, cap);
    for (int i = 0; i < cap; i++) {
        int pos = (idx + i * step) & (cap - 1);
        if (h->flags[pos] == 0) {
            return -1;
        }
        if (h->flags[pos] == 1 && h->keys[pos] == key) {
            return h->values[pos];
        }
    }
    return -1;
}

HTCuckoo* ht_cuckoo_create(int capacity) {
    HTCuckoo* h = new HTCuckoo;
    h->capacity = next_power_of_two(capacity);
    h->count = 0;
    h->keys = new int[h->capacity];
    h->values = new int[h->capacity];
    for (int i = 0; i < h->capacity; i++) {
        h->keys[i] = -1;
        h->values[i] = 0;
    }
    return h;
}

void ht_cuckoo_free(HTCuckoo* h) {
    delete[] h->keys;
    delete[] h->values;
    delete h;
}

bool ht_cuckoo_insert(HTCuckoo* h, int key, int value) {
    if ((h->count + 1) * 100 / h->capacity >= 90) {
        ht_cuckoo_resize(h, h->capacity * 2);
    }

    int pos1 = hash1(key, h->capacity);
    int pos2 = hash2(key, h->capacity);

    if (h->keys[pos1] == key) {
        h->values[pos1] = value;
        return true;
    }
    if (h->keys[pos2] == key) {
        h->values[pos2] = value;
        return true;
    }

    if (h->keys[pos1] == -1) {
        h->keys[pos1] = key;
        h->values[pos1] = value;
        h->count++;
        return true;
    }
    if (h->keys[pos2] == -1) {
        h->keys[pos2] = key;
        h->values[pos2] = value;
        h->count++;
        return true;
    }

    int current_key = key, current_value = value, table = 0;
    for (int i = 0; i < h->capacity * 2; i++) {
        int pos = (table == 0) ? hash1(current_key, h->capacity)
                               : hash2(current_key, h->capacity);

        int tmp_key = current_key;
        current_key = h->keys[pos];
        h->keys[pos] = tmp_key;

        int tmp_value = current_value;
        current_value = h->values[pos];
        h->values[pos] = tmp_value;

        if (current_key == -1) {
            h->count++;
            return true;
        }
        table = 1 - table;
    }
    ht_cuckoo_resize(h, h->capacity * 2);
    return ht_cuckoo_insert(h, current_key, current_value);
}

bool ht_cuckoo_remove(HTCuckoo* h, int key) {
    int pos1 = hash1(key, h->capacity);
    int pos2 = hash2(key, h->capacity);
    if (h->keys[pos1] == key) {
        h->keys[pos1] = -1;
        h->values[pos1] = 0;
        h->count--;
        return true;
    }
    if (h->keys[pos2] == key) {
        h->keys[pos2] = -1;
        h->values[pos2] = 0;
        h->count--;
        return true;
    }
    return false;
}

bool ht_cuckoo_contains(HTCuckoo* h, int key) {
    int pos1 = hash1(key, h->capacity);
    int pos2 = hash2(key, h->capacity);
    return (h->keys[pos1] == key) || (h->keys[pos2] == key);
}

int ht_cuckoo_get(HTCuckoo* h, int key) {
    int pos1 = hash1(key, h->capacity);
    int pos2 = hash2(key, h->capacity);
    if (h->keys[pos1] == key) {
        return h->values[pos1];
    }
    if (h->keys[pos2] == key) {
        return h->values[pos2];
    }
    return -1;
}

void ht_cuckoo_resize(HTCuckoo* h, int new_capacity) {
    int nc = (4 > next_power_of_two(new_capacity)) ? 4 : next_power_of_two(new_capacity);
    HTCuckoo temp;
    temp.capacity = nc;
    temp.count = 0;
    temp.keys = new int[temp.capacity];
    temp.values = new int[temp.capacity];
    for (int i = 0; i < temp.capacity; i++) {
        temp.keys[i] = -1;
        temp.values[i] = 0;
    }

    for (int i = 0; i < h->capacity; i++) {
        if (h->keys[i] != -1) {
            ht_cuckoo_insert(&temp, h->keys[i], h->values[i]);
        }
    }

    delete[] h->keys;
    delete[] h->values;
    *h = temp;
}
