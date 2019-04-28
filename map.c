#include <stdlib.h>
#include "map.h"
#include "vector_road.h"
#include "vector_city.h"
#include "road.h"
#include "track.h"
#include "priority_queue.h"
#include <string.h>
#include <zconf.h>
#include <stdio.h>

Map* newMap(){
   Map* new_map = malloc(sizeof(Map));
   new_map->cities_list = new_vector_city();
   new_map->roads_list = new_vector_road();
   return new_map;
}

// zwraca miasto o podanej nazwie, lub NULL, jesli nie istnieje
city * find_city(Map * mapa, const char *city){
   for(int i = 0;i < mapa->cities_list->length;i++){
      if(strcmp(get_city(i, mapa->cities_list)->name, city) == 0){
         return get_city(i, mapa->cities_list);
      }
   }
   return NULL;
}
// jezeli jest droga pomiedzy city1 i city2, to ja zwraca,
// w przeciwnym razie NULL, w szczegolnosci, gdy jedno z miast nie istnieje
// to zwraca NULL
road * road_between(city * city1, city * city2){

   if(city1 == NULL || city2 == NULL){
      return NULL;
   }
   for(int i = 0;i < city1->roads->length;i++){
      road * road1 = get_road(i, city1->roads);
      if(road1->city1_id == city1->id || road1->city2_id == city2->id){
         return road1;
      }
   }
   return NULL;
}

/** @brief Dodaje do mapy odcinek drogi między dwoma różnymi miastami.
 * Jeśli któreś z podanych miast nie istnieje, to dodaje je do mapy, a następnie
 * dodaje do mapy odcinek drogi między tymi miastami.
 * @param[in,out] map    – wskaźnik na strukturę przechowującą mapę dróg;
 * @param[in] city1      – wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] city2      – wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] length     – długość w km odcinka drogi;
 * @param[in] builtYear  – rok budowy odcinka drogi.
 * @return Wartość @p true, jeśli odcinek drogi został dodany.
 * Wartość @p false, jeśli wystąpił błąd: któryś z parametrów ma niepoprawną
 * wartość, obie podane nazwy miast są identyczne, odcinek drogi między tymi
 * miastami już istnieje lub nie udało się zaalokować pamięci.
 */

bool addRoad(Map *map, const char *city_name1, const char *city_name2,
             unsigned length, int builtYear) {

   if(strcmp(city_name1, city_name2) == 0) {
      return false;
   }

   city * city1 = find_city(map, city_name1);
   city * city2 = find_city(map, city_name2);
   if(road_between(city1, city2) != NULL){
      return false;
   }
   if(city1 == NULL){
      city1 = add_city_to_map(map, city_name1);
   }
   if(city2 == NULL){
      city2 = add_city_to_map(map, city_name2);
   }

   road * new_road1 = new_road(city1->id, city2->id, length, builtYear);
   add_road_to_vec(city1->roads, new_road1);
   add_road_to_vec(city2->roads, new_road1);
   add_road_to_vec(map->roads_list, new_road1);
}

// przyjmuje nazwe miasta, funkcja zaklada, ze danego miasta nie bylo wczesniej na mapie
// dodaje je do mapy i zwraca jego id
city * add_city_to_map(Map* map,const char *city_name){
   vector_city * list_of_cities = map->cities_list;
   city * created_city = new_city(city_name, list_of_cities->length);
   add_city_to_vec(list_of_cities, created_city);
   return created_city;
}

/** @brief Modyfikuje rok ostatniego remontu odcinka drogi.
 * Dla odcinka drogi między dwoma miastami zmienia rok jego ostatniego remontu
 * lub ustawia ten rok, jeśli odcinek nie był jeszcze remontowany.
 * @param[in,out] map    – wskaźnik na strukturę przechowującą mapę dróg;
 * @param[in] city1      – wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] city2      – wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] repairYear – rok ostatniego remontu odcinka drogi.
 * @return Wartość @p true, jeśli modyfikacja się powiodła.
 * Wartość @p false, jeśli wystąpił błąd: któryś z parametrów ma niepoprawną
 * wartość, któreś z podanych miast nie istnieje, nie ma odcinka drogi między
 * podanymi miastami, podany rok jest wcześniejszy niż zapisany dla tego odcinka
 * drogi rok budowy lub ostatniego remontu.
 */
bool repairRoad(Map *map, const char *city_name1, const char *city_name2, int repairYear){
   city * city1 = find_city(map, city_name1);
   city * city2 = find_city(map, city_name2);
   road * road1 = road_between(city1, city2);
   if(road1 == NULL){
      return false;
   }
   if(repairYear == 0 || repairYear < road1->built_year){
      return false;
   }
   road1->built_year = repairYear;

   return true;
}

