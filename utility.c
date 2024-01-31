#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "utility.h"

/*
    CONSTANT VARIABLE
    You may change the constant value variable here
    Description of the variable at header file
*/
const int FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 800;
const int RESERVE_SAMPLES = 4;
const char* GAME_TITLE = "Brandon-RPG Adventure";
const char* log_file = "log.txt";
const int TILE_SIZE = 64;
int spawn_x = 0;
int spawn_y = 0;
//Queue implementation



// Function to initialize the queue
void initializeQueue( Queue* queue,int size) {
    queue->front = -1;
    queue->rear = -1;
    queue->MAX_SIZE = size;
}

// Function to check if the queue is empty
int isEmpty( Queue* queue) {
    return (queue->front == -1 && queue->rear == -1);
}

// Function to check if the queue is full
int isFull( Queue* queue) {
    return (queue->rear == queue->MAX_SIZE - 1);
}

// Function to add an element to the queue (enqueue)
void enqueue( Queue* queue, Point value) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->rear++;
    queue->items[queue->rear] = value;

}

// Function to remove an element from the front of the queue (dequeue)
void dequeue( Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }


    if (queue->front == queue->rear) {
        // Last element is dequeued, reset front and rear
        initializeQueue(queue,queue->MAX_SIZE);
    } else {
        // Move front to the next element
        queue->front++;
    }
}

// Function to display the elements of the queue



// Utility Initialization
void init_Util(void){
    // Clear the log file and replace it with the new one
    FILE * f = fopen(log_file, "w");
    if(f != NULL)
        fprintf(f, "Mini RPG game log file\n");
    fclose(f);
}

/*
    GAME LOG
    You can disable the log by remove the "#define LOG_ENABLE" in utility.h
    It's not recommended if you are still in progress on making this game
    You may do it after finishing it for performance boost purpose
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
