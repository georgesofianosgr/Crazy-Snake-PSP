#include <pspkernel.h>
#include <psprtc.h>
#include <psptypes.h>
#include <stdio.h>
#include "input.h"
#include "map.h"
#include "globals.h"

#include "graphics.h"
#include "callbacks.h"
#include "colors.h"



int currentDirection = DIR_LEFT;
int tempDirection = 0;
int newDirection  = DIR_LEFT;


// Snakes Values
int snakeHeadX = 0; // Snakes Head Position
int snakeHeadY = 0;
int snakeTailX = 0; // Snakes Tail Position
int snakeTailY = 0;
int snakeBodyN = 0; // Snakes Body Number Of Blocks

// Regulate Snake Speed
u64 ticks = 0;
u64 SpeedTime = 300000;
int currentSpeed = 300000;

// Declare
int speedLimitEnabled();
void checkNewDirection();
void moveSnake();
void moveHead();

void moveClear()
{
currentDirection = DIR_LEFT;
tempDirection = 0;
newDirection  = DIR_LEFT;


// Snakes Values
snakeHeadX = 0; // Snakes Head Position
snakeHeadY = 0;
snakeTailX = 0; // Snakes Tail Position
snakeTailY = 0;
snakeBodyN = 0; // Snakes Body Number Of Blocks

// Regulate Snake Speed
ticks = 0;
SpeedTime = 120000;
currentSpeed = 120000;

}

void moveLoop()
{

	if(levelX==1)
	{
		changeLevel();
	}

	// Take Input
	newDirection = getInput();

	checkNewDirection();
	if(speedLimitEnabled())
	{
		if(newDirection !=0)
			tempDirection = newDirection;
	}
	else
	{
		if(tempDirection)
		{
			currentDirection = tempDirection;
			tempDirection=0;
		}
		else
		{
			if(newDirection)
				currentDirection = newDirection;
		}
		
		moveSnake();
	}

}

int speedLimitEnabled()
{
	sceRtcGetCurrentTick(&ticks);
   if(ticks >= SpeedTime)
   {
        SpeedTime = ticks + currentSpeed;
		return 0;
   }
   else
	   return 1;
}

void checkNewDirection()
{

	if(currentDirection == DIR_UP || currentDirection == DIR_DOWN)
	{
		if(newDirection == DIR_UP || newDirection == DIR_DOWN)
			newDirection = 0;
	}
	else if(currentDirection == DIR_RIGHT || currentDirection == DIR_LEFT)
	{
		if(newDirection == DIR_RIGHT || newDirection == DIR_LEFT)
			newDirection = 0;
	}
}

int getCurrentDirection()
{
	return currentDirection;
}

void moveSnake()
{

			int ypos=0;
			int xpos=0;
			if(currentDirection == DIR_UP)
			{
					ypos = -1;
					xpos =  0;
			}
			else if(currentDirection == DIR_DOWN)
			{
					ypos = 1;
					xpos = 0;	
			}
			else if(currentDirection == DIR_LEFT)
			{
					ypos =  0;
					xpos = -1;	
			}
			else if(currentDirection == DIR_RIGHT)
			{
					ypos = 0;
					xpos = 1;	
			}

				if(map[snakeHeadY + ypos][snakeHeadX + xpos]==WALL || map[snakeHeadY + ypos][snakeHeadX + xpos]>=1)
				{
					GAMEOVER = 1;
				}
				else if(map[snakeHeadY + ypos][snakeHeadX + xpos]==POINT)
				{
					pointAlive = 0;
					POINTS += pointsGain;
					moveHead();
					map[snakeHeadY + ypos][snakeHeadX + xpos] = 1 ;
					snakeHeadY += ypos;
					snakeHeadX += xpos;
					snakeTailN++;
					
				}
				else if(map[snakeHeadY + ypos][snakeHeadX + xpos]==EMPTY)
				{
					moveHead();
					map[snakeHeadY + ypos][snakeHeadX + xpos] = 1 ;
					snakeHeadY += ypos;
					snakeHeadX += xpos;

				}
			

}

void moveHead()
{
	int exitMapSearch = 0;
	int y;
	int x;
	int blocksFound = 0;

	// Delete Tail
	if(pointAlive)
	{
		map[snakeTailY][snakeTailX]=0;
	}

	for(y=1;y<12;y++)//or values y2 y9
	{
		for(x=1;x<23;x++)//or values x1 x16
		{

					if(map[y][x]>=1) // Increasing Snakes Body Number
					{
						map[y][x]++;
						blocksFound++;

						if(pointAlive && map[y][x] == snakeTailN) // Set New Tail Offsets
						{
							snakeTailX=x;
							snakeTailY=y;
						}

					}

					// Exit If All Found
					if(blocksFound==snakeTailN)
						exitMapSearch=1;
	
			}
			if(exitMapSearch)
				break;
		
		if(exitMapSearch)
				break;
	}
}

void setSpeed(int Speed)
{
	if(Speed==0)
    {
	 SpeedTime = 300000;
	 currentSpeed = 300000;
     pointsGain=3;
    }
    else if(Speed==1)
    {
	 SpeedTime = 300000;
	 currentSpeed = 300000;
     pointsGain=3;
    }
    else if (Speed==2)
    {
	 SpeedTime = 270000;
	 currentSpeed = 270000;
     pointsGain=4;
    }
    else if (Speed==3)
    {
	 SpeedTime = 240000;
	 currentSpeed = 240000;
     pointsGain=5;
    }
    else if (Speed==4)
    {
	 SpeedTime = 180000;
	 currentSpeed = 180000;
     pointsGain=7;
    }
    else if (Speed==5)
    {
	 SpeedTime = 100000;
	 currentSpeed = 100000;
     pointsGain=8;
    }
}

void changeLevel()
{
    if(POINTS<27)
    {
	 LEVEL=1;
	 currentSpeed = 300000;
     pointsGain=3;
    }
    else if(POINTS>=27 && POINTS < 90 )
    {
	 LEVEL=2;
	 currentSpeed = 260000;
     pointsGain=4;
    }
    else if(POINTS>=90 && POINTS < 150 )
    {
	 LEVEL=3;
	 currentSpeed = 230000;
     pointsGain=5;
    }
    else if(POINTS>=150 && POINTS < 220 )
    {
	 LEVEL=4;
	 currentSpeed = 160000;
     pointsGain=7;
    }
    else if(POINTS>=220)
    {
	 LEVEL=5;
	 currentSpeed = 110000;
     pointsGain=8;
    }
}