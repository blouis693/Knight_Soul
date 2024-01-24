#ifndef player_h
#define player_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "utility.h"

typedef struct Player_{
    Point coord; // coordinate of the player
    int speed;
    ALLEGRO_BITMAP* image;
} Player;

Player create_player(char * path);
void update_player(Player * player);
void draw_player(Player * player);
void delete_player(Player * player);

#endif /* player_h */
