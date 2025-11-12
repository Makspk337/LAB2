#ifndef SET_H
#define SET_H

#include "hash_table.h"
#include <string>

struct Set {
    HT* table;
};

Set* set_create(int capacity);
void set_add(Set* s, int value);
void set_remove(Set* s, int value);
bool set_contains(Set* s, int value);
void set_free(Set* s);
void set_save(Set* s, const std::string& path);

#endif
