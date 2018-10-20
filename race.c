/*-----------------------------------------------------------------------------
-					  		SE 185 Lab 08
-             Developed for 185-Rursch by T.Tran and K.Wang
-	Name:
- 	Section:
-	NetID:
-	Date:
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-								Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


/*-----------------------------------------------------------------------------
-								Defines
-----------------------------------------------------------------------------*/
/* Mathmatical constants */
#define PI 3.14159

/* 	Screen geometry
    Use ROWS and COLUMNS for the screen height and width (set by system)
    MAXIMUMS */
#define COLUMNS 100
#define ROWS 80

/* 	Character definitions taken from the ASCII table */
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '

/*	Number of samples taken to form an moving average for the gyroscope data
    Feel free to tweak this. */
#define NUM_SAMPLES 10


/*-----------------------------------------------------------------------------
-								Static Data
-----------------------------------------------------------------------------*/
/* 2D character array which the maze is mapped into */
char MAZE[COLUMNS][ROWS];


/*-----------------------------------------------------------------------------
-								Prototypes
-----------------------------------------------------------------------------*/
/*	POST: Generates a random maze structure into MAZE[][]
    You will want to use the rand() function and maybe use the output %100.
    You will have to use the argument to the command line to determine how
    difficult the maze is (how many maze characters are on the screen). */
void generate_maze(int difficulty);

/*	PRE: MAZE[][] has been initialized by generate_maze()
    POST: Draws the maze to the screen */
void draw_maze(void);

/*	PRE: 0 < x < COLUMNS, 0 < y < ROWS, 0 < use < 255
    POST: Draws character use to the screen and position x,y */
void draw_character(int x, int y, char use);

/*	PRE: -1.0 < mag < 1.0
    POST: Returns tilt magnitude scaled to -1.0 -> 1.0
    You may want to reuse the roll function written in previous labs. */
double calc_roll(double mag);

/* 	Updates the buffer with the new_item and returns the computed
    moving average of the updated buffer */
double m_avg(double buffer[], int avg_size, double new_item);

/* Detect if a failure has occured, when the avatar is stuck */
int detect_failure(int posX, int posY);


/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
/*	Main - Run with './ds4rd.exe -t -g' piped into STDIN */
void main(int argc, char* argv[])
{
    double xArray[NUM_SAMPLES];
    double gx, gy, gz, averageX = 0.0;
    int i = 0, j = 0;
    int t;
    int oldTime = 0, skillLevel = 2, playerLost = 0, avatarRow = 0, avatarCol = COLUMNS/2;

    /* WEEK 2 Generate the Maze */
    if (argc != 2 )
    {
        printw("You must enter the difficulty level on the command line.");
        refresh();
        return;
    }
    else
    {
        /* 	Setup screen for Ncurses
        The initscr functionis used to setup the Ncurses environment
        The refreash function needs to be called to refresh the outputs
        to the screen */
        initscr();
        refresh();

 //       sscanf(argv[1], "%d", &skillLevel);
        while (skillLevel < 0 || skillLevel > 100)
        {
            printw("The difficulty level must be between 0 and 100");
            refresh();
            sscanf(argv[1], "%d", &skillLevel);
        }

        // Generate and draw the maze, with initial avatar
        generate_maze(skillLevel);
        draw_maze();

        //Avatar placed and waiting
        //draw_character(width, height,use)
        draw_character(avatarCol, avatarRow, AVATAR);

        /* Read gyroscope data and fill the buffer before continuing */
        for(i = 0; i < NUM_SAMPLES; i++)
        {
            scanf("%d,%lf, %lf, %lf, %d, %d, %d, %d", &t, &gx, &gy, &gz);
            xArray[i] = gx;

        }

        /* Event loop */
        do
        {
            /* Read data, update average */
            scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d", &t, &gx, &gy, &gz);

            averageX = m_avg(xArray, NUM_SAMPLES, gx);

            averageX = calc_roll(averageX);

            /* Is it time to move?  if so, then move avatar */

            if ((t - oldTime) > 100  )
            {
                if ((averageX <= -0.3) && (MAZE[avatarRow][avatarCol + 1] == EMPTY_SPACE)  && (avatarRow < ROWS) && (avatarCol < COLUMNS -1))  //RIGHT MOVE?
                {
                    draw_character(avatarCol, avatarRow, EMPTY_SPACE);
                    avatarCol += 1; //UPDATE X
                    draw_character(avatarCol, avatarRow, AVATAR);
                }


                else if ((averageX >= 0.3) && (MAZE[avatarRow][avatarCol - 1] == EMPTY_SPACE)  && (avatarRow < ROWS ) && (avatarCol > 0))	//LEFT MOVE?
                {
                    draw_character(avatarCol, avatarRow, EMPTY_SPACE);
                    avatarCol -= 1; //UPDATE X
                    draw_character(avatarCol, avatarRow, AVATAR);
                }

                draw_character(avatarCol, avatarRow, AVATAR);

                if ((MAZE[avatarRow +1][avatarCol] == EMPTY_SPACE)  && (avatarRow < ROWS -1 ) ) //Wall below check
                {
                    draw_character(avatarCol, avatarRow, EMPTY_SPACE);
                    avatarRow += 1;	//UPDATE Y
                    draw_character(avatarCol, avatarRow, AVATAR);
                }
                else if(detect_failure(avatarCol, avatarRow) && (avatarRow < ROWS-1))
                {
                    playerLost = 1;
                    sleep(1);
                    break;
                }

                oldTime = t;
            }

        } while((avatarRow < ROWS - 1)); // Change this to end game at right time




        /* This function is used to cleanup the Ncurses environment.
        Without it, the characters printed to the screen will persist
        even after the progam terminates */
        endwin();

        /* Print the win message */
        if (playerLost == 1)
            printf("Game OVER!  You're a LOST!!!\n");
        else
            printf("YOU WIN!\n");

    }

}

