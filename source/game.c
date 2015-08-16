#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <psprtc.h>
#include <stdio.h>
#include <pspctrl.h>
#include <time.h>
#include <stdlib.h>

#include "triggers.h"
#include "menu.h"
#include "callbacks.h"
#include "graphics.h"
#include "intro.h"
#include "render.h"
#include "colors.h"
#include "map.h"
#include "globals.h"
#include "move.h"
#include "level.h"
PSP_MODULE_INFO("Crazy Snake PSP",0,1,1);

void randomPoint();
void gameLoop();
void loadGameImages(Image**,Image**,Image**,Image**,Image**,Image**,Image**);
void freeGameImages(Image**,Image**,Image**,Image**,Image**,Image**,Image**);
int pauseGame(Image**snakeHead,Image**snakeBody,Image**SnakeTail,Image**pauseScreen);
void clearGame();
void screenGameOver(Image**);


int main(void)
{
	//Initialize
	pspDebugScreenInit();
	SetupCallbacks();
	initGraphics();

	introLoop();
	//While Start
	while(isRunning())
	{
		// Menu
		if(isRunning())
			menuLoop();

		//Level
		if(isRunning() && menuChoice==2)
			selectLevel();

		//Main Game
		if(isRunning() && menuChoice==1)
			gameLoop();

	}
	

	//Exit
	sceKernelExitGame();
	return 0;
}

void gameLoop()
{
	// Load Images
	Image* gameBG;
	Image* snakeBody;
	Image* snakeHead;
	Image* snakeTail;
	Image* pointImg;
	Image* pauseScreen;
	Image* gameOver;
	loadGameImages(&gameBG,&snakeBody,&snakeHead,&snakeTail,&pointImg,&pauseScreen,&gameOver);
	srand(time(NULL));

	SceCtrlData pad;

	// Frame Regulating
	u64 firstTicks = 0;
	u64 lastTicks = 0;

	// Create Map
	if(isRunning())
		buildMap();
	
	// Add Random Point
	randomPoint();

	// Set Speed
	setSpeed(LEVEL);

	// Buttons Switches
	int lrtriggerPressed = 0;
	
	// Main Game Loop
	while(isRunning())
	{
		// Frame Regulating START
		sceRtcGetCurrentTick(&firstTicks);


		//Check For pause -> TO BE DONE 
		sceCtrlReadBufferPositive(&pad, 1);



		// Logic - Snake Move + Get Input + GameOver + Points -> TO BE DONE
		moveLoop();
		// Random Point
		if(!pointAlive)
		randomPoint();
		//Render Snake
		renderMap(&gameBG,&snakeBody,&snakeHead,&snakeTail,&pointImg);
		//Render Stats
		renderStats();

		//Update Screen
		sceDisplayWaitVblankStart();
		flipScreen();

		//pause
		if(pad.Buttons & PSP_CTRL_START)
		{
			sceKernelDelayThread(500000);
			if(pauseGame(&snakeHead,&snakeBody,&snakeTail,&pauseScreen) == 1)
				break;
			sceKernelDelayThread(500000);
		}

		// GO MODE
		if(PSPGOAvail)
		{
			if((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_RTRIGGER) && !lrtriggerPressed)
			{
				sceKernelDelayThread(500000);
				if(pauseGame(&snakeHead,&snakeBody,&snakeTail,&pauseScreen) == 1)
					break;
				lrtriggerPressed=1;
				sceKernelDelayThread(500000);
			}
			else if(!(pad.Buttons & PSP_CTRL_LTRIGGER) || !(pad.Buttons & PSP_CTRL_RTRIGGER))
			{
				lrtriggerPressed=0;
			}
		}


		// Frame Regulating END
		sceRtcGetCurrentTick( &lastTicks);
		if((lastTicks - firstTicks) < 1000000 / FPS)
		{
			sceKernelDelayThread((1000000 / FPS) - (lastTicks - firstTicks) );
		}
		
		///////////////////////////////////////////////TEST/////////////////////////////////////
		// GAME OVER TEST
		//
			if(GAMEOVER==1)
			{
				screenGameOver(&gameOver);
				break;
			}
	}
	///////////////////////////////////////////////////////////////////
		// Free Images
		freeGameImages(&gameBG,&snakeBody,&snakeHead,&snakeTail,&pointImg,&pauseScreen,&gameOver);
		clearGame();

}

