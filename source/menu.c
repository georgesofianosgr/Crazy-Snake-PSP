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

	u64 ticks;
	u64 snakeTicks = 9000;
	int snakeSpeed = 9000;

void menuLoop()
{
	// LoadImages
	Image* menuBG;
	Image* snake;
	Image* snakeV;
	Image* menuText;

	char buffer[30];
	sprintf(buffer,"images/menuBG.png");
	menuBG = loadImage(buffer);
	sprintf(buffer,"images/snake.png");
	snake = loadImage(buffer);
	sprintf(buffer,"images/snakeV.png");
	snakeV = loadImage(buffer);
	sprintf(buffer,"images/menuText.png");
	menuText = loadImage(buffer);

	if(!menuBG || !snake || !snakeV || !menuText)
	{
		printTextScreen(10,10,"Load Image Failed!",clr_white);
		printTextScreen(10,20,"Make sure that you transferred all images to psp.",clr_white);
		flipScreen();
		sceKernelDelayThread(1000000*3);
		exitGame();
	}

	int choice = 2;
	int snakeX =0;
	int snakeY = 174;
	int snakeDir = 0;
	int firstTicks=0;
	int lastTicks=0;

	int leftPressed=0;
	int rightPressed=0;

	int ltriggerPressed=0;
	int rtriggerPressed=0;

	while(isRunning())
	{
		// Frame Regulating START
		sceRtcGetCurrentTick(&firstTicks);
		//print background
		blitAlphaImageToScreen(0,0,480,272,menuBG,0,0);

		//Snake Effe

		if(snakeX <= -120)
			snakeDir= 1;
		else if(snakeX >= 570)
			snakeDir= 0;

		if(!snakeSpeedLimitEnabled())
		{
			if(snakeDir==1)
				snakeX+=7;
			else if(snakeDir==0)
				snakeX-=7;
		}
		
		if(snakeDir==1)
		blitAlphaImageToScreen(0,0,126,123,snake,snakeX,snakeY);
		else if(snakeDir==0)
		blitAlphaImageToScreen(0,0,126,123,snakeV,snakeX,snakeY);
		


		//checkInput
		SceCtrlData pad;
		sceCtrlReadBufferPositive(&pad, 1);

		if(pad.Buttons & PSP_CTRL_RIGHT && !rightPressed)
		{
			if(choice<3)
				choice++;

			rightPressed = 1;
		}
		else if(!(pad.Buttons & PSP_CTRL_RIGHT))
		{
			rightPressed = 0;
		}
		
		if(pad.Buttons & PSP_CTRL_LEFT && !leftPressed)
		{
			if(choice>1)
				choice--;
			leftPressed = 1;
		}
		else if(!(pad.Buttons & PSP_CTRL_LEFT))
		{
			leftPressed = 0;
		}

		//////////////////////// PSP GO MODE ////////////////////////////////////
	if(PSPGOAvail)
	{

		if((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_RTRIGGER))
		{
			if(choice==3)
				exitGame();
			else if(choice==2)
			{
				menuChoice=1;
				break;
			}
			else if(choice==1)
			{
				menuChoice=2;
				break;
			}
		}

		if(pad.Buttons & PSP_CTRL_LTRIGGER && !ltriggerPressed)
		{
			ltriggerPressed=1;
			if(choice>1)
				choice--;

		}
		else if(!(pad.Buttons & PSP_CTRL_LTRIGGER))
		{
			ltriggerPressed=0;
		}

		if(pad.Buttons & PSP_CTRL_RTRIGGER && !rtriggerPressed)
		{
			rtriggerPressed=1;
			if(choice<3)
				choice++;

		}
		else if(!(pad.Buttons & PSP_CTRL_RTRIGGER))
		{
			rtriggerPressed=0;
		}

	
	}
		//////////////////////// PSP GO MODE ///////////////////////////////////

		// Enter Option
		if((pad.Buttons & PSP_CTRL_CROSS) || (pad.Buttons & PSP_CTRL_START))
		{
			if(choice==3)
				exitGame();
			else if(choice==2)
			{
				menuChoice=1;
				break;
			}
			else if(choice==1)
			{
				menuChoice=2;
				break;
			}
		}


		//Options
		if(choice==1)
			blitAlphaImageToScreen(164,0,107,33,menuText,15,119);
		else
			blitAlphaImageToScreen(164,33,107,33,menuText,15,130);
		
		//Start Game
		if(choice==2)
			blitAlphaImageToScreen(0,0,162,33,menuText,155,120);
		else
			blitAlphaImageToScreen(0,33,162,33,menuText,155,131);


		//Exit
		if(choice==3)
			blitAlphaImageToScreen(271,0,60,33,menuText,360,119);
		else
			blitAlphaImageToScreen(271,33,60,33,menuText,360,134);
			


		//CheckHome
		sceDisplayWaitVblankStart();
		flipScreen();
		

		sceRtcGetCurrentTick( &lastTicks);
		if((lastTicks - firstTicks) < 1000000 / MENUFPS)
		{
			sceKernelDelayThread((1000000 / MENUFPS) - (lastTicks - firstTicks) );
		}
	}

	if(menuBG)
	freeImage(menuBG);
	if(snake)
	freeImage(snake);
	if(snakeV)
	freeImage(snakeV);
	if(menuText)
	freeImage(menuText);
}

int snakeSpeedLimitEnabled()
{
	sceRtcGetCurrentTick(&ticks);
   if(ticks >= snakeTicks)
   {
        snakeTicks = ticks + snakeSpeed;
		return 0;
   }
   else
	   return 1;
}
