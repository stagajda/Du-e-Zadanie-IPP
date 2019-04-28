#ifndef DROGI_VECTOR_TRACK_H
#define DROGI_VECTOR_TRACK_H

#include <stdlib.h>
#include <assert.h>
#include "track.h"

struct vec_track {
    // tablica wskaznikow na trasy
    track ** arr;
    int arr_size;
    int length;
};
typedef struct vec_track vector_track;

vector_track *new_vector_track();

void add_track_to_vec(vector_track *, track *);

track * get_track(int i, vector_track * vector);


#endif //DROGI_VECTOR_TRACK_H
