



#include <stdlib.h>

int size;
char[100][100] graph;
char[100][100] snake;
char* ptr;

void creatGraph(){
	int i=0;
	int  j=0;
	
	for(i=0; i<100; i++){
		for(j=0; j<100; j++){
			char[i][j] = 1;
		}
	}
	
}


void startSnake(){
	int size =3;
	int i=0;
	snake[0][size-1]=2;
	ptr= &snake[0][size-1];
	for(i=0; i<size-2; i++){
		snake[0][i]=1;
	}
}

void move(char move){
	switch(move){
			
		case 'u':
		
	}
	
}

void add(int num){
	size+= num;
}

int isEaten(){
	if(
}

