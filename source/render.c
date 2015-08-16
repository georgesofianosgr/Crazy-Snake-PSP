#include <pspkernel.h>
#include <pspdisplay.h>
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "map.h"
#include "globals.h"
#include "colors.h"
// render Menu -> TO BE DONE


void renderMap(Image** gameBG,Image** snakeBody,Image** snakeHead,Image** snakeTail,Image**pointImg)
{
	// 26x  59y
	// BLIT BACKGROUND
	blitAlphaImageToScreen(0,0,480,272,*gameBG,0,0);
	int x;
	int y;
	for(y=0;y<12;y++)
	{
		for(x=0;x<24;x++)
		{
			// BLIT SNAKE'S BODY
			if(map[y][x]==1)
				blitAlphaImageToScreen(0,0,20,20,*snakeHead,6+x*20,39+y*20);
			if(map[y][x]>=2 && map[y][x]<snakeTailN)
				blitAlphaImageToScreen(0,0,20,20,*snakeBody,6+x*20,39+y*20);
			if(map[y][x]==snakeTailN)
				blitAlphaImageToScreen(0,0,20,20,*snakeTail,6+x*20,39+y*20);
			// BLIT POINT CIRCLE
			if(map[y][x]==POINT)
				blitAlphaImageToScreen(0,0,20,20,*pointImg,6+x*20,39+y*20);
		}
	}
	

}

// Render Stats -> TO BE DONE

void renderStats()
{
	char buffer[50];
	int pointsX=300;
	if(POINTS >999)
		pointsX=290;
	else if(POINTS >99)
		pointsX=293;
	else if(POINTS>9)
		pointsX=296;

	// POINTS
	sprintf(buffer,"%d",POINTS);
	printTextScreen(pointsX,34,buffer,clr_white);
	// LEVEL
	sprintf(buffer,"%d",LEVEL);
	printTextScreen(418,34,buffer,clr_white);
}