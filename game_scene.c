#include <string.h>

#include "game_scene.h"
#include "player.h"

Player player;

static void init(void){
    player = createPlayer("pacman.png");
}

static void draw(void){
    drawPlayer(&player);
}

static void update(void){
    updatePlayer(&player);
}

static void destroy(void){
    deletePlayer(&player);
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
