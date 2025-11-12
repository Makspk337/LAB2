#include "set.h"
#include <fstream>

Set* set_create(int capacity) {
    Set* s = new Set;
    s->table = ht_create(capacity);
    return s;
}

void set_add(Set* s, int value) {
    ht_insert(s->table, value, value);
}

void set_remove(Set* s, int value) {
    ht_remove(s->table, value);
}

bool set_contains(Set* s, int value) {
    return ht_contains(s->table, value);
}

void set_free(Set* s) {
    ht_free(s->table);
    delete s;
}

void set_save(Set* s, const std::string& path) {
    std::ofstream out(path, std::ios::trunc);
    if (!out.is_open()) {
        return;
    }

    bool first = true;
    for (int i = 0; i < s->table->capacity; i++) {
        if (s->table->flags[i] == 1) {
            if (!first) {
                out << " ";
            }
            out << s->table->keys[i];
            first = false;
        }
    }
}
