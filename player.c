#include "player.h"
#include "game.h"
#include <math.h>
#include "map.h"
extern const int TILE_SIZE;

Player create_player(char * path,int row,int col){
    Player player;
    memset(&player, 0, sizeof(player));
    
    player.coord = (Point){
                           (-SCREEN_H/2+col*TILE_SIZE)+TILE_SIZE/4,
                           (-SCREEN_W/2+row*TILE_SIZE)+TILE_SIZE/4
                          };
    player.pos = (Point){col*TILE_SIZE+TILE_SIZE/2,row*TILE_SIZE+TILE_SIZE/2};
    
    player.speed = 5;
    player.image = al_load_bitmap(path);
    if(!player.image){
        game_abort("Error Load Bitmap with path : %s", path);
    }
    
    return player;
}

void update_player(Player * player,Map* map){
    int save_x = player->coord.x;
    int save_y = player->coord.y;
    int pos_x = player->pos.x;
    int pos_y = player->pos.y;
    
    if (keyState[ALLEGRO_KEY_W]) {
        player->coord.y -= player->speed;
        player->pos.y -= player->speed;
        player->direction = UP;
    }
    if (keyState[ALLEGRO_KEY_S]) {
        player->coord.y += player->speed;
        player->pos.y += player->speed;
        player->direction = DOWN;

    }
    if (keyState[ALLEGRO_KEY_A]) {
        player->coord.x -= player->speed;
        player->pos.x -= player->speed;
        player->direction = LEFT;

    }
    if (keyState[ALLEGRO_KEY_D]) {
        player->coord.x += player->speed;
        player->pos.x += player->speed;
        player->direction = RIGHT;
    }
    if(wall_collision(player,map)){
        player->coord.x = save_x;
        player->coord.y = save_y;
        player->pos.x = pos_x;
        player->pos.y = pos_y;
        game_log("collided\n");
    }
//    game_log("direction: %d\n",player->direction);
//    game_log("coord x:%d \n coords y:%d \n",player->pos.x/TILE_SIZE,player->pos.y/TILE_SIZE);
}

void draw_player(Player * player){
    al_draw_scaled_bitmap(
        player->image,
        0, 0, 16, 16,
        SCREEN_H/2, SCREEN_W/2, 32, 32,
        0);
}

void delete_player(Player * player){
    al_destroy_bitmap(player->image);
}

bool wall_collision(Player* player,Map* map){
    // top left corner
    int tl_x = (player->pos.x - TILE_SIZE / 4) / TILE_SIZE;
    int tl_y = (player->pos.y - TILE_SIZE / 4) / TILE_SIZE;
    // top right corner
    int tr_x = (player->pos.x + TILE_SIZE / 4) / TILE_SIZE;
    int tr_y = (player->pos.y - TILE_SIZE / 4) / TILE_SIZE;
    //bottom left corner
    int bl_x = (player->pos.x - TILE_SIZE / 4) / TILE_SIZE;
    int bl_y = (player->pos.y + TILE_SIZE / 4) / TILE_SIZE;
    //bottom right corner
    int br_x = (player->pos.x + TILE_SIZE / 4) / TILE_SIZE;
    int br_y = (player->pos.y + TILE_SIZE / 4) / TILE_SIZE;


    if(player->pos.y < TILE_SIZE/4
       || player->pos.x < TILE_SIZE/4
       || player->pos.y > TILE_SIZE*map->row-TILE_SIZE/4
       || player->pos.x > TILE_SIZE*map->row-TILE_SIZE/4
       || map->map[tl_y][tl_x]==WALL
       || map->map[tr_y][tr_x]==WALL
       || map->map[bl_y][bl_x]==WALL
       || map->map[br_y][br_x]==WALL)return true;

    return false;
    
}
