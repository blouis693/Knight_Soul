#include <string.h>
#include "game_scene.h"
#include "player.h"
#include "map.h"
#include "SlimeEnemy.h"
#include <math.h>
#include <time.h>
Player player; // Player
Map map; // Map
extern int spawn_x;
extern int spawn_y;

extern int TILE_SIZE;
Enemylist* head = NULL;
Enemylist* tail = NULL;
int enemy_count = 0;
static void init(void){
    map = create_map("map0.txt", 0);
    
    
    player = create_player("pixilart-sprite-2.png",spawn_y,spawn_x);
    game_log("coord x:%d \n coords y:%d \n",spawn_x,spawn_y);
   

}

static void draw(void){
    // Set the Camera coordinate
    Point Camera;
    Camera.x = player.coord.x;// - (SCREEN_H/2);
    Camera.y = player.coord.y;// - (SCREEN_W/2);
    
    // Draw
    draw_map(&map, Camera);
    draw_player(&player);
    Enemylist* enemy = head;
    while(enemy != NULL){
        draw_enemy(enemy->enemy, Camera);
        enemy = enemy->next;
    }
}

static void update(void){
    Point dest = (Point){player.pos.x / TILE_SIZE,player.pos.y/TILE_SIZE};
    update_player(&player,&map);
    if(enemy_count < 4){
        
        int sx;
        int sy;

        while(1){
            sx = Randoms(0, 19);
            sy = Randoms(0, 19);
            if(map.map[sy][sx]==FLOOR)break;
        }
        SlimeEnemy* enemy = create_enemy("Slime.png",sy,sx);

        if(head == NULL){
            head = insert(enemy);
            tail = head;
        }
        else{
            tail->next = insert(enemy);
            tail = tail->next;
        }
        enemy_count++;
    }
    Enemylist* enemy = head;
    while(enemy != NULL){
        enemy->enemy->coord = (Point){enemy->enemy->pos.x/TILE_SIZE,enemy->enemy->pos.y/TILE_SIZE};

        update_enemy(enemy->enemy, &map, enemy->enemy->coord,dest);

        enemy = enemy->next;
    }

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
