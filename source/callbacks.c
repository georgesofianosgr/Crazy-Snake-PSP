#include <pspkernel.h> // For PSP Main Instructions
//#include <pspdebug.h> // Unknown

static int exitRequest = 0;

void exitGame()
{
	exitRequest = 1;
}

int isRunning()
{
	return !exitRequest;
}

// Exit Callback
int exit_callback(int arg1,int arg2,void* common)
{
	exitRequest = 1;
	return 0;
}
// Callback Thread
int CallbackTread(SceSize args, void* argp)
{
	int cbid;
	cbid = sceKernelCreateCallback("Exit Callback",exit_callback,NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}

// Sets Up Callback
int SetupCallbacks(void)
{
	int thid = 0;
	thid = sceKernelCreateThread("update_thread",CallbackTread,0x11,0xFA0,0,0);
	if(thid >=0)
	{
		sceKernelStartThread(thid,0,0);			
	}
	return thid;
}