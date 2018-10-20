/*  Lab 6 Bop-It
-	Name: Cobi Mom
- 	Section: A
-	NetID: cjmom
-	Date: 2/27/2018
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-	                            Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*-----------------------------------------------------------------------------
-	                            Defines
-----------------------------------------------------------------------------*/
#define TRUE 1
#define FALSE 0


/*-----------------------------------------------------------------------------
-	                            Prototypes
-----------------------------------------------------------------------------*/
int PlayGame(int input);
int SelectRandNum();
int readyToPlay();
/*-----------------------------------------------------------------------------
-							  Implementation
-----------------------------------------------------------------------------*/
int main(void) {
	
	int t, b1, b2, b3, b4;
	int input;
	int start = 0;
		
		printf("This is a Bop-It Game!\n");
		printf("Please press the Circle Button to begin!\n");
		while(TRUE)
		{			
			start = readyToPlay();		
			if(start == 1) 
			{
				input = SelectRandNum();
				PlayGame(input);				
			}
		}
	
	return 0;
}
		
/* Put your functions here */
int SelectRandNum()
{
	int r = 0;
    srand((int)time(0));
    r = ((rand() % 5) + 1);
    return r;
}

int readyToPlay()
{		
	int t, b1, b2, b3, b4;
	int temp;
	while(TRUE)
	{
		scanf("%d, %d, %d, %d, %d", &t, &b1, &b2, &b3, &b4);
		temp = t;
		if(b2 == 1)
		{
			return 1;
		}
	}
}

int PlayGame(int input)
{
	int totalTime = 2500;
	int t, b1, b2, b3, b4;
	int check = 0;
	int rounds = 0;
	
		if(input == 1) 
		{
			while(check == 0) 
			{
				scanf("%d, %d, %d, %d, %d", &t, &b1, &b2, &b3, &b4);
				printf("Press the triangle button!\n");
				printf("You have %d milliseconds to respond\n", totalTime - t);
				if(b1 == 1) 
				{
					rounds++;
					input = SelectRandNum();	
					check = 1;
				}
				else if(b2 == 1 || b3 == 1 || b4 == 1)
				{
					printf("Wrong button!\n");
					printf("You lose!\n");
					printf("You made it through %d rounds!\n", rounds);
					exit(0);
				}
				else if(totalTime - t == 0)
				{
					printf("Thanks for playing!\n");
					printf("You made it through %d rounds!", rounds);
					exit(0);
				}
			}	
		}
		
		if(input == 2) 
		{
			while(check == 0) 
			{
				scanf("%d, %d, %d, %d, %d", &t, &b1, &b2, &b3, &b4);
				printf("Press the Circle button!\n");
				printf("You have %d milliseconds to respond\n", totalTime - t);
				if(b2 == 1) 
				{					
					rounds++;
					input = SelectRandNum();
					check = 1;					
				}
				else if(b1 == 1 || b3 == 1 || b4 == 1)
				{
					printf("Wrong button!\n");
					printf("You lose!\n");
					printf("You made it through %d rounds!\n", rounds);
					exit(0);
				}
				else if(totalTime - t == 0)
				{
					printf("Thanks for playing!\n");
					printf("You made it through %d rounds!", rounds);
					exit(0);
				}
			}	
		}
		
		else if(input == 3) 
		{
			while(check == 0) 
			{
				scanf("%d, %d, %d, %d, %d", &t, &b1, &b2, &b3, &b4);
				printf("Press the X button!\n");
				printf("You have %d milliseconds to respond\n", totalTime - t);
				if(b3 == 1) 
				{
					rounds++;
					input = SelectRandNum();
					check = 1;
				}
				else if(b1 == 1 || b2 == 1 || b4 == 1)
				{
					printf("Wrong button!\n");
					printf("You lose!\n");
					printf("You made it through %d rounds!\n", rounds);
					exit(0);
				}
				else if(totalTime - t == 0)
				{
					printf("Thanks for playing!\n");
					printf("You made it through %d rounds!", rounds);
					exit(0);
				}
			}	
		}
		
		else if(input == 4) 
		{
			while(check == 0) 
			{
				scanf("%d, %d, %d, %d, %d", &t, &b1, &b2, &b3, &b4);
				printf("Press the triangle button!\n");
				printf("You have %d milliseconds to respond\n", totalTime - t);
				if(b4 == 1) 
				{
					rounds++;
					input = SelectRandNum();
					check = 1;
				}
				else if(b1 == 1 || b2 == 1 || b3 == 1)
				{
					printf("Wrong button!\n");
					printf("You lose!\n");
					printf("You made it through %d rounds!\n", rounds);
					exit(0);
				}
				else if(totalTime - t == 0)
				{
					printf("Thanks for playing!\n");
					printf("You made it through %d rounds!", rounds);
					exit(0);
				}
			}	
		}	
}

/*NOTES
Triangle = b1
Circle = b2
X = b3
Square = b4
*/