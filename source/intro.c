#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>
#include <pspkernel.h>
#include <stdio.h>
#include <stdlib.h>


#include "graphics.h"
#include "callbacks.h"
#include "colors.h"
#include "globals.h"



void introLoop()
{
	// Load Images
	Image* background;
	Image* textImg[3];
	char imageName[25];
	sprintf(imageName,"images/introBG.png");
	background = loadImage(imageName);
	sprintf(imageName,"images/psA0.png");
	textImg[0] = loadImage(imageName);
	sprintf(imageName,"images/psA1.png");
	textImg[1] = loadImage(imageName);
	sprintf(imageName,"images/psA2.png");
	textImg[2] = loadImage(imageName);

	if(!background || !textImg[0] || !textImg[1] || !textImg[2])
	{
		printTextScreen(10,10,"Load Image Failed!",clr_white);
		printTextScreen(10,20,"Make sure that you transferred all images to psp.",clr_white);
		flipScreen();
		sceKernelDelayThread(1000000*3);
		exitGame();
		
	}

	

	SceCtrlData pad;
	int AlphaDI = 0; // 0 - Alpha Decrease , 1-Alpha Increase
	short int textNum = 2;
	u64 firstTicks = 0;
	u64 lastTicks = 0;
	short int fps = 8;

	while(isRunning())
	{

		sceRtcGetCurrentTick(&firstTicks);

		// Read Gamepad Buffer
		sceCtrlReadBufferPositive(&pad, 1);

		// Draw Background
		blitAlphaImageToScreen(0,0,480,272,background,0,0);
		
		// Press Button Text 
		if(textNum == 2)
			AlphaDI = 0;
		else if(textNum == -1)
			AlphaDI = 1;

		// Blit Press Button
		if(textNum >=0 && textNum <=2)
		{
			blitAlphaImageToScreen(0,0,159,44,textImg[textNum],165,180);
		}

		// Blit High Score
		loadHighScore();
		int highscoreX=185;
		printTextScreen(highscoreX,5,"High Score:", clr_white);
		printTextScreen(highscoreX+90,5,highScore, clr_white);

		// Blit Game Creator
		printTextScreen(330,250,"Created By Geocool", clr_black);

		// Increase Decrease Image Alpha
		if(AlphaDI)
			textNum += 1;
		else
			textNum -= 1;

		// Get Input
		if(pad.Buttons & PSP_CTRL_START)
		{
			break;
		}
		else if((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_RTRIGGER))
		{
			PSPGOAvail=1;
			break;
		}
		//Check For Home
		sceDisplayWaitVblankStart();



		//Draw Screen
		flipScreen();

		// FrameRate Regulation
		sceRtcGetCurrentTick( &lastTicks);
		if((lastTicks - firstTicks) < 1000000 / fps)
		{
			sceKernelDelayThread((1000000 / fps) - (lastTicks - firstTicks) );
		}
		
	}



	// Free Images
	if(background)
	freeImage(background);
	if(textImg[0])
	freeImage(textImg[0]);
	if(textImg[1])
	freeImage(textImg[1]);
	if(textImg[2])
	freeImage(textImg[2]);
}

