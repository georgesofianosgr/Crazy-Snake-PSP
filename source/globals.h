#ifndef _GLOBALS_H
#define _GLOBALS_H

// Directions
#define DIR_UP		1
#define DIR_RIGHT	2
#define DIR_DOWN	3
#define DIR_LEFT	4

// Input Modes
	/*
	General-A (D-PAD)	1
	General-B  (X[]O)	2
	PSP Go Mode (L-R)	3
	*/
#define GENERAL_A	1
#define GENERAL_B	2
#define GO_METHOD	3

#define WALL	-1
#define POINT	-2
#define EMPTY	 0

#define TILE_S 29 // Tile Size
#define FPS 20
#define MENUFPS 15

int loadHighScore();

int levelX;
int PSPGOAvail;
int pointAlive;
int snakeTailN;
int GAMEOVER;
int POINTS;
int LEVEL;
int menuChoice;
int pointsGain;
char highScore[20];

#endif