#ifndef player_h
#define player_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "utility.h"
#include "map.h"
typedef struct Player_{
    Point coord; // coordinate of the player
    Point pos;
    int speed;
    ALLEGRO_BITMAP* image;
    int direction;
} Player;

Player create_player(char * path,int row,int col);
void update_player(Player * player,Map* map);
void draw_player(Player * player);
void delete_player(Player * player);
bool wall_collision(Player* player,Map* map);

#endif /* player_h */
