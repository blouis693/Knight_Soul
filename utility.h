#ifndef utility_h
#define utility_h

// LOG_ENABLE : To print the game log message
// You may comment the define below to boost your game performance
// It's recommended to use this this out before finishing for debugging purpose
#define LOG_ENABLE

/*
    EXTERN VARIABLE
    To share a same variable to different files
    Remember you can't directly declare variable in header file
 */
extern const uint32_t FPS;
extern const uint32_t SCREEN_W;
extern const uint32_t SCREEN_H;
extern const uint32_t RESERVE_SAMPLES;
extern const char* gameTitle;

/*
    ENUMERATION DEFINITION
    You may add new enum definition here
 */
typedef enum logtype{
    Log,
    Error,
    Warning
} logtype;



/*
    UTILITY FUNCTION DECLARATION
 */
// Utility Initialization
void initUtil(void);
// Game Log
void game_log(const char * msg, ...);
// Game Error Msg
void game_abort(const char * msg, ...);


#endif /* utility_h */
