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

static ALLEGRO_DISPLAY* gameDisplay;
static ALLEGRO_TIMER* gameTimer;
static ALLEGRO_TIMER* gameTick;
static ALLEGRO_EVENT_QUEUE* event_queue;

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
    gameDisplay = al_create_display(SCREEN_W, SCREEN_H);
    if (!gameDisplay)
        game_abort("failed to create display");
    // Set Window Title
    al_set_window_title(gameDisplay, gameTitle);
    
    //Set event queue
    event_queue = al_create_event_queue();
    if(!event_queue)
        game_abort("failed to create event queue");
    // Set Game Timer for display
    gameTimer = al_create_timer(1.0f / FPS);
    if (!gameTimer)
        game_abort("failed to create timer");
  
    al_register_event_source(event_queue,
        al_get_display_event_source(gameDisplay));
    al_register_event_source(event_queue,
        al_get_timer_event_source(gameTimer));
    al_register_event_source(event_queue,
        al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(gameTimer);
}

void startGame(void){
    initGame();
    
    return;
}
