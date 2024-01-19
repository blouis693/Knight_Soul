#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "utility.h"

/*
    CONSTANT VARIABLE
    You may change the constant value variable here
*/
// Frame per Second
const uint32_t FPS = 60;
// Screen Width
const uint32_t SCREEN_W = 800;
// Screen Height
const uint32_t SCREEN_H = 800;
// Reserve Sample Audio
const uint32_t RESERVE_SAMPLES = 4;
// Game Title
const char* gameTitle = "Mini-RPG";
// Log File path
const char* log_file = "log.txt";


// Utility Initialization
void initUtil(void){
    // Clear the log file and replace it with the new one
    FILE * f = fopen(log_file, "w");
    if(f != NULL)
        fprintf(f, "Mini RPG game log file\n");
    fclose(f);
}


/*
    GAME LOG
*/

void print_log(const char * msg, va_list arg, logtype type){
#ifdef LOG_ENABLE
    // Open File
    FILE * f = fopen(log_file, "a");
    
    switch(type){
        case Log:
            printf("[LOG] ");
            if(f != NULL) // to prevent if we can't open the log file
                fprintf(f, "[LOG] ");
            break;
        case Error:
            printf("[Error] ");
            if(f != NULL)
                fprintf(f, "[Error] ");
            break;
        case Warning:
            printf("[Warning] ");
            if(f != NULL)
                fprintf(f, "[Warning] ");
        default:
            printf("[???] ");
            if(f != NULL)
                fprintf(f, "[???] ");
            break;
    }
    
    vprintf(msg, arg);
    printf("\n");
    if(f != NULL){
        vfprintf(f, msg, arg);
        fprintf(f, "\n");
    }
#endif
}

// Game Log
void game_log(const char * msg, ...){
#ifdef LOG_ENABLE
    va_list args;
    va_start(args, msg);
    print_log(msg, args, Log);
    va_end(args);
#endif
}

// Game Error Messgae
void game_abort(const char * msg, ...){
#ifdef LOG_ENABLE
    va_list args;
    va_start(args, msg);
    print_log(msg, args, Error);
    va_end(args);
#endif
    // Abort the game if there is an error
    exit(1);
}

void game_warning(const char * msg, ...){
#ifdef LOG_ENABLE
    va_list args;
    va_start(args, msg);
    print_log(msg, args, Warning);
    va_end(args);
#endif
}


