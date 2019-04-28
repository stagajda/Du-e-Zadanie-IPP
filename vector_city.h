#ifndef VECTOR_CITY_H
#define VECTOR_CITY_H
#include <stdlib.h>
#include <assert.h>
#include "city.h"

struct vec_city {
    // tablica wskaznikow na miasto
    city ** arr;
    int arr_size;
    int length;
};
typedef struct vec_city vector_city;

vector_city *new_vector_city();

void add_city_to_vec(vector_city *, city *);

city * get_city(int i, vector_city * vector);

#endif //DROGI_VECTOR_H
