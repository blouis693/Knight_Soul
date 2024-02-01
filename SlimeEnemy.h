//
//  SlimeEnemy.h
//  Knight_Soul
//
//  Created by Brandon Louis Chiender on 2024/2/1.
//

#ifndef SlimeEnemy_h
#define SlimeEnemy_h

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "utility.h"
#include "map.h"
typedef enum status_{
    Moving,
    Idle,
    Jump,
} status;
typedef struct SlimeEnemy_{
    Point coord; // coordinate of the player in index
    Point pos;
    int speed;
    ALLEGRO_BITMAP* image;
    int direction;
    int Status;
    int dist;
    int save_dist;
} SlimeEnemy;
SlimeEnemy create_enemy(char * path,int row,int col);
void update_enemy(SlimeEnemy * enemy,Map* map,Point src,Point dest);
void draw_enemy(SlimeEnemy * enemy, Point cam);
void delete_enemy(SlimeEnemy * enemy);
int shortest_path(Point src,Point dest,Map* map);
void move_enemy(SlimeEnemy * enemy,int move,int speed);
#endif /* SlimeEnemy_h */
