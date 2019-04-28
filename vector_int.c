#include <stdlib.h>
#include "vector_int.h"

vector_int *new_vector_int(){
   vector_int *new_vector;
   new_vector = malloc(sizeof(vector_int));
   new_vector->arr = malloc(10*sizeof(int));
   new_vector->arr_size = 10;
   new_vector->length = 0;
   return new_vector;
}

void add(vector_int *vector1, int elem){
   vector1->length++;
   if(vector1->length > vector1->arr_size) {
      vector1->arr = realloc(vector1->arr, 2 * vector1->arr_size);
      vector1->arr_size *= 2;
   }
   vector1->arr[vector1->length-1] = elem;
}

int get(int i, vector_int * vector) {
   assert(i < vector->length);
   return vector->arr[i];
}