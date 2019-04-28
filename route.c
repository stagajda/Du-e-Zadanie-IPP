#include "route.h"
#include "city.h"


route * new_route(int id, city * city1, city * city2){
   route * created_route = malloc(sizeof(route));
   created_route->city1 = city1;
   created_route->city2 = city2;
   created_route->id = id;
   created_route->parts = new_vector_road();
}
