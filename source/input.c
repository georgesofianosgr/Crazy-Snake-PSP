#include <pspctrl.h>
#include "move.h"
#include "globals.h"

int inputMethod;
int ltriggerPressed=0;
int rtriggerPressed=0;
int getInput()
{
	

	SceCtrlData pad;
//	if(PSPGOAvail)
//		inputMethod = GO_METHOD;
//	else
		inputMethod = GENERAL_A;
	sceCtrlReadBufferPositive(&pad, 1);



	if(inputMethod==GENERAL_A)
	{
		if(pad.Buttons & PSP_CTRL_UP)
			return DIR_UP;
		else if(pad.Buttons & PSP_CTRL_RIGHT)
			return DIR_RIGHT;
		else if(pad.Buttons & PSP_CTRL_DOWN)
			return DIR_DOWN;
		else if(pad.Buttons & PSP_CTRL_LEFT)
			return DIR_LEFT;

/*	}
	else if(inputMethod==GO_METHOD)
	{*/
		if(pad.Buttons & PSP_CTRL_LTRIGGER && pad.Buttons & PSP_CTRL_RTRIGGER)
			return 0;


		if(pad.Buttons & PSP_CTRL_LTRIGGER && !ltriggerPressed)
		{
			ltriggerPressed = 1;
			if(getCurrentDirection() == DIR_UP)
			{
				return DIR_LEFT;
			}
			else if(getCurrentDirection() == DIR_RIGHT)
			{
				return DIR_UP;
			}
			else if(getCurrentDirection() == DIR_DOWN)
			{
				return DIR_RIGHT;
			}
			else if(getCurrentDirection() == DIR_LEFT)
			{
				return DIR_DOWN;
			}
		}
		else if(!(pad.Buttons & PSP_CTRL_LTRIGGER))
		{
			ltriggerPressed = 0;
			
		}
		
		if(pad.Buttons & PSP_CTRL_RTRIGGER && !rtriggerPressed)
		{
			rtriggerPressed = 1;
			if(getCurrentDirection() == DIR_UP)
			{
				return DIR_RIGHT;
			}
			else if(getCurrentDirection() == DIR_RIGHT)
			{
				return DIR_DOWN;
			}
			else if(getCurrentDirection() == DIR_DOWN)
			{
				return DIR_LEFT;
			}
			else if(getCurrentDirection() == DIR_LEFT)
			{
				return DIR_UP;
			}
		}
		else if(!(pad.Buttons & PSP_CTRL_RTRIGGER))
		{
			rtriggerPressed=0;
			
		}

	}
	else 
		return 0;

	return 0;
}