cmake_minimum_required(VERSION 3.14)
project(Drogi C)

set(CMAKE_C_STANDARD 11)

add_executable(Drogi main.c vector_int.h vector_int.c road.c road.h map.h city.h city.c vector_road.c vector_road.h vector_city.c vector_city.h map.c track.c track.h priority_queue.c priority_queue.h vector_track.c vector_track.h route.c route.h)