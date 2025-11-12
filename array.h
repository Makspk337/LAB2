#ifndef ARRAY_H
#define ARRAY_H

struct Array {
    int* data;
    int size;
    int capacity;
};

Array* array_create(int initial_capacity);
void array_push_back(Array* a, int v);
int array_get(Array* a, int i);
void array_set(Array* a, int i, int v);
int array_size(Array* a);
void array_free(Array* a);
void array_sort(Array* a);

#endif
