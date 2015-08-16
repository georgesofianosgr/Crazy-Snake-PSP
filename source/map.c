#include "globals.h"
#include "move.h"
int map[12][24];

// UP-lEFT		CORNER: (y==2 && x==1 )	
// UP-RIGHT		CORNER:	(y==2 && x==15)
// DOWN-LEFT	CORNER:	(y==8 && x==1 )
// DOWN-RIGHT	CORNER: (y==8 && x==15)

void buildMap()
{
	int x;
	int y;



	for(y=0;y<12;y++)
	{
		for(x=0;x<24;x++)
		{
			//Upper Wall X1-Y1 -- X15-Y1
			if(y==0 && x>=1 && x<=22)
				map[y][x] = WALL;
			// Down Wall X1-Y9 -- X15-Y9
			else if(y==11 && x>=1 && x<=22)
				map[y][x] = WALL;
			// Left Wall X0-Y2 -- X0-Y8
			else if(x==0 && y>=1 && y<=10)
				map[y][x] = WALL;
			// Right Wall X16-Y2 -- X16-Y8
			else if(x==23 && y>=1 && y<=10)
				map[y][x] = WALL;

			// Start Snake Values Y5 X8 X9 X10
			if(y==5)
			{
				if(x==18)
				{
					map[y][x] = 1;
					snakeHeadX = x;
					snakeHeadY = y;


				}
				else if(x==19)
				{
					map[y][x] = 2;
				}
				else if(x==20)
				{
					map[y][x] = 3;
					snakeTailX = x;
					snakeTailY = y;	
				}
				
				
			}
		}
	}

}