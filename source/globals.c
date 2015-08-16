#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int levelX = 1;
int PSPGOAvail=1;
int pointAlive = 1;
int snakeTailN = 3;
int GAMEOVER=0;
int POINTS=0;
int LEVEL=0;
int menuChoice=0;
int pointsGain = 15;
char highScore[20];

void loadHighScore()
{
	// Check If file exist if not create it
	FILE* file;
	// Load File
	file = fopen("HS.dat","r");
	if(!file)
	{
		file = fopen("HS.dat","w+");
		fprintf(file,"%d",0);
	}

	char buffer[20];
	int i;
	for(i=0;i<20;i++)
	{
		buffer[i] = getc(file);

		if(buffer[i]==EOF)
		{
			buffer[i] = '\0';
			break;
		}
		else if(buffer[i]!=EOF && i==19)
		{
			buffer[i] = '\0';
		}
			
	}
	fclose(file);

	strcpy(highScore,buffer);
}
