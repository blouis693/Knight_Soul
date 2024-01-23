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

Player createPlayer(char * path);
void updatePlayer(Player * player);
void drawPlayer(Player * player);
void deletePlayer(Player * player);

#endif /* player_h */
