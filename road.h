#ifndef DROGI_ROAD_H
#define DROGI_ROAD_H

#include "vector_int.h"

struct roadd{
    // id's of cities on the ends of road
    int city1_id;
    int city2_id;
    int distance;
    int built_year;
    // ID's of routes which contain this road
    vector_int *routes;
};

typedef struct roadd road;

road *new_road(int, int , int, int);

#endif //DROGI_ROAD_H