// znajduje najkrotsza trase do miast na mapie, wszystkie te trasy nie przechodza
// przez miasta nalezace do wektora ignored_cities
track ** dijkstra(Map * map, vector_city * ignored_cities,  city * start_city){
   track ** track_to;
   int cities_num = map->cities_list->length;
   track_to = malloc(cities_num * sizeof(track *));
   // na poczatku do wszystkich ustawiamy maksymalna odleglosc
   for(int i = 0;i < cities_num;i++){
      track_to[i] = new_track(i);
      track_to[i]->length = INT_MAX;
   }
   // teraz tym ignorowanym ustawiam taka mala odleglosc, ze nigdy nie poprawie w nich wyniku dijkstra
   // wiec nigdy nie bede bral pod uwage krawedzi z nich wychodzacych
   for(int i = 0;i < ignored_cities->length;i++){
      track_to[ignored_cities->arr[i]->id]->length = 0;
   }

   track_to[start_city->id]->length = 0;
   track_to[start_city->id]->year_of_oldest_part = INT_MAX;

   // wrzucam moj startowy wierzcholek na kolejke
   priority_queue * queue = new_priority_queue();
   add_to_queue(queue, track_to[start_city->id]);

   // dopoki cos jest na kolejce
   // bierzemy trase ze szczytu kolejki, jezeli odleglosc i rok sa aktualne, to rozpatrujemy wszystkie krawedzie
   // z koncowego miasta i jezeli jakas krawedz poprawia wynik dla ktoregos miasta, to rozszerzamy trase o nia
   // poprawiamy wynik w tablicy i wrzucamy na kolejke
   while(!is_empty(queue)){
      track * track1 = pop_best(queue);
      int dest = track1->destination_id;
      city * dest_city = get_city(dest, map->cities_list);
      if(track1->length == track_to[dest]->length &&
         track1->year_of_oldest_part == track_to[dest]->year_of_oldest_part){
         for(int i = 0;i < dest_city->roads->length;i++){
            road * road1 = get_road(i, dest_city->roads);
            track * extended_track = extend_track(track1, road1);
            if(!is_better_track(track_to[extended_track->destination_id], extended_track)){

               track_to[extended_track->destination_id] = extended_track;
               add_to_queue(queue, extended_track); // TU COS NIE DZIALA XD
            }
            else{
               // zwalniamy pamiec z tego rozszerzonego tracku
            }
         }
      }
   }
   return track_to;
}

// funkcja zwraca wektor z odcinkami ukladajacymi sie w najbardziej optymalna
// droge z city1 do city2 jezeli taka droga nie istnieje, to zwraca NULL
vector_road * best_parts(city * city1, city * city2, track ** tracks){
   if(tracks[city2->id] == NULL){
      return NULL;
   }
   vector_road * result = new_vector_road();
   road * part;
   int end_id = city2;
   int previous_city_id;
   part = tracks[city2->id]->last_road;

   while(true){
      if(part->city1_id == end_id){
         previous_city_id = part->city2_id;
      }
      else{
         previous_city_id = part->city1_id;
      }
      add_road_to_vec(result, part);
      if(previous_city_id == city1->id){
         break;
      }
      else{
         end_id = previous_city_id;
      }
   }
   reverse(result);
   return result;
}

/** @brief Łączy dwa różne miasta drogą krajową.
 * Tworzy drogę krajową pomiędzy dwoma miastami i nadaje jej podany numer.
 * Wśród istniejących odcinków dróg wyszukuje najkrótszą drogę. Jeśli jest
 * więcej niż jeden sposób takiego wyboru, to dla każdego wariantu wyznacza
 * wśród wybranych w nim odcinków dróg ten, który był najdawniej wybudowany lub
 * remontowany i wybiera wariant z odcinkiem, który jest najmłodszy.
 * @param[in,out] map    – wskaźnik na strukturę przechowującą mapę dróg;
 * @param[in] routeId    – numer drogi krajowej;
 * @param[in] city1      – wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] city2      – wskaźnik na napis reprezentujący nazwę miasta.
 * @return Wartość @p true, jeśli droga krajowa została utworzona.
 * Wartość @p false, jeśli wystąpił błąd: któryś z parametrów ma niepoprawną
 * wartość, istnieje już droga krajowa o podanym numerze, któreś z podanych
 * miast nie istnieje, obie podane nazwy miast są identyczne, nie można
 * jednoznacznie wyznaczyć drogi krajowej między podanymi miastami lub nie udało
 * się zaalokować pamięci.
 */
bool newRoute(Map *map, unsigned routeId,
              const char *city1_name, const char *city2_name){
   if(routeId > 999 || strcmp(city1_name, city2_name) == 0){
      return false;
   }
   if(map->routes_list[routeId] != NULL){
      return false;
   }

   city * city1 = find_city(map, city1_name);
   city * city2 = find_city(map, city2_name);
   if(city1 == NULL || city2 == NULL){
      return false;
   }
   route * new_route1 = new_route(routeId, city1, city2);
   vector_city * no_ignored = new_vector_city();
   // znajdujemy kolejne odcinki
   track ** tracks = dijkstra(map, no_ignored, city1);
   new_route1->parts = best_parts(city1, city2, tracks);
   if(new_route1->parts == NULL){
      return NULL;
   }
   // wszystkim tym odcinkom, ktore naleza do tej drogi krajowej wpisujemy ta informacje

}