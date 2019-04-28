// kolejka priorytetowa tras
#include "priority_queue.h"
#include "vector_track.h"
#include <stdio.h>

priority_queue * new_priority_queue(){
   priority_queue * queue = malloc(sizeof(priority_queue));
   queue->elem_list = new_vector_track();
   track * blocker = new_track(-1);
   add_track_to_vec(queue->elem_list, blocker);
   return queue;
}

void add_to_queue(priority_queue * queue, track * track1) {
   add_track_to_vec(queue->elem_list, track1);
   int index = (queue->elem_list)->length - 1;
   while (index > 1) {
      // jezeli ten nowy jest lepszy
      if (!is_better_track(get_track(index / 2, queue->elem_list), track1)) {
         queue->elem_list->arr[index] = queue->elem_list->arr[index / 2];
         queue->elem_list->arr[index / 2] = track1;
      }
      else {
         break;
      }
      index = index / 2;
   }
}
   int size(priority_queue * queue) {
      return queue->elem_list->length-1;
   }

   bool is_empty(priority_queue * queue){
      return size(queue) == 0;
   }

   // usuwa z kolejki najlepszy track
track * pop_best(priority_queue * queue){
   if(is_empty(queue)){
      return NULL;
   }
   track * result = get_track(1, queue->elem_list);
   int index = 1;
   while (index * 2 <= size(queue)){
      // bierzemy lewego
      if(index * 2 == size(queue)){
         queue->elem_list->arr[index] = queue->elem_list->arr[index * 2];
         index *= 2;
      }
      else {
         track *left = queue->elem_list->arr[index * 2];
         track *right = queue->elem_list->arr[2 * index + 1];
         // bierzemy mniejszego z 2 synow
         if (is_better_track(left, right)) {
            queue->elem_list->arr[index] = left;
            index *= 2;
         }
         else {
            queue->elem_list->arr[index] = right;
            index = 2 * index + 1;
         }
      }
   }
   queue->elem_list->arr[index] = queue->elem_list->arr[queue->elem_list->length-1];
   queue->elem_list->length--;
   return result;
 }



