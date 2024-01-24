#include <stdio.h>
#include <stdlib.h>

#include "map.h"

Map create_map(char * path, uint8_t type){
    Map map;
    FILE * f = fopen(path, "r");
    if(!f){
        game_abort("Can't load map file : %s", path);
    }
    
    fscanf(f, "%u %u", &map.row, &map.col);
    char ch;
    
    map.map = (uint8_t **) malloc(map.row * sizeof(uint8_t *));
    for(int i=0; i<map.row; i++){
        map.map[i] = (uint8_t *) malloc(map.col * sizeof(uint8_t));
    }
    
    for(int i = 0; i < map.row; i++){
        for(int j = 0; j < map.col; j++){
            fscanf(f, " %c", &ch);
            
            switch(ch)
            {
                case '#':
                    map.map[i][j] = WALL;
                    break;
                    
                case '.':
                    map.map[i][j] = FLOOR;
                    break;
                    
                case '_':
                    map.map[i][j] = WATER;
                    break;
                    
                default:
                    map.map[i][j] = WATER;
                    break;
            }
        }
    }
    
    // Different type of map may load different asset
    // Feel free to add more type of your map
    switch(type){
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
            //
            
            break;
    }
    
    return map;
}

void draw_map(Map * map){
    
}

void update_map(Map * map){
    
}

void destroy_map(Map * map){
    for(int i = 0; i < map->row; i++){
        free(map->map[i]);
    }
    free(map->map);
}