void loadGameImages(Image**gameBG,Image**snakeBody,Image**snakeHead,Image**snakeTail,Image**pointImg,Image**pauseScreen,Image**gameOver)
{
	char buffer[40];
	sprintf(buffer,"images/gamebg.png");
	*gameBG = loadImage(buffer);
	sprintf(buffer,"images/sbody.png");
	*snakeBody = loadImage(buffer);
	sprintf(buffer,"images/shead.png");
	*snakeHead = loadImage(buffer);
	sprintf(buffer,"images/stail.png");
	*snakeTail = loadImage(buffer);
	sprintf(buffer,"images/point.png");
	*pointImg = loadImage(buffer);
	sprintf(buffer,"images/pause.png");
	*pauseScreen = loadImage(buffer);
	sprintf(buffer,"images/gameover.png");
	*gameOver = loadImage(buffer);

	if(!(*gameBG) || !(*snakeBody) || !(*snakeHead) || !(*snakeTail) || !(*pointImg) || !(*pauseScreen) || !(*gameOver))
	{
		clearScreen(clr_black);
		printTextScreen(10,10,"Load Image Failed!",clr_white);
		printTextScreen(10,20,"Make sure that you transferred all images to psp.",clr_white);
		flipScreen();
		sceKernelDelayThread(1000000*3);
		exitGame();
		
	}
}

void freeGameImages(Image**gameBG,Image**snakeBody,Image**snakeHead,Image**snakeTail,Image**pointImg,Image**pauseScreen,Image**gameOver)
{
	if(*gameBG)
		freeImage(*gameBG);
	if(*snakeBody)
		freeImage(*snakeBody);
	if(*snakeHead)
		freeImage(*snakeHead);
	if(*snakeTail)
		freeImage(*snakeTail);
	if(*pointImg)
		freeImage(*pointImg);
	if(*pauseScreen)
		freeImage(*pauseScreen);

	/* I'm Checking if images are loaded or 
	else game will crash trying to free them */
}

void randomPoint()
{
	int pointY;
	int pointX;

	do
    {
    pointY = rand() % 10 + 1;
    pointX = rand() % 22 + 1;
    }while( map[pointY][pointX] >=1);
    map[pointY][pointX] = POINT;
    pointAlive = 1;
}

