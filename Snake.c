//
//  Snake.c
//  Snake
//
//  Created by Cobi Mom on 10/19/18.
//  Copyright © 2018 Cobi Mom. All rights reserved.
//

#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <stdbool.h>


//CONSTANTS
#define EMPTY_SPACE ' '
#define FOOD 'O'
#define SNAKEBODYPART '*'
#define COLUMNS 50
#define ROWS 50
#define TRUE 1
#define BOUNDARY '$'

typedef struct node{
    char data;
    struct node * next;
    struct node * prev;
    int row;
    int col;
}node;

//VARIABLES
int size;
char graph[COLUMNS][ROWS];
char* ptr;
node * head; // add head node
char endGame = 0;
//PROTOTYPES

void startSnake();

//initialize the environment of the game
void startEnvironment();

//make a piece of food spawn in a random spot on the gameboard
void makeFood();

//Draw character to the screen
//position is (x,y)
void draw_character(int x, int y, char use);

void add();

void mov(int movee);

void isEaten();

void main()
{
    int up = 0;
    int left = 0;
    int down = 0;
    int right = 0;
    int time=0;
    int oldTime=0;
    int dir = 1;
    
    
	printf("Press UP to START: " );
	fflush(stdout);
	while(up==0){
		scanf("%d, %d, %d, %d, %d", &time, &up, &left, &down, &right);

	}
	
    //Setup screen for ncurses
    initscr();
    refresh();
    
    //make the map
    startEnvironment();
    
    startSnake();
    
    //generate a piece of food on at a random spot on the map
    makeFood();
    
    scanf("%d, %d, %d, %d, %d", &oldTime, &up, &left, &down, 
	&right);
    
    
    
    while(TRUE)
    {
        
        //scan for dpad input
        scanf("%d, %d, %d, %d, %d", &time, &up, &left, &down, &right);
         if(time-oldTime >= 100){
			//if up is pressed, return 1
			if(up == 1 && dir != 3)
			{
				dir = 1;
			}
			
			//if left is pressed, return 2
			else if(left == 1 && dir != 4)
			{
				dir = 2;
			}
			
			//if down is pressed, return 3
			else if(down == 1 && dir != 1)
			{
				dir = 3;
			}
			
			//if right is pressed, return 4
			else if(right == 1 && dir != 2)
			{
				dir = 4;
			}
			
		   
				mov(dir);
				if(endGame==1){
					printf("game over");
					fflush(stdout);
					return;
				}
				oldTime=time;
        }
    }
    endwin();
}

//initialize the environment of the game
void startEnvironment()
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    
    //loop through and make every spot on our gameboard an empty space
    for(i = 0; i < COLUMNS; i++)
    {
        for(j = 0; j < ROWS; j++)
        {
            draw_character(i, j, EMPTY_SPACE);
        }
    }
    
    //make outer edge the boundary
    for(k = 0; k < COLUMNS; k++)
    {
        draw_character(k, 0, SNAKEBODYPART);
        draw_character(k, ROWS-1, SNAKEBODYPART);
        graph[k][0] = SNAKEBODYPART;
        graph[k][ROWS-1] = SNAKEBODYPART;
    }
    
    for(l = 0; l < ROWS; l++)
    {
        draw_character(0, l, SNAKEBODYPART);
        draw_character(COLUMNS-1, l, SNAKEBODYPART);
        graph[0][l] = SNAKEBODYPART;
        graph[COLUMNS-1][l] = SNAKEBODYPART;
    }
    
}

//make a piece of food spawn in a random spot on the gameboard
void makeFood()
{
    srand(time(NULL));
    //generate random number between 3-22
    int randVert = rand() % (23 - 3) + 3;
    int randHori = rand() % (23 - 3) + 3;
    
    //value at random location is now a piece of food
    while(graph[randVert][randHori] == SNAKEBODYPART)
    {
        randVert = rand() % (23 - 3) + 3;
        randHori = rand() % (23 - 3) + 3;
    }
    graph[randVert][randHori] = FOOD;
    draw_character(randVert, randHori, FOOD);
}

//Draw character to the screen
//position is (x,y)
void draw_character(int x, int y, char use)
{
    mvaddch(y, x, use);
    refresh();
}

//read an input from the dualshock dpad
//char direction()
//{
//    int up = 0;
//    int left = 0;
//    int down = 0;
//    int right = 0;
//
//    while(TRUE)
//    {
//        //scan for dpad input
//        scanf("%d, %d, %d, %d", &up, &left, &down, &right);
//
//        //if up is pressed, return u
//        if(up == 1)
//        {
//            return 'u';
//        }
//
//        //if left is pressed, return l
//        else if(left == 1)
//        {
//            return 'l';
//        }
//
//        //if down is pressed, return d
//        else if(down == 1)
//        {
//            return 'd';
//        }
//
//        //if right is pressed, return r
//        else if(right == 1)
//        {
//            return 'r';
//        }
//    }
//}

void mov(int movee)
{
    
    
    node * p = head;
    node * temp =(node*)malloc(sizeof(node));
    temp->row = p->row;
    temp->col = p->col;
    
    
    
    switch(movee)
    {
        case 1:
            
            head->row = head->row -1; //add if contraints
			if( graph[head->col][head->row] == SNAKEBODYPART || head->row<0 )
             endGame = 1; 
            break;
        case 2:
            head->col = head->col - 1; //add if contraints
            if( graph[head->col][head->row] == SNAKEBODYPART || head->col < 0 )
             endGame = 1;     
            break;
            
        case 3:
            
            head->row = head->row + 1; //add if contraints
			if( graph[head->col][head->row] == SNAKEBODYPART || head->row > ROWS )
             endGame = 1; 
            break;
            
        case 4:
            head->col = head->col+1 ; //add if contraints
            if( graph[head->col][head->row] == SNAKEBODYPART || head->col > COLUMNS )
             endGame = 1; 
            break;
            
            
    }
    
    if(endGame==1)
        return;
    draw_character(head->col,head->row, head->data);
    
    
    
    
    while(p->next != NULL){
        
        
        p= p->next;
        
        int r = temp->row;
        int c = temp->col;
        
        temp->row = p->row;
        temp->col = p->col;
        
        p->row = r;
        p->col = c;
        
        
    }
    isEaten();
    draw_character(temp->col,temp->row, EMPTY_SPACE);
    graph[temp->col][temp->row] = EMPTY_SPACE;
    graph[head->col][head->row]= SNAKEBODYPART;
}

void add()
{
    size++;
    node * temp = NULL;
    node * p = NULL;
    temp= (node*)malloc(sizeof(node));
    temp->data = SNAKEBODYPART;
    
    
    p=head;
    while(p->next !=NULL)
        p=p->next;
    p->next = temp;
    
    temp->next = NULL;
    temp->prev = p;
    temp->col = NULL;
    temp->row = NULL;
}

void startSnake() {
    size=1;
    head = (node*)malloc(sizeof(node));
    head->data = SNAKEBODYPART;
    head->next = NULL;
    head->prev = NULL;
    head->row = ROWS/2;
    head->col = COLUMNS/2;
    graph[head->row][head->col]= head->data;
    draw_character(head->row, head->col, head->data);
}

void isEaten()
{
    if(graph[head->col][head->row] == FOOD)
    {
        add();
        makeFood();
    }
}