#include <stdlib.h>
#include "vector_city.h"
#include "city.h"

vector_city *new_vector_city(){
   vector_city *new_vector;
   new_vector = malloc(sizeof(vector_city));
   new_vector->arr = malloc(10*sizeof(int));
   new_vector->arr_size = 10;
   new_vector->length = 0;
   return new_vector;
}

void add_city_to_vec(vector_city *vector1, city *elem){
   vector1->length++;
   if(vector1->length > vector1->arr_size) {
      vector1->arr = realloc(vector1->arr, 2 * vector1->arr_size);
      vector1->arr_size *= 2;
   }
   vector1->arr[vector1->length-1] = elem;
}

city * get_city(int i, vector_city * vector) {
   assert(i < vector->length);
   return vector->arr[i];
}