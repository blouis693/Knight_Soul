#include <string.h>

#include "game_scene.h"
#include "player.h"
#include "map.h"

Player player; // Player
Map map; // Map

static void init(void){
    player = create_player("pacman.png");
    map = create_map("map0.txt", 0);
}

static void draw(void){
    // Set the Camera coordinate
    Point Camera;
    Camera.x = player.coord.x;// - (SCREEN_H/2);
    Camera.y = player.coord.y;// - (SCREEN_W/2);
    
    // Draw
    draw_map(&map, Camera);
    draw_player(&player);
}

static void update(void){
    update_player(&player);
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