int pauseGame(Image**snakeHead,Image**snakeBody,Image**snakeTail,Image**pauseScreen)
{
	SceCtrlData pad;
	int choice = 1;
	int upPressed = 0;
	int downPressed = 0;
	int ltriggerPressed = 0;
	int rtriggerPressed = 0;
	int startPressed = 1;
	int lrTriggersPressed = 1;


	while(isRunning())
	{
		// GET INPUT
		sceCtrlReadBufferPositive(&pad, 1);

		if(choice == 1 && pad.Buttons & PSP_CTRL_CROSS)
			break;
		else if(choice ==2 && pad.Buttons & PSP_CTRL_CROSS)
		{
			return 1;
		}

		if(pad.Buttons & PSP_CTRL_START && !startPressed)
			break;
		else if(!(pad.Buttons & PSP_CTRL_START))
		{
			startPressed=0;
		}

		//GO MODE
		if(PSPGOAvail)
		{
			if((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_RTRIGGER) && !lrTriggersPressed)
			{
				lrTriggersPressed=1;
				if(choice==1)
					return 0;
				else if(choice==2)
				{
					return 1;
				}
			}
			else if(!(pad.Buttons & PSP_CTRL_LTRIGGER) || !(pad.Buttons & PSP_CTRL_RTRIGGER))
			{
				lrTriggersPressed=0;
			}

		}
	//




		if(pad.Buttons & PSP_CTRL_UP && !upPressed)
		{
			if(choice==2)
				choice--;

			upPressed = 1;
		}
		else
		{
			upPressed = 0;
		}
		
		if(pad.Buttons & PSP_CTRL_DOWN && !downPressed)
		{
			if(choice==1)
				choice++;
			downPressed = 1;
		}
		else
		{
			downPressed = 0;
		}

		//////////////// PSP GO MODE /////////////////////
	if(PSPGOAvail)
	{
		if(pad.Buttons & PSP_CTRL_LTRIGGER && !ltriggerPressed)
		{
			ltriggerPressed=1;
		}
		else if(!(pad.Buttons & PSP_CTRL_LTRIGGER) && ltriggerPressed)
		{
			ltriggerPressed=0;
					if(choice==2)
						choice--;
		}

		if(pad.Buttons & PSP_CTRL_RTRIGGER && !rtriggerPressed)
		{
			rtriggerPressed=1;
		}
		else if(!(pad.Buttons & PSP_CTRL_RTRIGGER) && rtriggerPressed)
		{
			rtriggerPressed=0;
				if(choice==1)
					choice++;

		}
	}
		////////////////////////////////////////////


		// Blit Pause Image
		blitAlphaImageToScreen(0,0,480,272,*pauseScreen,0,0);

		//Blit Snake Choice
		if(choice==1)
		{
			// Left Snake
			blitAlphaImageToScreen(0,0,20,20,*snakeTail,114,126);
			blitAlphaImageToScreen(0,0,20,20,*snakeBody,134,126);
			blitAlphaImageToScreen(0,0,20,20,*snakeHead,154,126);
			
			

			// Right Snake
			blitAlphaImageToScreen(0,0,20,20,*snakeHead,310,126);
			blitAlphaImageToScreen(0,0,20,20,*snakeBody,330,126);
			blitAlphaImageToScreen(0,0,20,20,*snakeTail,350,126);
		}
		else if(choice==2)
		{
						// Left Snake
			blitAlphaImageToScreen(0,0,20,20,*snakeTail,82,156);
			blitAlphaImageToScreen(0,0,20,20,*snakeBody,102,156);
			blitAlphaImageToScreen(0,0,20,20,*snakeHead,122,156);
			
			

			// Right Snake
			blitAlphaImageToScreen(0,0,20,20,*snakeHead,340,156);
			blitAlphaImageToScreen(0,0,20,20,*snakeBody,360,156);
			blitAlphaImageToScreen(0,0,20,20,*snakeTail,380,156);

		}

		//Choice 

		
		sceDisplayWaitVblankStart();
		flipScreen();
	}
	return 0;
}

void clearGame()
{
	moveClear();
pointAlive = 0 ;
snakeTailN = 3;
GAMEOVER = 0;
POINTS = 0;
menuChoice = 0;
if(levelX==1)
	LEVEL=1;

// Clear Map
int y,x;
for(y=0;y<12;y++)
{
	for(x=0;x<24;x++)
	{
		map[y][x] = 0;
	}
}
}

void screenGameOver(Image** gameOver)
{
	SceCtrlData pad;
	int pX=54,pY=148,hsX=400,hsY=148;
	char points_c[20];
	// Get High Score
					int highScoreN = atoi(highScore);
				if(POINTS>highScoreN)
				{
					FILE* file;
					file = fopen("HS.dat","w");
					fprintf(file,"%d",POINTS);
					fclose(file);
				}
				sprintf(points_c,"%d",POINTS);

/*	if(POINTS >999)
		pointsX=290;
	else if(POINTS >99)
		pointsX=293;
	else if(POINTS>9)
		pointsX=296;
		*/

	while(isRunning())
	{
		// GET INPUT
		sceCtrlReadBufferPositive(&pad, 1);


		// Blit Background
		blitAlphaImageToScreen(0,0,480,272,*gameOver,0,0);

		// Blit Score And High Score
		printTextScreen(pX,pY,points_c,clr_black);
		printTextScreen(hsX,hsY,highScore,clr_black);


		
		sceDisplayWaitVblankStart();
		flipScreen();


				// EXIT //
		if(PSPGOAvail && ((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_RTRIGGER)))
			break;

		if((pad.Buttons & PSP_CTRL_START) || (pad.Buttons & PSP_CTRL_CROSS))
			break;
	}
	loadHighScore();
}