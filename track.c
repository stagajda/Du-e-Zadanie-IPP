#include <zconf.h>
#include "track.h"
#include <stdio.h>

int min(int a, int b){
   if(a < b){
      return a;
   }
   return b;
}
track * new_track(int destination_id){
   track * new_track1 = malloc(sizeof(track));
   new_track1->destination_id = destination_id;
   new_track1->previous_city_id = -1;
   new_track1->year_of_oldest_part = INT_MAX;
   new_track1->length = 0;
   new_track1->last_road = NULL;
   return new_track1;
}

track * copy_track(track * track1){
   track * new_track1 = new_track(track1->destination_id);
   new_track1->year_of_oldest_part = track1->year_of_oldest_part;
   new_track1->length = track1->length;
   new_track1->previous_city_id = track1->previous_city_id;
   new_track1->last_road = track1->last_road;
   return new_track1;
}

track * extend_track(track * track1, road * road1){
   track * extended_track = copy_track(track1);
   extended_track->last_road = road1;
   extended_track->length += road1->distance;
   extended_track->year_of_oldest_part = min(road1->built_year, extended_track->year_of_oldest_part);
   extended_track->previous_city_id = extended_track->destination_id;
   if(extended_track->destination_id == road1->city1_id){
      extended_track->destination_id = road1->city2_id;
   }
   else{
      extended_track->destination_id = road1->city1_id;
   }
   return extended_track;
}

// zwraca prawde, jezeli track1 jest lepszy, lub rowny track2
// jest lepszy, gdy jego dlugosc jest krotsza, a jezeli dlugosci sa rowne,
// to jezeli jego najstarszy odcinek jest mlodszy
bool is_better_track(track * track1, track * track2){
   if(track1->length < track2->length){
      return true;
   }
   if(track1->length == track2->length) {
      return track1->year_of_oldest_part >= track2->year_of_oldest_part;
   }

   return false;
}