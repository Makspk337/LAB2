#include "array.h"

Array* array_create(int initial_capacity) {
    if (initial_capacity < 1) {
        initial_capacity = 4;
    }
    Array* a = new Array;
    a->capacity = initial_capacity;
    a->size = 0;
    a->data = new int[a->capacity];
    return a;
}

void array_push_back(Array* a, int v) {
    if (a->size >= a->capacity) {
        a->capacity *= 2;
        int* nd = new int[a->capacity];
        for (int i = 0; i < a->size; i++) {
            nd[i] = a->data[i];
        }
        delete[] a->data;
        a->data = nd;
    }
    a->data[a->size++] = v;
}

int array_get(Array* a, int i) {
    if (i < 0 || i >= a->size) {
        return 0;
    }
    return a->data[i];
}

void array_set(Array* a, int i, int v) {
    if (i < 0 || i >= a->size) {
        return;
    }
    a->data[i] = v;
}

int array_size(Array* a) {
    return a->size;
}

void array_free(Array* a) {
    delete[] a->data;
    delete a;
}

static void qsort_inplace(int* data, int l, int r) {
    if (l >= r) {
        return;
    }
    int i = l, j = r, pivot = data[(l + r) / 2];
    while (i <= j) {
        while (data[i] < pivot) {
            i++;
        }
        while (data[j] > pivot) {
            j--;
        }
        if (i <= j) {
            int t = data[i]; data[i] = data[j]; data[j] = t;
            i++; j--;
        }
    }
    if (l < j) {
        qsort_inplace(data, l, j);
    }
    if (i < r){
        qsort_inplace(data, i, r);
    }
}

void array_sort(Array* a) {
    if (a->size > 0) {
        qsort_inplace(a->data, 0, a->size - 1);
    }
}
