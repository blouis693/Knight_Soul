//
//  Enemy.h
//  Knight_Soul
//
//  Created by Brandon Louis Chiender on 2024/1/28.
//

#ifndef Enemy_h
#define Enemy_h

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "utility.h"
#include "map.h"
typedef struct Enemy_{
    Point coord; // coordinate of the player in index
    Point pos; 
    int speed;
    ALLEGRO_BITMAP* image;
    int direction;
    int moving;
    int dist;
} Enemy;
typedef struct enemy_list_{
    struct enemy_list* next;
    Enemy enemy;
}enemy_list;
Enemy create_enemy(char * path,int row,int col);
void update_enemy(Enemy * enemy,Map* map,Point src,Point dest);
void draw_enemy(Enemy * enemy, Point cam);
void delete_enemy(Enemy * enemy);
enemy_list* insert_enemy(int sx,int sy);
int shortest_path(Point src,Point dest,Map* map);
void move_enemy(Enemy * enemy,int move);
#endif /* Enemy_h */

