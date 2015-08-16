#ifndef _MOVE_H
#define _MOVE_H

int getCurrentDirection();
int snakeHeadX;
int snakeHeadY;
int snakeTailX;
int snakeTailY;
int snakeBodyN;
int currentDirection;
int tempDirection;
int newDirection;

void setSpeed(int Speed);
void moveClear(void);
void moveLoop(void);
void moveTest(void);
void moveSnake(void);
#endif