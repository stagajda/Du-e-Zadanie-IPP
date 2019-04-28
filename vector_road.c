#include <stdlib.h>
#include "vector_road.h"
#include "road.h"

vector_road *new_vector_road(){
   vector_road *new_vector;
   new_vector = malloc(sizeof(vector_road));
   new_vector->arr = malloc(10 * sizeof(road *));
   new_vector->arr_size = 10;
   new_vector->length = 0;
   return new_vector;
}

void add_road_to_vec(vector_road *vector1, road *elem){
   vector1->length++;
   if(vector1->length > vector1->arr_size) {
      vector1->arr = realloc(vector1->arr, 2 * vector1->arr_size);
      vector1->arr_size *= 2;
   }
   vector1->arr[vector1->length-1] = elem;
}

road * get_road(int i, vector_road * vector) {
   assert(i < vector->length);
   return vector->arr[i];
}

void reverse(vector_road * vector){
   road * temp;
   for(int i = 0;i < vector->length/2;i++){
      temp = get_road(i, vector);
      vector->arr[i] = vector->arr[vector->length-i-1];
      vector->arr[vector->length-i-1] = temp;
   }
}