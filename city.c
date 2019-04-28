#include "city.h"
#include "vector_road.h"

city *new_city(const char * name, int id){
   city *new_city1;
   new_city1 = malloc(sizeof(city));
   new_city1->roads = new_vector_road();
   new_city1->name = name;
   new_city1->id = id;
   return new_city1;
}

