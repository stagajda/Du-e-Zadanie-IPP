#ifndef VECTOR_INT_H
#define VECTOR_INT_H
#include <stdlib.h>
#include <assert.h>

struct vec_int {
    int *arr;
    int arr_size;
    int length;
};
typedef struct vec_int vector_int;

vector_int *new_vector_int();

void add(vector_int *, int);

int get(int i, vector_int * vector);

#endif //DROGI_VECTOR_H
