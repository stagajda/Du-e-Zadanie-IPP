#ifndef DROGI_TRACK_H
#define DROGI_TRACK_H

#include <stdbool.h>
#include "city.h"
#include "vector_road.h"

struct trackk {
   int destination_id;
   int year_of_oldest_part;
   int length;
   int previous_city_id;
   road * last_road;
};

typedef struct trackk track;

track * new_track(int);

track * copy_track(track *);

track * extend_track(track *, road *);

bool is_better_track(track *, track *);

#endif //DROGI_TRACK_H
