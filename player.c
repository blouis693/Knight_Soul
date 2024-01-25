#include "player.h"
#include "game.h"

Player create_player(char * path){
    Player player;
    memset(&player, 0, sizeof(player));
    
    player.coord = (Point){SCREEN_H/2, SCREEN_W/2};
    player.speed = 5;
    player.image = al_load_bitmap(path);
    if(!player.image){
        game_abort("Error Load Bitmap with path : %s", path);
    }
    
    return player;
}

void update_player(Player * player){
    
    if (keyState[ALLEGRO_KEY_W]) {
        player->coord.y -= player->speed;
    }
    if (keyState[ALLEGRO_KEY_S]) {
        player->coord.y += player->speed;
    }
    if (keyState[ALLEGRO_KEY_A]) {
        player->coord.x -= player->speed;
    }
    if (keyState[ALLEGRO_KEY_D]) {
        player->coord.x += player->speed;
    }
}

void draw_player(Player * player){
    al_draw_scaled_bitmap(
        player->image,
        0, 0, 16, 16,
        player->coord.x, player->coord.y, 32, 32,
        0);
}

void delete_player(Player * player){
    al_destroy_bitmap(player->image);
}
