#ifndef DROGI_PRIORITY_QUEUE_H
#define DROGI_PRIORITY_QUEUE_H

#include "track.h"
#include "vector_track.h"

struct priority_queue1{
    vector_track * elem_list;
};

typedef struct priority_queue1 priority_queue;

priority_queue * new_priority_queue();

void add_to_queue(priority_queue *, track *);

bool is_empty(priority_queue *);

track * pop_best(priority_queue *);



#endif //DROGI_PRIORITY_QUEUE_H