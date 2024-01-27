#include <stdio.h>
#include <stdlib.h>

#include "map.h"

/*
    TILE SIZE DISPLAYED IN THE GAME
    You may change the tile size, but
    it's recommended to make the TILE SIZE is a multiplier from 16 from original image
 */
extern const int TILE_SIZE;
extern int spawn_x;
extern int spawn_y;
Map create_map(char * path, uint8_t type){
    Map map;
    memset(&map, 0, sizeof(Map));
    
    FILE * f = fopen(path, "r");
    if(!f){
        game_abort("Can't load map file : %s", path);
    }
    
    game_log("Using %s to load the map", path);
    
    fscanf(f, "%d %d", &map.row, &map.col);
    char ch;
    
    map.map = (uint8_t **) malloc(map.row * sizeof(uint8_t *));
    for(int i=0; i<map.row; i++){
        map.map[i] = (uint8_t *) malloc(map.col * sizeof(uint8_t));
    }
    
    // Scan the map to the array
    for(int i = 0; i < map.row; i++){
        for(int j = 0; j < map.col; j++){
            fscanf(f, " %c", &ch);
            
            switch(ch)
            {
                case '#': // Case Wall
                    map.map[i][j] = WALL;
                    break;
                    
                case '.': // Case Floor
                    map.map[i][j] = FLOOR;
                    break;
                    
                case '_': // Case Water
                    map.map[i][j] = WATER;
                    break;
                case 'P':
                    map.map[i][j] = FLOOR;
                    spawn_x = j;
                    spawn_y = i;
                    break;
                    
                default: // If not determined, set it as water
                    map.map[i][j] = WATER;
                    break;
            }
        }
    }
    
    switch(type){
        // In case you have more than 1 different asset of map, you can add here
        default:
            // Tiles
            map.asset_floor = al_load_bitmap("floor0.png");
            if(!map.asset_floor){
                game_abort("Failed to load floor0.png");
            }
            // Water
            map.asset_water = al_load_bitmap("water0.png");
            if(!map.asset_water){
                game_abort("Failed to load water0.png");
            }
            // Wall
            map.asset_wall = al_load_bitmap("wall0.png");
            if(!map.asset_water){
                game_abort("Failed to load wall0.png");
            }
            break;
    }
    
    return map;
}

void draw_map(Map * map, Point cam){
    // Draw map based on the camera point coordinate
    for(int i=0; i<map->row; i++){
        for(int j=0; j<map->col; j++){
            int dy = i * TILE_SIZE - cam.y; // destiny y axis
            int dx = j * TILE_SIZE - cam.x; // destiny x axis
            ALLEGRO_BITMAP * IMG; // the source bitmap
            
            switch(map->map[i][j]){
                case WALL:
                    IMG = map->asset_wall;
                    break;
                    
                case FLOOR:
                    IMG = map->asset_floor;
                    break;
                    
                case WATER:
                    IMG = map->asset_water;
                    break;
                    
                default:
                    IMG = map->asset_water;
                    break;
            }
            
            // Remember to 
            al_draw_scaled_bitmap(
                IMG, // image
                0, 0, 16, 16, // source x, source y, width, height
                dx, dy,TILE_SIZE,TILE_SIZE, // destiny x, destiny y, destiny width, destiny height
                0); // flag : set 0


        }
    }
}

void update_map(Map * map){
    
}

void destroy_map(Map * map){
    for(int i = 0; i < map->row; i++){
        free(map->map[i]);
    }
    free(map->map);
}
