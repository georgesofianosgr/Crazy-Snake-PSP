#include <pspctrl.h>

int CTRL_L_PRESSED = 0;
int CTRL_R_PRESSED = 0;

/*
RETURN
1 = BUTTON_DOWN
2 = BUTTON_UP
*/
int L_TRIGGER(SceCtrlData* pad)
{
	if(pad->Buttons & PSP_CTRL_LTRIGGER && !CTRL_L_PRESSED)
	{
		CTRL_L_PRESSED = 1;
		return 1;
	}
	else if(CTRL_L_PRESSED==1 && !(pad->Buttons & PSP_CTRL_LTRIGGER))
	{
		CTRL_L_PRESSED = 0;
		return 2;
	}
	else
		return 0;
}

int R_TRIGGER(SceCtrlData* pad)
{
	if(pad->Buttons & PSP_CTRL_RTRIGGER && !CTRL_R_PRESSED)
	{
		CTRL_R_PRESSED = 1;
		return 1;
	}
	else if(CTRL_R_PRESSED==1 && !(pad->Buttons & PSP_CTRL_RTRIGGER))
	{
		CTRL_R_PRESSED = 0;
		return 2;
	}
	else
		return 0;
}
