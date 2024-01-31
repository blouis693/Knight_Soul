#include <string.h>
#include "game_scene.h"
#include "player.h"
#include "map.h"
#include "Enemy.h"
#include <math.h>
#include <time.h>
Player player; // Player
Map map; // Map
Enemy enemy;
int enemy_count = 0;
extern int spawn_x;
extern int spawn_y;
enemy_list* enemy_group = NULL;
enemy_list* tail_group = NULL;
extern int TILE_SIZE;

static void init(void){
    map = create_map("map0.txt", 0);
    
    
    player = create_player("pacman.png",spawn_y,spawn_x);
    game_log("coord x:%d \n coords y:%d \n",spawn_x,spawn_y);
    enemy = create_enemy("pacman.png",1,1);
}

static void draw(void){
    // Set the Camera coordinate
    Point Camera;
    Camera.x = player.coord.x;// - (SCREEN_H/2);
    Camera.y = player.coord.y;// - (SCREEN_W/2);
    
    // Draw
    draw_map(&map, Camera);
    draw_player(&player);
    
    draw_enemy(&enemy,Camera);
}

static void update(void){
    Point dest = (Point){player.pos.x / TILE_SIZE,player.pos.y/TILE_SIZE};
    enemy.coord = (Point){enemy.pos.x/TILE_SIZE,enemy.pos.y/TILE_SIZE};
    update_player(&player,&map);
    update_enemy(&enemy, &map, enemy.coord,dest);
//    if(enemy_count == 0){
//        srand(time(0));
//        int sx = Randoms(0, 19);
//        int sy = Randoms(0,19);
//        if(!enemy_group){
//            enemy_group = insert_enemy(sx,sy);
//            tail_group = enemy_group;
//        }
//        else{
//            tail_group->next = insert_enemy(sx,sy);
//            tail_group = tail_group->next;
//        }
//    }
}

static void destroy(void){
    delete_player(&player);
}


Scene create_game_scene(void){
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    
    scene.init = &init;
    scene.draw = &draw;
    scene.update = &update;
    scene.destroy = &destroy;
    
    return scene;
}
int Randoms(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}
