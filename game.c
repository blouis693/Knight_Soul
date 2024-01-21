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
static ALLEGRO_EVENT event;
static ALLEGRO_BITMAP* aurick = NULL;
bool key[ALLEGRO_KEY_MAX] = { false };  // Array to track the state of each key

int done = 0;
//game loop

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
    if(!al_init_image_addon())
        game_abort("couldn't initialize image addon\n");
    
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
    gameTick = al_create_timer(1.0f / FPS);

    if (!gameTimer)
        game_abort("failed to create timer");
    // Create character
    aurick = al_load_bitmap("pacman.png");
    if(!aurick)
    {
        game_abort("cant load aurick");
    }
    al_register_event_source(event_queue,
        al_get_display_event_source(gameDisplay));
    al_register_event_source(event_queue,
        al_get_timer_event_source(gameTimer));
    al_register_event_source(event_queue,
        al_get_timer_event_source(gameTick));
    al_register_event_source(event_queue,
        al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(gameTimer);
}
void start_loop(void){
    done = 0;
    int redraw = 1;
    float x = 0;
    float y = 0;
    float speed = 1;
    while(!done){
        al_wait_for_event(event_queue, &event);

        switch(event.type)
               {
                   case ALLEGRO_EVENT_TIMER:
                       // game logic goes here.
                       redraw = 1;
                       break;

                   case ALLEGRO_EVENT_KEY_DOWN:
                       key[event.keyboard.keycode] = true;

                       break;
                   case ALLEGRO_EVENT_KEY_UP:
                       key[event.keyboard.keycode] = false;

                       break;
                   case ALLEGRO_EVENT_DISPLAY_CLOSE:
                       done = 1;
                       break;
               }

               if(done)
                   break;
              const float moveSpeed = 5.0;

               if (key[ALLEGRO_KEY_W]) {
                   y -= moveSpeed;
               }
               if (key[ALLEGRO_KEY_S]) {
                   y += moveSpeed;
               }
               if (key[ALLEGRO_KEY_A]) {
                   x -= moveSpeed;
               }
               if (key[ALLEGRO_KEY_D]) {
                   x += moveSpeed;
               }

               if(redraw && al_is_event_queue_empty(event_queue))
               {
                   game_log("draw\n");
                   al_clear_to_color(al_map_rgb(0, 0, 0));
                   al_draw_bitmap(aurick,x,y, 0);
//                   al_draw_bitmap(aurick,100,100, 0);
//
                   al_flip_display();
                   redraw = 0;
               }
               
    
    }
    al_destroy_display(gameDisplay);
    al_destroy_timer(gameTimer);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(aurick);

}
void startGame(void){
    initGame();
    game_log("game initialized");
    start_loop();
    return;
}


