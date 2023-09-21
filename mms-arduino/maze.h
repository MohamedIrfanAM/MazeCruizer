#ifndef MAZE_H
#define MAZE_H
#include <Arduino.h>
#include "api.h"
#include "queue.h"

class Maze
{
  short int rows = 17;
  short int cols = 17;
  short int targetx = 7;
  short int targety = 7;
  short int X = 0;
  short int Y = 0;
  short int d = 0;
  short int H[17][17];
  short int V[17][17];
  short int D[17][17];
  short int **path;

public:
  bool isFinished();

  void intialize();

  void update();

  bool isValidIndex(int x, int y);

  void floodFill();

  void turn(int dir);

  void findPath();

  void setWallDir(int dir);

  bool getWall(int dir);

  void moveForward();

  void explore();
};
#endif