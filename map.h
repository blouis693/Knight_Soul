#ifndef map_h
#define map_h

#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "utility.h"



// Map Struct

typedef struct Map_{
    uint8_t ** map;
    int row, col;
    ALLEGRO_BITMAP* asset_wall;
    ALLEGRO_BITMAP* asset_floor;
    ALLEGRO_BITMAP* asset_water;
} Map;

/*
    MAP FUNCTION
    Feel free to add more if you have some idea or interaction with the map
 */
Map create_map(char * path, uint8_t type); // Create a map based on given file path
void draw_map(Map * map, Point cam); // Draw the map
void update_map(Map * map); // Update map : you might want add some parameter here
void destroy_map(Map * map); // Destroy map

#endif /* map_h */
