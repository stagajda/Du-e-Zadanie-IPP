// DO ROZWAZENIA, CZY W MALLOCU TRACK, czy TRACK *
#include <stdlib.h>
#include "vector_track.h"
#include "track.h"

vector_track *new_vector_track(){
   vector_track *new_vector;
   new_vector = malloc(sizeof(vector_track));
   new_vector->arr = malloc(10*sizeof(track *));
   new_vector->arr_size = 10;
   new_vector->length = 0;
   return new_vector;
}

void add_track_to_vec(vector_track *vector1, track *elem){
   vector1->length++;
   if(vector1->length > vector1->arr_size) {
      vector1->arr = realloc(vector1->arr, 2 * vector1->arr_size);
      vector1->arr_size *= 2;
   }
   vector1->arr[vector1->length-1] = elem;
}

track * get_track(int i, vector_track * vector) {
   assert(i < vector->length);
   return vector->arr[i];
}
