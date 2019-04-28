#include <stdlib.h>
#include "road.h"
#include  "vector_int.h"
#include "city.h"

road *new_road(int city1_id, int city2_id, int length, int built_year){
   road *new_road;
   new_road = malloc(sizeof(road));
   new_road->routes = new_vector_int();
   new_road->city1_id = city1_id;
   new_road->city2_id = city2_id;
   new_road->distance = length;
   new_road->built_year = built_year;
}


