//
//  Enemy.c
//  Knight_Soul
//
//  Created by Brandon Louis Chiender on 2024/1/28.
//
#include "game.h"
#include <math.h>
#include "map.h"
#include "Enemy.h"

extern int TILE_SIZE;
int INF = 999999999;
Enemy create_enemy(char * path,int row,int col){
    Enemy enemy;
    memset(&enemy, 0, sizeof(enemy));
    enemy.pos = (Point){col*TILE_SIZE+TILE_SIZE/2,row*TILE_SIZE+TILE_SIZE/2};
//    enemy.pos = (Point){0,0};
    game_log("coord x:%d \n coords y:%d \n",enemy.pos.x/TILE_SIZE,enemy.pos.y/TILE_SIZE);
    enemy.speed = 5;
    enemy.image = al_load_bitmap(path);
    enemy.moving = 0;
    if(!enemy.image){
        game_abort("Error Load Bitmap with path : %s", path);
    }
    
    return enemy;
}

void update_enemy(Enemy * enemy,Map* map,Point src,Point dest){
    int speed = 0;
    int dist = 0;
    if(!enemy->moving){
        enemy->direction = shortest_path(dest,src,map);
        enemy->moving = 1;
        enemy->dist = TILE_SIZE/enemy->speed;
        dist = enemy->dist;
    }
    else{
        if(enemy->dist == -1){
            enemy->moving = 0;
            speed = TILE_SIZE-dist*enemy->speed;
            enemy->direction = -1;
        }
        else speed = enemy->speed;
        //    int move = -1;
        switch (enemy->direction) {
            case UP:
                enemy->pos.y -= speed;
                break;
            case DOWN:
                enemy->pos.y += speed;
                break;
            case LEFT:
                enemy->pos.x -= speed;
                break;
            case RIGHT:
                enemy->pos.x += speed;
                break;
            default:
                break;
        }
        enemy->dist--;
    }

//    game_log("direction: %d\n",player->direction);
//    game_log("coord x:%d \n coords y:%d \n",player->pos.x/TILE_SIZE,player->pos.y/TILE_SIZE);
}

void draw_enemy(Enemy * enemy,Point cam){
    int dy = enemy->pos.y - cam.y - TILE_SIZE/4; // destiny y axis
    int dx = enemy->pos.x - cam.x - TILE_SIZE/4; // destiny x axis
    al_draw_scaled_bitmap(
        enemy->image,
        0, 0, 16, 16,
        dx, dy, 32, 32,
        0);
}

void delete_enemy(Enemy * enemy){
    al_destroy_bitmap(enemy->image);
}

enemy_list* insert_enemy(int sx,int sy){
    enemy_list* new_enemy = (enemy_list*)malloc(sizeof(enemy_list));
    new_enemy->next = NULL;
    new_enemy->enemy = create_enemy("pacman.png",sy,sx);
    return new_enemy;
}

int shortest_path(Point src,Point dest,Map* map){
    Queue queue;
    if(src.x == dest.x && src.y == dest.y)return -1;
    int max = 400;
    int size = sqrt(max);
    initializeQueue(&queue,max);
//    queue.items = (Point*)malloc(size*sizeof(Point));
    int visited[size][size];
    int dist[size][size];
    int rowMoves[] = {-1, 1, 0, 0};
    int colMoves[] = {0, 0, -1, 1};
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            visited[i][j] = 0;
            dist[i][j] = INF;
        }
    }
    enqueue(&queue, src);
    dist[src.y][src.x] = 0;
    visited[src.y][src.x] = 1;
    int done = 0;
    while(!isEmpty(&queue)&& !done){
        Point curr = queue.items[queue.front];
        dequeue(&queue);
        for (int i = 0; i < 4; i++) {
            int newCol = curr.x + rowMoves[i];
            int newRow = curr.y + colMoves[i];
            //if reached destination
            if(newCol == dest.x && newRow == dest.y)done = 1;
            // Check if the adjacent cell is valid and hasn't been visited
            if (newCol >= 0
                && newCol < size
                && newRow >= 0
                && newRow < size
                && map->map[newRow][newCol] == FLOOR
                && dist[curr.y][curr.x] < dist[newRow][newCol]
                && !visited[newRow][newCol] ) {
                // Mark the cell as visited and enqueue it
                visited[newRow][newCol] = 1;
                dist[newRow][newCol] = dist[curr.y][curr.x] + 1;
                Point new = (Point){newCol,newRow};
                enqueue(&queue, new);
            }
        }
    }
    
    int inf = INF;
    int move = -1;
    for (int i = 0; i < 4; i++) {
        int newCol = dest.x + rowMoves[i];
        int newRow = dest.y + colMoves[i];
        
        if (newCol >= 0 && newCol < size && newRow >= 0 && newRow < size && dist[newRow][newCol] < inf) {
            inf = dist[newRow][newCol];
            if(i == 0)move = LEFT;
            else if(i == 1)move = RIGHT;
            else if(i == 2)move = UP;
            else move = DOWN;
        }
    }
    return move;
}

