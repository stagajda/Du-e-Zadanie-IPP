#ifndef DROGI_CITY_H
#define DROGI_CITY_H

//#include "vector_int.h"
#include "vector_road.h"

struct cit{
    // drogi wychodzace z danego miasta
    vector_road *roads;
    // nazwa miasta
    const char * name;
    int id;
};

typedef struct cit city;

city *new_city(const char *, int);

#endif //DROGI_CITY_H
