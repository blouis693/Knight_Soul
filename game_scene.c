#include <string.h>

#include "game_scene.h"
#include "player.h"

Player player;

static void init(void){
    player = create_player("pacman.png");
}

static void draw(void){
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