void generate_maze(int difficulty){
    int num = 0, k = 0, l = 0;
    srand(time(0));
    for (k =0; k < ROWS; k++)
    {
        for (l = 0; l < COLUMNS; l++)
        {
            num = rand()%100;

            if (num < difficulty)
                MAZE[k][l] = WALL;
            else
                MAZE[k][l] = EMPTY_SPACE;
        }
    }
}

void draw_maze(void)
{
    int k = 0, l = 0;
    for (k = 0; k < ROWS; k++)
    {
        for (l = 0; l < COLUMNS; l ++)
        {
            draw_character(l,k, MAZE[k][l]);
        }
    }
}

double calc_roll(double x_mag){
    if (x_mag>1.0)	// Capping the max value at 1
        x_mag = 1.0;

    if (x_mag<-1.0)	// Capping the min value at -1
        x_mag = -1.0;

    return x_mag; // Returning the number
}


double m_avg(double buffer[], int avg_size, double new_item)
{

    int k;
    for (k = 0; k < avg_size - 1; k++)
        buffer[k] = buffer[k+1];

    buffer[k] = new_item;


    double sum = 0.0;

    for (k = 0; k < avg_size; k++)
        sum += buffer[k];


    return sum/avg_size;
}


int detect_failure(int posX, int posY)
{
    int left 	= posX;
    int right 	= posX;
    int i 		= 0;


    while(MAZE[posY][left] != WALL)
    {
        /* Return if we move all the way to the left without a wall */
        if(left <= 0)
            return 0;
        left--;
    }

    while(MAZE[posY][right] != WALL)
    {
        /* Return if we move all the way to the right without a wall */
        if(right >= COLUMNS)
            return 0;
        right++;
    }

    /* 	Check the row below us from left+1 to right-1 for an empty space. If
        there is an empty space, the avatar is not stuck, so we are not in a
        failure state. Otherwise, the the avatar cannot move any further and
        we will return true */
    for(i = left+1; i <= right - 1; i++)
    {
        if(MAZE[posY+1][i] == EMPTY_SPACE)
            return 0;
    }

    return 1;

}

/* 	PRE: 0 < x < COLUMNS, 0 < y < ROWS, 0 < use < 255
    POST: Draws character use to the screen and position x,y
    THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
    DO NOT NEED TO CHANGE THIS FUNCTION. */
void draw_character(int x, int y, char use)
{
    mvaddch(y,x,use);
    refresh();
}