#ifndef vector_road_H
#define vector_road_H
#include <stdlib.h>
#include <assert.h>
#include "road.h"

struct vec_road {
    road **arr;
    int arr_size;
    int length;
};
typedef struct vec_road vector_road;

vector_road *new_vector_road();

road * xd();

void add_road_to_vec(vector_road *, road *);

road * get_road(int i, vector_road * vector);

void reverse(vector_road * vector);
#endif //DROGI_VECTOR_H
