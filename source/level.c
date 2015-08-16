#include <pspkernel.h>
#include <stdio.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>
#include "callbacks.h"
#include "graphics.h"
#include "colors.h"
#include "globals.h"
#include "input.h"
#include "triggers.h"

void selectLevel()
{
		// LoadImages
	Image* levelBG;
	Image* levelText;
	Image* levelImg;

	char buffer[30];
	sprintf(buffer,"images/levelBG.png");
	levelBG = loadImage(buffer);
	sprintf(buffer,"images/levelText.png");
	levelText = loadImage(buffer);
	sprintf(buffer,"images/levelimg.png");
	levelImg = loadImage(buffer);

	if(!levelBG  || !levelText || !levelImg)
	{
		clearScreen(clr_black);
		printTextScreen(10,10,"Load Image Failed!",clr_white);
		printTextScreen(10,20,"Make sure that you transferred all images to psp.",clr_white);
		flipScreen();
		sceKernelDelayThread(1000000*3);
		exitGame();
	}


	int lselection;
	if(levelX==1)
		lselection=0;
	else 
		lselection=LEVEL;

	int lclipX=0;

	int leftPressed=0;
	int rightPressed=0;
	int ltriggerPressed=0;
	int rtriggerPressed=0;

	while(isRunning())
	{

		//print background
		blitAlphaImageToScreen(0,0,480,272,levelBG,0,0);
		


		//checkInput
		SceCtrlData pad;
		sceCtrlReadBufferPositive(&pad, 1);

		if(pad.Buttons & PSP_CTRL_RIGHT && !rightPressed)
		{


			rightPressed = 1;
		}
		else if(!(pad.Buttons & PSP_CTRL_RIGHT) && rightPressed)
		{
			if(lselection<5)
				lselection++;
			rightPressed = 0;
		}
		
		if(pad.Buttons & PSP_CTRL_LEFT && !leftPressed)
		{


			leftPressed = 1;
		}
		else if(!(pad.Buttons & PSP_CTRL_LEFT) && leftPressed)
		{
			if(lselection>0)
				lselection--;
			leftPressed = 0;
		}

		//////////////////////// PSP GO MODE ////////////////////////////////////
	if(PSPGOAvail)
	{

		if((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_RTRIGGER))
		{
			if(lselection==0)
			{
				levelX = 1;
				LEVEL=1;
			}
			else
			{
				levelX = 0;
				LEVEL=lselection;
			}

			break;
		}

		if(pad.Buttons & PSP_CTRL_LTRIGGER && !ltriggerPressed)
		{
			ltriggerPressed=1;

		}
		else if(!(pad.Buttons & PSP_CTRL_LTRIGGER) && ltriggerPressed)
		{
			if(lselection>0)
				lselection--;
			ltriggerPressed=0;
		}

		if(pad.Buttons & PSP_CTRL_RTRIGGER && !rtriggerPressed)
		{
			rtriggerPressed=1;

		}
		else if(!(pad.Buttons & PSP_CTRL_RTRIGGER) && rtriggerPressed)
		{
			if(lselection<5)
				lselection++;
			rtriggerPressed=0;
		}

	
	}
		//////////////////////// PSP GO MODE ///////////////////////////////////

		// Enter Option
		if((pad.Buttons & PSP_CTRL_CROSS) || (pad.Buttons & PSP_CTRL_START))
		{
			if(lselection==0)
			{
				levelX = 1;
				LEVEL=1;
			}
			else
			{
				levelX = 0;
				LEVEL=lselection;
			}
			break;
		}
		else if(pad.Buttons & PSP_CTRL_CIRCLE)
		{
			break;
		}


		//Options
		if(lselection==0)
			lclipX=0;
		else if(lselection==1)
			lclipX=44;
		else if(lselection==2)
			lclipX=88;
		else if(lselection==3)
			lclipX=132;
		else if(lselection==4)
			lclipX=176;
		else if(lselection==5)
			lclipX=220;

		// Blit Level 
			blitAlphaImageToScreen(0,0,116,41,levelImg,160,131);	
			blitAlphaImageToScreen(lclipX,0,44,41,levelText,160+116,131);	

		//CheckHome
		sceDisplayWaitVblankStart();
		flipScreen();
	}

	if(levelBG)
	freeImage(levelBG);
	if(levelText)
	freeImage(levelText);
	if(levelImg)
	freeImage(levelImg);
}