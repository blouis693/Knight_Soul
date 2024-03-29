#ifndef utility_h
#define utility_h

/*
     LOG_ENABLE
     To print the game log message
     You may comment the define below to boost your game performance
     It's recommended to use this this out before finishing for debugging purpose
*/
#define LOG_ENABLE

/*
    EXTERN VARIABLE
    To share a same variable to different files
    Remember you can't directly declare variable in header file
    You may change the value variable in utility.c
 */
extern const uint32_t FPS;
extern const uint32_t SCREEN_W;
extern const uint32_t SCREEN_H;
extern const uint32_t RESERVE_SAMPLES;
extern const char* GAME_TITLE;

/*
    FUNCTION POINTER
    You can add if you have an unique function pointer
*/
typedef void(*function_void)(void);
typedef void(*function_key)(int keycode);
typedef void(*function_mouse)(int btn, int x, int y, int dz);

/*
    ENUMERATION & STRUCT DEFINITION
    You may add new enum or struct definition here
 */
typedef enum logtype_{
    Log,
    Error,
    Warning
} logtype;

typedef struct Point_{
    uint32_t x;
    uint32_t y;
} Point;

typedef struct Scene_{
    // You may add your own function or struct variable here
    char* name;
    function_void init; // initialize
    function_void update; // update scene
    function_void draw; // draw scene
    function_void destroy; // destroy scene
} Scene;

/*
    UTILITY FUNCTION DECLARATION
 */
// Utility Initialization
void init_Util(void);
// Game Log
void game_log(const char * msg, ...);
// Game Error Msg
void game_abort(const char * msg, ...);


#endif /* utility_h */
