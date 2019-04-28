#ifndef DROGI_ROUTE_H
#define DROGI_ROUTE_H
#include "city.h"

// city1 - miasto lezace na poczatku drogi krajowej
// city2 - miasto lezace na koncu drogi krajowej
struct rout {
    city * city1;
    city * city2;
    vector_road * parts;
    int id;
};

typedef struct rout route;

route * new_route(int, city *, city *);

#endif
