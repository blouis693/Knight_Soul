#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "game.h"
#include "utility.h"

// Global Variable
static ALLEGRO_DISPLAY* GAME_DISPLAY;
static ALLEGRO_TIMER* game_timer;
static ALLEGRO_EVENT_QUEUE* eventQueue = NULL;
static ALLEGRO_EVENT event;

// Current Active Scene
Scene * currentScene;
// Game Tick
uint32_t GAME_TICK = 0;
const uint32_t GAME_TICK_CD = 64;
ALLEGRO_TIMER* game_tick_timer;

 /*
    Shared Variable
 */
// You may use the KeyState if you have a triggered event by holding the button
bool key_state[ALLEGRO_KEY_MAX];
// Mouse (X, Y) coordinate
Point Mouse;

// Initialize Game Property
void initGame(void){
    if (!al_init())
        game_abort("failed to initialize allegro");
    // Initialize add-ons.
    if (!al_init_primitives_addon())
        game_abort("failed to initialize primitives add-on");
    if (!al_init_font_addon())
        game_abort("failed to initialize font add-on");
    if (!al_init_ttf_addon())
        game_abort("failed to initialize ttf add-on");
    if (!al_init_image_addon())
        game_abort("failed to initialize image add-on");
    if (!al_install_audio())
        game_abort("failed to initialize audio add-on");
    if (!al_init_acodec_addon())
        game_abort("failed to initialize audio codec add-on");
    if (!al_reserve_samples(RESERVE_SAMPLES))
        game_abort("failed to reserve samples");
    if (!al_install_keyboard())
        game_abort("failed to install keyboard");
    if (!al_install_mouse())
        game_abort("failed to install mouse");
    
    // Create Game Display
    GAME_DISPLAY = al_create_display(SCREEN_W, SCREEN_H);
    if (!GAME_DISPLAY)
        game_abort("failed to create display");
    // Set Window Title
    al_set_window_title(GAME_DISPLAY, GAME_TITLE);
    // Set Game Timer for display
    game_timer = al_create_timer(1.0f / FPS);
    if (!game_timer)
        game_abort("failed to create timer");
    
    // using time for random seed to get unique random
    srand((unsigned int)time(NULL));
    // Initialize Utility in utility.c
    init_Util();
}

void uninit(void){
    al_destroy_event_queue(eventQueue);
    al_destroy_display(GAME_DISPLAY);
    al_destroy_timer(game_timer);
}

void loopGame(void){
    // Game event Loop
    float startTime = 0.0f, endTime = 0.0f, deltaTime = 0.0f;
    bool redraw = true;
    bool gameDone = false;
    
    while(!gameDone){
        al_wait_for_event(eventQueue, &event);
        endTime = al_get_time();
        
        switch(event.type){
            // You may add more Allegro Event if you feel all this are not enough
                
            case ALLEGRO_EVENT_TIMER:
                // Redraw Display
                // TODO TIMER
                redraw = true;
                break;
                
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                // Window closed
                game_log("Game Closed");
                gameDone = true;
                break;
            
            // Key Down
            case ALLEGRO_EVENT_KEY_DOWN:
                game_log("Key with keycode %d down", event.keyboard.keycode);
                key_state[event.keyboard.keycode] = true;
                break;
            // Key Up
            case ALLEGRO_EVENT_KEY_UP:
                game_log("Key with keycode %d up", event.keyboard.keycode);
                key_state[event.keyboard.keycode] = false;
                break;
            // Mouse Down
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                break;
            // Mouse Up
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                break;
        }
        
        // Redraw a frame
        if(redraw && al_event_queue_is_empty(eventQueue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            // Update
            // Draw
            al_flip_display();
        }
        
    }
}

void startGame(void){
    // Initialize
    initGame();
    
    // Start Game Event Loop
    loopGame();
    
    // Terminate all program and delete the resources
    uninit();
    
    return;
}
