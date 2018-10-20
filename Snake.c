//
//  Snake.c
//  Snake
//
//  Created by Cobi Mom on 10/19/18.
//  Copyright © 2018 Cobi Mom. All rights reserved.
//



#include "Snake.h"
#include <stdlib.h>

int size;
char graph[100][100];
char snake[100][100];
char* ptr;

void creatGraph()
{
    int i=0;
    int j=0;
    
    for(i=0; i<100; i++)
    {
        for(j=0; j<100; j++)
        {
            graph[i][j] = 1;
        }
    }
}


void startSnake(){
    int size = 3;
    int i = 0;
    snake[0][size - 1] = 2;
    ptr = &snake[0][size - 1];
    for(i=0; i<size-2; i++){
        snake[0][i]=1;
    }
}

void mov(char movee)
{
    switch(movee)
    {
        case 'u':
    }
    
}

void add(int num){
    size+= num;
}

int isEaten(){
    if(
        }
        
char direction()
{
    int up = 0;
    int left = 0;
    int down = 0;
    int right = 0;
    
    while(TRUE)
    {
        //scan for dpad input
        scanf("%d, %d, %d, %d", &up, &left, &down, &right)
        
        //if up is pressed, return u
        if(up == 1)
        {
            return u;
        }
        
        //if left is pressed, return l
        else if(left == 1)
        {
            return l;
        }
        
        //if down is pressed, return d
        else if(down == 1)
        {
            return d;
        }
        
        //if right is pressed, return r
        else if(right == 1)
        {
            return r;
        }
    }
}
       
void makeFood()
{
    srand(time(NULL));
    
    //generate random number between 3-97
    int randVert = rand() % (98 - 3) + 3;
    int randHori = rand() % (98 - 3) + 3;
    
    //value at random location is now 2(a piece of food)
    graph[randVert][randHori] = 2;
}
