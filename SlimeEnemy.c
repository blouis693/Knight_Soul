//
//  SlimeEnemy.c
//  Knight_Soul
//
//  Created by Brandon Louis Chiender on 2024/2/1.
//

#include "SlimeEnemy.h"
#include "game.h"
#include <math.h>
#include <time.h>


extern int TILE_SIZE;
int INF = 999999999;
int looping = 0;

Enemylist* insert(SlimeEnemy* enemy){
    Enemylist* tmp = (Enemylist*)malloc(sizeof(Enemylist));
    if(!tmp)game_log("failed\n");
    tmp->next = NULL;
    tmp->enemy = enemy;
    return tmp;
}
SlimeEnemy* create_enemy(char * path,int row,int col){
    SlimeEnemy* enemy =(SlimeEnemy*)malloc(sizeof(SlimeEnemy));
    enemy->sprite_size = 64;
    enemy->pos = (Point){col*TILE_SIZE+TILE_SIZE/4,row*TILE_SIZE+TILE_SIZE/4};
    game_log("coord x:%d \n coords y:%d \n",enemy->pos.x/TILE_SIZE,enemy->pos.y/TILE_SIZE);
    enemy->speed = 3;
    enemy->image = al_load_bitmap(path);
    enemy->Status = Idle;
    if(!enemy->image){
        game_abort("Error Load Bitmap with path : %s", path);
    }
    
    return enemy;
}
void move_enemy(SlimeEnemy * enemy,int move,int speed){
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
}
void update_enemy(SlimeEnemy * enemy,Map* map,Point src,Point dest){
    int speed = 0;
    if(enemy->Status == Idle){
        enemy->dist = TILE_SIZE/enemy->speed;
        enemy->save_dist = enemy->dist;
        enemy->direction = shortest_path(dest,src,map);
//        if(enemy->direction == -1){
//            enemy->Status = Jump;
//            enemy->direction = UP;
//            looping = 2;
//        }
//        else{
//            enemy->Status = Moving;
//        }
        enemy->Status = Moving;
    }
    if(enemy->Status == Moving){
        if(enemy->dist == -1){
            enemy->Status = Idle ;
            speed = TILE_SIZE-enemy->save_dist*enemy->speed;
            enemy->direction = -1;
        }
        else speed = enemy->speed;
        enemy->dist--;
        move_enemy(enemy, enemy->direction,speed);
    }
    if(enemy->Status == Jump){
        speed = 2;

        if(enemy->dist == 0){
            enemy->direction = -1;
            if(looping == 2){
                looping--;
                enemy->direction = DOWN;
                enemy->dist = enemy->save_dist+1;
            }
            else if(looping == 1){
                enemy->Status = Idle ;
                enemy->direction = UP;
            }

        }
        enemy->dist--;

        move_enemy(enemy, enemy->direction,speed);
    }
}

void draw_enemy(SlimeEnemy * enemy,Point cam){
    int dy = enemy->pos.y - cam.y - TILE_SIZE/4; // destiny y axis
    int dx = enemy->pos.x - cam.x - TILE_SIZE/4; // destiny x axis
    al_draw_scaled_bitmap(
        enemy->image,
        0, 0, 16, 16,
        dx, dy, enemy->sprite_size, enemy->sprite_size,
        0);
}

void delete_enemy(SlimeEnemy * enemy){
    al_destroy_bitmap(enemy->image);
}

int shortest_path(Point src,Point dest,Map* map){
    Queue queue;
    if(src.x == dest.x && src.y == dest.y)return -1;
    int max = map->row*map->col;
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

