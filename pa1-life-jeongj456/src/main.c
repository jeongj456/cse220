#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "life.h"

void create_next_gen_matrix(int org, int next);
void empty_matrix(int x);
bool will_it_live(int y, int x, int org);
bool will_it_come_alive(int y, int x, int org);


char grid[2][GRIDY+2][GRIDX+2];

int main(int argc, char *argv[]){
    int generation = 0;

    if(argc!=3){
        printf("Error: incorrect input");
        return -1;
    }

    empty_matrix(0);
    empty_matrix(1);

    //creates the first next_gen_matrix
    char **starting_position=parse_life(argv[1]);
    for (int y=0; y<GRIDY; y++){        //loops through each array in the list
        for (int x=0; x<GRIDX; x++){    //loops through each value in that array
            if(starting_position[y][x]==LIVE||starting_position[y][x]==DEAD){
                grid[0][y+1][x+1]=starting_position[y][x];  
            }else{
                printf("Error: Not correct char 'X' or ' '!\n");
                return -1;
            }
        }
    }
    while(generation!=atoi(argv[2])){
        //if generation modulo remainder is 0, next gen matrix is grid[1]
        if(generation % 2 == 0){
            create_next_gen_matrix(0, 1);
        }//if generation modulo remainder is not 0, next gen matrix is grid[0]
        else if (generation % 2 != 0){
            create_next_gen_matrix(1, 0);
        }
        generation++;
    }
    for (int y=1; y<GRIDY+1; y++){        
        for (int x=1; x<GRIDX+1; x++){ 
            putchar(grid[generation%2][y][x]);  //correct output method?
        }putchar('\n');
    }
    return 0;
}


//____________________________________________________________________________________________

void create_next_gen_matrix(int org, int next){
    for (int y=1; y<GRIDY+1; y++){
        for (int x=1; x<GRIDX+1; x++){ 
            if(grid[org][y][x]==LIVE){
                if(will_it_live(y, x, org)){
                    grid[next][y][x]=LIVE;
                }else{
                    grid[next][y][x]=DEAD;
                }
            }else{
                if(will_it_come_alive(y, x, org)){
                    grid[next][y][x]=LIVE;
                }else{
                    grid[next][y][x]=DEAD; 
                }
            }
        }
    }
}

void empty_matrix(int md){
    for (int y=0; y<GRIDY+2; y++){
        for(int x=0; x<GRIDX+2; x++){
            grid[md][y][x]=DEAD;
        }
    }  
}

bool will_it_live(int y, int x, int org){
    int count = 0;
    for (int yc=y-1; yc<y+2; yc++){
        for (int xc=x-1; xc<x+2; xc++){
            if (grid[org][yc][xc]==LIVE){
                count ++;
            }
        }
    }
    count=count-1;
    if (count<2 || count >3){
        return false;
    }
    return true;
}

bool will_it_come_alive(int y, int x, int org){
    int count = 0;
    for (int yc=y-1; yc<y+2; yc++){
        for (int xc=x-1; xc<x+2; xc++){
            if (grid[org][yc][xc]==LIVE){
                count ++;
            }
        }
    }
    if (count==3){
        return true;
    }
    return false;
}
