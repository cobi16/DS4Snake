

//
//  Snake.c
//  Snake
//
//  Created by Cobi Mom on 10/19/18.
//  Copyright © 2018 Cobi Mom. All rights reserved.
//

#include <stdlib.h>
#include <time.h>

//CONSTANTS
#define EMPTY_SPACE ' '
#define FOOD 'O'
#define SNAKEBODYPART '*'
#define COLUMNS 100
#define ROWS 100

//VARIABLES
int size;
int graph[COLUMNS][ROWS];
node * head; // add head node

//PROTOTYPES

//create a graph with a value of 1 in each spot, so they are not null
void createGraph();

void startSnake();

void main
{
    OOOOOOOOO
    **********
    
}

//initialize the environment of the game
void startEnvironment()
{
    int i = 0;
    int j = 0;
    
    //loop through and make every spot on our gameboard an empty space
    for(i = 0; i < COLUMNS; i++)
    {
        for(j = 0; j < ROWS; j++)
        {
            draw_character(i, j, EMPTY_SPACE);
        }
    }
}

//make a piece of food spawn in a random spot on the gameboard
void makeFood()
{
    srand(time(NULL));
    
    //generate random number between 3-97
    int randVert = rand() % (98 - 3) + 3;
    int randHori = rand() % (98 - 3) + 3;
    
    //value at random location is now a piece of food
    draw_character(randVert, randHori, FOOD);
}

//Draw character to the screen
//position is (x,y)
void draw_character(int x, int y, char use)
{
    mvaddch(y, x, use);
    refresh();
}



void mov(char movee)
{
    switch(movee)
    {
        case 'u':
    }
    
}

void add()
{
    size++;
	node * temp = null;
	node * p = null;
	temp= (node*)malloc(sizeof(node));
	temp->data = SNAKEBODYPART;
	
	
	p=head;
	while(p->next !=null)
		p=p->next;
	p->next = temp;
	
	temp->next = null;
	temp->prev = p;
	temp->
		
	
	
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


void startSnake(){
	size=1;
	head = (node*)malloc(sizeof(node));
	head->data = SNAKEBODYPART;
	head->next = null;
	head->prev = null;
	head->row = 0;
	head->col = 0;
	graph[head->row][head->col]= head->data;

}


typedef struct node{
	char data;
	struct node * next;
	struct node * prev;
	int row;
	int col;
}node;
